#ifndef __CONNECTION_POOL_H__
#define __CONNECTION_POOL_H__

#include "x_connection.h"
#include <pthread.h>
#include <list>


# if defined(__WILLOW_HAS_NAMESPACES) && !defined(__WILLOW_NO_NAMESPACES)
#   define __CONNPOOL_LOCK_BEGIN_NAMESPACE namespace connpoollocklib {
#   define __CONNPOOL_LOCK_END_NAMESPACE }
#	define __CONNPOOL_LOCK_NAMESPACE connpoollocklib
# else
#   define __CONNPOOL_LOCK_BEGIN_NAMESPACE
#   define __CONNPOOL_LOCK_END_NAMESPACE
#	define __CONNPOOL_LOCK_NAMESPACE
# endif

class ConnectionPool
{
private:
	ConnectionPool();
	ConnectionPool(int size);
	
public:
	static ConnectionPool* GetInstance();
	void GetConnection(xConnection **pConn);
	void ReleaseConnection(xConnection*);
	
private:
	void Initialize(int size);
	xConnection* CreateConnection();
	void DestoryConnPool();
	
private:
	static ConnectionPool* connpool;
	int m_maxSize;
	int m_curSize;
	pthread_mutex_t m_lock;	//thread lock
	list<xConnection*> m_pConnList;
	
	class Deleter
	{
	public:
		~Deleter()
		{
			if (ConnectionPool::connpool != NULL)
			{
				ConnectionPool::connpool->DestoryConnPool();
				delete ConnectionPool::connpool;
			}
		}
	};
	// 定义一个静态的Deleter实例
	static Deleter deleter;
};
#endif