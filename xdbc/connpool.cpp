/***************************************
**file：			implement of class ConnectionPool
**description:		A simple implement of connection pool
**copyright:		vathena
**date:				16/11/2015
**version:			V1.0.1
****************************************/
#include "xdbc/connpool.h"
#include "xdbc/mysqlConnection.h"

__CONNPOOL_LOCK_BEGIN_NAMESPACE
pthread_mutex_t ConnPoolLock;
__CONNPOOL_LOCK_END_NAMESPACE

//create a connection pool instance for each process, befor enter main
ConnectionPool* ConnectionPool::connpool = NULL;
ConnectionPool::Deleter ConnectionPool::deleter;

ConnectionPool::ConnectionPool():m_maxSize(MAX_CONN_SIZE),m_curSize(0)
{
	//cout << "come to the connection pool constructor" << endl;
	Initialize(m_maxSize/2);
}

ConnectionPool::ConnectionPool(int size):m_maxSize(size),m_curSize(0)
{
	Initialize(m_maxSize/2);
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
		}
	}
	pthread_mutex_unlock(&__CONNPOOL_LOCK_NAMESPACE::ConnPoolLock);
	return connpool;
}

void ConnectionPool::GetConnection(xConnection **pConn)
{
	//cout << "GetConnection，current thread:" << pthread_self() << endl;
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
	
	if( !(*pConn) && ( m_curSize < MAX_CONN_SIZE ) )
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
	
	if( !(*pConn) )
	{
		//应用上，此处更好的处理方式应该是如果超过连接池最大连接数，则等待直至有空闲连接或服务程序超时返回
		string errmsg = "Maximum allowable number of database connections.";
		throw SQLException(errmsg);
	}
	
	pthread_mutex_unlock(&m_lock);
	//return *pConn;
}

void ConnectionPool::Initialize(int size)
{
	if( size > MAX_CONN_SIZE )
	{
		size = MAX_CONN_SIZE;
	}
	
	xConnection *pConn;
	for(int i=0; i < size; i++)
	{
		pConn = CreateConnection();
		m_pConnList.push_back(pConn);
	}
}

xConnection* ConnectionPool::CreateConnection()
{
	xConnection *pConn;
	if( XDBC_CONN_TYPE == _MYSQL )
	{
		pConn = new MysqlConnection();
	}
	else if( XDBC_CONN_TYPE == _ORACLE )
	{
		//return you oracle connection in this case
		string errmsg = "XDBC_CONN_TYPE of _ORACLE does not support";
		throw SQLException(errmsg);
	}
	else
	{
		//unkown database type，do something in this scope	
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
	list<xConnection*>::iterator it;
	for( it = m_pConnList.begin(); it != m_pConnList.end(); it++ )
	{
		delete (*it);
	}
}