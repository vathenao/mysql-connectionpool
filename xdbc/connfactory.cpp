#include "xdbc/connfactory.h"
#include "xdbc/sqlException.h"
#include "xdbc/mysqlConnection.h"

xConnection* CConnFactory::GetConn(DBTYPE dbType)
{
	xConnection * pConn = NULL;
	if( dbType == _MYSQL ) pConn = new MysqlConnection();
	else
	{
		throw SQLException("create connection,unkonw database type!");
	}
	return pConn;
}

CConnFactory::~CConnFactory()
{
	
}