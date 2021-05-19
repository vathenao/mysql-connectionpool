#ifndef __CONNECTION_POOL_H__
#define __CONNECTION_POOL_H__

#include "x_connection.h"
#include <pthread.h>

class ConnectionPool
{
	ConnectionPool();
	~ConnectionPool();

public:
	static ConnectionPool* GetInstance();

	/*<D> Add a database connection to the connection pool
	/*<P> pConn: A pointer point to the connection which will be added to the connection pool.*/
	/*<Remark> Usually, this function is used to add connection to the connection pool at a working thread*/
	void AddConnection(xConnection* pconn);

	/*<D> remove connection from the connection pool
	/*<P> pConn: A pointer point to the connection which will be remove from the connection pool.*/
	/*<Remark> Usually, this function is used to remove connection to the connection pool at a working thread*/
	void RemoveConnection(xConnection* pconn);

	/*<D> Get a free connection from the connection pool, if there is no free connection in the 
	connection pool, this function will create a new connection except the connection pool is full.*/
	/*<P> pConn: A pointer that use for receiving the return connection point to a pointer which point to the connection.*/
	/*<P> timeout(seconds): When requesting a connection from connection pool in the case of connection pool is full and there is 
	no free connection immediately. The request will wait for a free connection and the waiting time of the request can be	
	set with this parameter.If this parameter wasn't set, the waiting time will be refer to the velue was declared in the 
	configuration file with TIMEOUT under the section [ConnPoolConf] */
	/*<Remark> Finish using a connection, function ReleaseConnection must be called to release 
	the connection, otherwise it will be mark as busy all the time.*/
	xConnection* GetConnection();

	/*<D> Release the connection to the connection pool.*/
	/*<P> Pointer to the connection which want to release.*/
	/*<Remark> Finish using a connection, function ReleaseConnection must be called to release 
	the connection, otherwise it will be mark as busy all the time.*/
	void ReleaseConnection(xConnection*);

	/*<D> get count of the connection pool */
	/*<P> none*/
	/*<return> size of connection pool*/
	size_t Count();

	/*<D> check the connection poll is full */
	/*<P> none*/
	/*<return> return full if the connection pool is full, otherwise return false*/
	bool IsFull();
	
	/*<D> check if has any free connection in the connection pool */
	/*<P> Pointer to a size_t used to recieve the count of free connection*/
	/*<return> return full if the connection pool is full, otherwise return false*/
	bool HasFree(OUT size_t *freeConnCount = NULL);

private:
	void Init();
	
private:
	pthread_mutex_t m_lock;
	list<xConnection*> m_pConnList;
	static ConnectionPool* sm_connpool;

private:
	size_t m_maxConns;
};

class ConnectionPoolMgr
{
	ConnectionPoolMgr();
	~ConnectionPoolMgr();

public:
	static ConnectionPoolMgr* GetInstance();
	void GetConnection(xConnection **pConn, int timeout = 0);
	void ReleaseConnection(xConnection*);

	void Init();

private:
	list<xConnection*> m_pConnList;
	int m_timeout;
};
#endif