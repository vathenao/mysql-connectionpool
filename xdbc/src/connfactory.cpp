#include "stdafx.h"
#include "connfactory.h"
#include "sqlException.h"
#include "mysqlConnection.h"

xConnection* CConnFactory::GetConn()
{
	xConnection * pConn = NULL;
	/*if( dbType == _MYSQL ) pConn = new MysqlConnection();
	else
	{
		throw SQLException("create connection,unkonw database type!");
	}*/
	return pConn;
}

CConnFactory::~CConnFactory()
{
	
}