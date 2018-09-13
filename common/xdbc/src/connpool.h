#ifndef __CONNECTION_POOL_H__
#define __CONNECTION_POOL_H__

#include "x_connection.h"
#include <pthread.h>

/*
#define SUCCESS 0
#define FAILURE 1
*/
class ConnectionPool
{
private:
	ConnectionPool();
	
public:
	static ConnectionPool* GetInstance();
	/*<D> Get a free connection from the connection pool, if there is no free connection in the 
	connection pool, this function will create a new connection except the connection pool is full.*/
	/*<P> pConn: A pointer that use for receiving the return connection point to a pointer which point to the connection.*/
	/*<P> timeout(seconds): When requesting a connection from connection pool in the case of connection pool is full and there is 
	no free connection immediately. The request will wait for a free connection and the waiting time of the request can be	
	set with this parameter.If this parameter wasn't set, the waiting time will be refer to the velue was declared in the 
	configuration file with TIMEOUT under the section [ConnPoolConf] */
	/*<Remark> Finish using a connection, function ReleaseConnection must be called to release 
	the connection, otherwise it will be mark as busy all the time.*/
	void GetConnection(xConnection **pConn, int timeout=0);
	
	/*<D> Release the connection to the connection pool.*/
	/*<P> Pointer to the connection which want to release.*/
	/*<Remark> Finish using a connection, function ReleaseConnection must be called to release 
	the connection, otherwise it will be mark as busy all the time.*/
	void ReleaseConnection(xConnection*);
	
private:
	void GetConn(xConnection **pConn);
	void Initialize();
	xConnection* CreateConnection();
	void DestoryConnPool();
	void LoadConfig(const string &fileName="");
	
private:
	static ConnectionPool* connpool;
	int m_maxSize;
	int m_curSize;
	pthread_mutex_t m_lock;	//thread lock
	list<xConnection*> m_pConnList;
	//connection information
	string m_host;
	string m_user;
	string m_password;
	string m_database;
	string m_dbtype;
	int m_itimeout;
	
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