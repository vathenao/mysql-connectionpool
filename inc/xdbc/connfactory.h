#ifndef __CONN_FACTORY_H__
#define __CONN_FACTORY_H__

#include "x_connection.h"

class CConnFactory
{
public:
	static xConnection* GetConn(DBTYPE dbType);
	~CConnFactory();
private:
	CConnFactory();
};

#endif