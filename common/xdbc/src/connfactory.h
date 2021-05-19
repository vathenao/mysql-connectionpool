#ifndef __CONN_FACTORY_H__
#define __CONN_FACTORY_H__

#include "x_connection.h"
#include "xdbc.h"

class ConnFactory
{
public:
	static ConnFactory* GetInstance();

	xConnection* GetConn(xdbc::XDBC_DB_TYPE type);

private:
	ConnFactory();
};

#endif