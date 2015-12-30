#include "xdbc/mysqlConnection.h"
#include "xdbc/mysqlPrepareStatement.h"


MysqlConnection::MysqlConnection() DECL_THROW_EXCEPTION(SQLException)
{
	mysql_init(&m_Conn);
	if( !mysql_real_connect(&m_Conn, "localhost", "staff", "staff@123", "FSBL", 0, NULL, 0) )
	{
		string errmsg;
		errmsg.append("connect to database fail.");
		errmsg.append(mysql_error(&m_Conn));
		throw SQLException(errmsg);
	}
}

MysqlConnection::~MysqlConnection()
{
	mysql_close(&m_Conn);
}

xPrepareStatement* MysqlConnection::prepareStatement(const string &sqlStr) DECL_THROW_EXCEPTION(SQLException)
{
	return new MysqlPrepareStatement(&m_Conn, sqlStr);
}