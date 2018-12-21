/***************************************
**file£º			implement of class ConnectionPool
**description:		A simple implement of connection pool
**copyright:		vathena
**date:				16/11/2015
**version:			V1.0.1
****************************************/

#include "stdafx.h"
#include "connpool.h"
#include "xdbc.h"
#include "connfactory.h"
#include "connpoolException.h"
#include "base/platform.h"

#ifndef WIN32
#include <unistd.h>
#endif // !WIN32

namespace
{
	pthread_mutex_t g_connMgrLock = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t g_connPoolLock = PTHREAD_MUTEX_INITIALIZER;
	SEMHANDLE g_createConnNotify = NULL;
}

ConnectionPool::ConnectionPool()
{
	
}

ConnectionPool::~ConnectionPool()
{
	for (list<xConnection*>::iterator it = m_pConnList.begin(); it != m_pConnList.end(); it++)
	{
		delete (*it);
	}

	m_pConnList.clear();
}

ConnectionPool* ConnectionPool::sm_connpool = new ConnectionPool;
ConnectionPool* ConnectionPool::GetInstance()
{
	static bool bInited = false;
	if (bInited)
		return sm_connpool;

	pthread_mutex_lock(&g_connPoolLock);
	if (!bInited)
	{
		sm_connpool->Init();
		bInited = true;
	}
	pthread_mutex_unlock(&g_connPoolLock);
	return sm_connpool;
}

void ConnectionPool::AddConnection(xConnection* pConn)
{
	pthread_mutex_lock(&m_lock);
	m_pConnList.push_back(pConn);
	pthread_mutex_unlock(&m_lock);
}

void ConnectionPool::RemoveConnection(xConnection* pconn)
{
	pthread_mutex_lock(&m_lock);

	for (list<xConnection*>::iterator it = m_pConnList.begin(); it != m_pConnList.end(); )
	{
		if (*it == pconn)
		{
			it = m_pConnList.erase(it);
			continue;
		}

		it++;
	}

	pthread_mutex_unlock(&m_lock);
}

xConnection* ConnectionPool::GetConnection()
{
	//return a connection from the connection pool
	pthread_mutex_lock(&m_lock);
	xConnection *pConn = NULL;
	list<xConnection*>::iterator it;
	for (it = m_pConnList.begin(); it != m_pConnList.end(); it++)
	{
		if ((*it)->IsFree())
		{
			(*it)->Lock();
			pConn = *it;
			break;
		}
	}

	pthread_mutex_unlock(&m_lock);
	return pConn;
}

void ConnectionPool::ReleaseConnection(xConnection* pConn)
{
	if (pConn)
		pConn->UnLock();
}

size_t ConnectionPool::Count()
{
	size_t count = 0;
	pthread_mutex_lock(&m_lock);
	count = m_pConnList.size();
	pthread_mutex_unlock(&m_lock);

	return count;
}

bool ConnectionPool::IsFull()
{
	return Count() >= m_maxConns;
}

bool ConnectionPool::HasFree(OUT size_t *freeConnCount /*= NULL*/)
{
	/*size_t tatolCount = Count();
	size_t usedCount = CurrentUsed();
	size_t freeCount = tatolCount > usedCount ? tatolCount - usedCount : 0;

	if (NULL != freeConnCount)
		*freeConnCount = freeCount;

	return freeCount > 0;*/
	
	bool bHasFree = false;
	for (list<xConnection*>::iterator it = m_pConnList.begin(); it != m_pConnList.end(); it++)
	{
		if ((*it)->IsFree())
		{
			bHasFree = true;
			break;
		}
	}

	return bHasFree;
}

void ConnectionPool::Init()
{
	pthread_mutex_init(&m_lock, NULL);
	m_pConnList.clear();

	m_maxConns = xdbc::connpool::GetMaxConnSize();
}

void* CreateConnectionWorkerThread(void*)
{
	xdbc::XDBC_DB_TYPE dbType = xdbc::connpool::GetDbType();
	ConnectionPool* pConnPool = ConnectionPool::GetInstance();
	ConnFactory* factory = ConnFactory::GetInstance();
	if (g_createConnNotify == NULL)
		g_createConnNotify = CreateSemaphore(NULL, 0, 1, NULL);

	while (true)
	{
		WaitForSingleObject(g_createConnNotify, INFINITE);
		if (pConnPool->IsFull())
			continue;

		try 
		{
			xConnection* pConn = factory->GetConn(dbType);
			pConn->ConnectToDB();
			pConnPool->AddConnection(pConn);
		}
		catch (CoreException ex)
		{
			//handle database connect exception
			//cout << ex.getMessage() << endl;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
ConnectionPoolMgr::ConnectionPoolMgr()
{
}

ConnectionPoolMgr::~ConnectionPoolMgr()
{

}

ConnectionPoolMgr* ConnectionPoolMgr::GetInstance()
{
	static ConnectionPoolMgr* pConnpoolMgr = NULL;
	if (pConnpoolMgr)
		return pConnpoolMgr;

	pthread_mutex_lock(&g_connMgrLock);
	if (!pConnpoolMgr)
	{
		pConnpoolMgr = new ConnectionPoolMgr();
		pConnpoolMgr->Init();
	}
	pthread_mutex_unlock(&g_connMgrLock);
	return pConnpoolMgr;
}

void ConnectionPoolMgr::GetConnection(xConnection **pConn, int timeout /*= 0*/)
{
	time_t begin;
	time_t now;
	time(&begin);
	int _timeout = timeout > 0 ? timeout : m_timeout;

	ConnectionPool* pConnPool = ConnectionPool::GetInstance();
	while (1)
	{
		if (!pConnPool->HasFree() && !pConnPool->IsFull())
		{
			ReleaseSemaphore(g_createConnNotify, 1, NULL);
			_Sleep(0);
		}
		
		*pConn = pConnPool->GetConnection();
		if (*pConn)
		{
			//break;
			if ((*pConn)->IsConnected())
			{
				break;
			}
			
			pConnPool->RemoveConnection(*pConn);
		}

		time(&now);
		if (now - begin > _timeout)
		{
			string errmsg = "ERR_GETCONN_TIMEOUT";
			throw ConnpollException(errmsg);
		}

		_Sleep(0);
	}
}

void ConnectionPoolMgr::ReleaseConnection(xConnection* pConn)
{
	ConnectionPool::GetInstance()->ReleaseConnection(pConn);
}

void ConnectionPoolMgr::Init()
{
	m_timeout = xdbc::connpool::GetConnTimeOut();
	if (m_timeout < 0)
		m_timeout = 10;

	pthread_t createConnThread;
	pthread_create(&createConnThread, NULL,CreateConnectionWorkerThread, NULL);
	_Sleep(0);
}
