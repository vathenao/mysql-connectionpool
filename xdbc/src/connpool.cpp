/***************************************
**file£º			implement of class ConnectionPool
**description:		A simple implement of connection pool
**copyright:		vathena
**date:				16/11/2015
**version:			V1.0.1
****************************************/

#include "stdafx.h"
#include "mysqlConnection.h"
#include "connpoolException.h"
#include "connpool.h"

#include <base/configHelper.h>
#include <base/pubfunc.h>

#ifndef WIN32
#include <unistd.h>
#endif // !WIN32

__CONNPOOL_LOCK_BEGIN_NAMESPACE
pthread_mutex_t ConnPoolLock = PTHREAD_MUTEX_INITIALIZER;
__CONNPOOL_LOCK_END_NAMESPACE

//create a connection pool instance for each process, befor enter main

ConnectionPool* ConnectionPool::connpool = NULL;
ConnectionPool::Deleter ConnectionPool::deleter;

ConnectionPool::ConnectionPool():m_curSize(0),m_itimeout(60)
{
	//cout << "come to the connection pool constructor" << endl;
	Initialize();
}

ConnectionPool* ConnectionPool::GetInstance()
{
	if( connpool )
	{
		return connpool;
	}
	
	pthread_mutex_lock(&__CONNPOOL_LOCK_NAMESPACE::ConnPoolLock);
	if( !connpool )
	{
		//cout << "sleep thread:" << pthread_self() << endl;
		try
		{
			connpool = new ConnectionPool();
		}
		catch(...)
		{
			pthread_mutex_unlock(&__CONNPOOL_LOCK_NAMESPACE::ConnPoolLock);
			throw SQLException("ConnectionPool::GetInstance, unkown exception!");
		}
	}
	pthread_mutex_unlock(&__CONNPOOL_LOCK_NAMESPACE::ConnPoolLock);
	return connpool;
}

void ConnectionPool::GetConnection(xConnection **pConn, int timeout)
{
	time_t begin;
	time_t now;
	time(&begin);
	int _timeout = timeout > 0 ? timeout : m_itimeout; 
	
	while(1)
	{
		GetConn( pConn );
		if( *pConn )
		{
			break;
		}
		time(&now);
		if( now - begin > _timeout)
		{
			string errmsg = "ERR_GETCONN_TIMEOUT";
			throw ConnpollException(errmsg);
		}
		
#ifdef WIN32
		Sleep(1000);
#else
		sleep(1);
#endif // WIN32
	}
}

void ConnectionPool::GetConn(xConnection **pConn)
{
	//cout << "GetConnection£¬current thread:" << pthread_self() << endl;
	*pConn = NULL;
	pthread_mutex_lock(&m_lock);
	
	//return a connection from the connection pool
	list<xConnection*>::iterator it;
	for( it = m_pConnList.begin(); it != m_pConnList.end(); it++ )
	{
		if( (*it)->IsFree())
		{
			(*it)->Lock();
			*pConn = *it;
			break;
		}
	}
	
	if( !(*pConn) && ( m_curSize < m_maxSize ) )
	{
		try
		{
			*pConn = CreateConnection();
			m_pConnList.push_back(*pConn);
			(*pConn)->Lock();
		}
		catch(SQLException ex)	//catch the exception here because of the lock has to be released
		{
			string errmsg = "GetConnection fail,";
			errmsg.append(ex.getMessage());
			pthread_mutex_unlock(&m_lock);
			throw SQLException(errmsg);
		}
		catch(exception ex)
		{
			string errmsg = "GetConnection fail,";
			errmsg.append(ex.what());
			pthread_mutex_unlock(&m_lock);
			throw SQLException(errmsg);
		}
		catch(...)
		{
			string errmsg = "GetConnection fail,other exceptions.";
			pthread_mutex_unlock(&m_lock);
			throw SQLException(errmsg);
		}
	}
	
	pthread_mutex_unlock(&m_lock);
	//return *pConn;
}

void ConnectionPool::Initialize()
{
	xConnection *pConn;
	pthread_mutex_init( &m_lock, NULL );
	
	//load the configuration file
	LoadConfig();
	
	for(int i=0; i < m_maxSize/2; i++)
	{
		pConn = CreateConnection();
		m_pConnList.push_back(pConn);	
	}
}

xConnection* ConnectionPool::CreateConnection()
{
	xConnection *pConn;
	if( m_dbtype == "MYSQL" )
	{
		pConn = new MysqlConnection(m_host, m_user, m_password, m_database);
	}
	else if( m_dbtype == "ORACLE" )
	{
		//return you oracle connection in this case
		string errmsg = "XDBC_CONN_TYPE of ORACLE does not support";
		throw SQLException(errmsg);
	}
	else
	{
		//unkown database type£¬do something in this scope	
		string errmsg = " unkown database type, check the support values of XDBC_CONN_TYPE ";
		throw SQLException(errmsg);
	}
	
	m_curSize++;
	return pConn;
}

void ConnectionPool::ReleaseConnection(xConnection* pConn)
{
	if( pConn )
	{
		pConn->UnLock();
	}
}

void ConnectionPool::DestoryConnPool()
{
	pthread_mutex_destroy( &m_lock );
	pthread_mutex_destroy( &connpoollocklib::ConnPoolLock );
	list<xConnection*>::iterator it;
	for( it = m_pConnList.begin(); it != m_pConnList.end(); it++ )
	{
		delete (*it);
	}
}

void ConnectionPool::LoadConfig(const string &fileName)
{
	try
	{
		VConfigHelper configHelper;
		if( isNotEqual( fileName, "" ) )
		{
			configHelper.ReLoad(fileName);
		}
		else
		{
			configHelper.ReLoad(CONFIG_FILE_NAME);
		}
		
		if( !configHelper.GetConfigStringValue("ConnInfo", "HOST", m_host) )
		{
			throw SQLException(configHelper.GetLastErrorMsg());
		}
		
		if( !configHelper.GetConfigStringValue("ConnInfo", "USER", m_user) )
		{
			throw SQLException(configHelper.GetLastErrorMsg());
		}
		
		if( !configHelper.GetConfigStringValue("ConnInfo", "PASSWD", m_password) )
		{
			throw SQLException(configHelper.GetLastErrorMsg());
		}
		
		if( !configHelper.GetConfigStringValue("ConnInfo", "DATABASE", m_database) )
		{
			throw SQLException(configHelper.GetLastErrorMsg());
		}
		
		if( !configHelper.GetConfigStringValue("ConnPoolConf", "DBTYPE", m_dbtype) )
		{
			throw SQLException(configHelper.GetLastErrorMsg());
		}
		
		if( !configHelper.GetConfigIntValue("ConnPoolConf", "MAXCONNSIZE", m_maxSize) )
		{
			throw SQLException(configHelper.GetLastErrorMsg());
		}
		m_maxSize = m_maxSize < 200 ? m_maxSize : 200;
		
		if( !configHelper.GetConfigIntValue("ConnPoolConf", "TIMEOUT", m_itimeout) )
		{
			if( configHelper.GetLastErrorCode() != VCHP_KEY_NOTFOUND )
			{
				throw SQLException(configHelper.GetLastErrorMsg());
			}
		}
		m_itimeout = (m_itimeout < 0 || configHelper.GetLastErrorCode() == VCHP_KEY_NOTFOUND) ? 60: m_itimeout;
		
	}
	catch(CBaseException ex)
	{
		string errmsg = "Read configuration file infomation,";
		errmsg.append(ex.getMessage());
		throw SQLException(errmsg);
	}
}