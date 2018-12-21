#include "stdafx.h"
#include "connfactory.h"
#include "sqlException.h"
#include "mysqlConnection.h"

ConnFactory* ConnFactory::GetInstance()
{
	static ConnFactory obj;
	return &obj;
}

xConnection* ConnFactory::GetConn(xdbc::XDBC_DB_TYPE type)
{
	xConnection *pConn;
	switch (type)
	{
	case xdbc::DB_MYSQL:
	{
		pConn = new MysqlConnection();
	}
		break;
	case xdbc::DB_ORACLE:
	{
		string errmsg = "XDBC_CONN_TYPE of ORACLE does not support";
		throw SQLException(errmsg);
	}
		break;
	case xdbc::DB_SQLSERVER:
	{
		string errmsg = "XDBC_CONN_TYPE of SQLSERVER does not support";
		throw SQLException(errmsg);
	}
	break;
	default:
	{
		//unkown database type£¬do something in this scope	
		string errmsg = " unkown database type, check the support values of XDBC_CONN_TYPE ";
		throw SQLException(errmsg);
	}
	break;
	}

	return pConn;
}

ConnFactory::ConnFactory()
{

}
