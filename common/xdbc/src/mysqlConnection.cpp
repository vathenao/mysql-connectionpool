#include "stdafx.h"
#include "mysqlConnection.h"
#include "mysqlPrepareStatement.h"
#include "xdbc.h"

#include <base/configHelper.h>

MysqlConnection::MysqlConnection()
	: m_pPreStmt(NULL)
	, m_bConned(false)
{

}

MysqlConnection::~MysqlConnection()
{
	mysql_close(&m_Conn);
}

xPrepareStatement* MysqlConnection::prepareStatement(const string &sqlStr) DECL_THROW_EXCEPTION(SQLException)
{	
	m_pPreStmt = new MysqlPrepareStatement(&m_Conn, sqlStr);	
	return m_pPreStmt;
}

void MysqlConnection::TransactionStart()
{
	string sqlStr = "set autocommit=0";
	MysqlPrepareStatement preStmt(&m_Conn, sqlStr);
	preStmt.executeUpdate(sqlStr);
}

void MysqlConnection::TransactionEnd()
{
	string sqlStr = "set autocommit=1";
	MysqlPrepareStatement preStmt(&m_Conn, sqlStr);
	preStmt.executeUpdate(sqlStr);
}

void MysqlConnection::RollBack()
{
	string sqlStr = "rollback";
	MysqlPrepareStatement preStmt(&m_Conn, sqlStr);
	preStmt.executeUpdate(sqlStr);
}

void MysqlConnection::Commit()
{
	string sqlStr = "commit";
	MysqlPrepareStatement preStmt(&m_Conn, sqlStr);
	preStmt.executeUpdate(sqlStr);
}

bool MysqlConnection::IsConnected()
{
	int ret = mysql_ping(&m_Conn);
	if (ret != 0)
	{
		cout << "mysql_ping failed" << mysql_error(&m_Conn) << endl;
		return false;
	}

	return true;
}

void MysqlConnection::ConnectToDB()
{
	if (m_bConned)
		return;

	string host = xdbc::db::GetHost();
	string user = xdbc::db::GetUser();
	string passwd = xdbc::db::GetPwd();
	string database = xdbc::db::GetDatabaseName();

	mysql_init(&m_Conn);
	if( !mysql_real_connect(&m_Conn, host.c_str(), user.c_str(),
		passwd.c_str(), database.c_str(), 0, NULL, 0) )
	{
		string errmsg;
		errmsg.append("connect to database fail.");
		errmsg.append(mysql_error(&m_Conn));
		throw SQLException(errmsg);
	}

	char value = 1;
	int timeOut = 5;
	mysql_options(&m_Conn, MYSQL_OPT_RECONNECT, &value);
	mysql_options(&m_Conn, MYSQL_OPT_READ_TIMEOUT, (char*)&timeOut);

	m_bConned = true;
}
