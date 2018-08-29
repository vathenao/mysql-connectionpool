#include "mysqlConnection.h"
#include <base/configHelper.h>

MysqlConnection::MysqlConnection() DECL_THROW_EXCEPTION(SQLException):m_pPreStmt(NULL)
{	
	//load connection information
	LoadConnectionInfo();
	
	ConnectToDB();	
}

MysqlConnection::MysqlConnection(const string &host, const string &user, const string &password, const string &database):m_pPreStmt(NULL)
{
	m_host = host;
	m_user = user;
	m_password = password;
	m_database = database;
	
	ConnectToDB();
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


void MysqlConnection::LoadConnectionInfo(const string &fileName)
{		
	try
	{
		VConfigHelper configHelper;
		if( isNotEqual( fileName, "" ) )
		{
			configHelper.ReLoad(fileName);
		}
		else
		{
			configHelper.ReLoad(CONFIG_FILE_NAME);
		}
		
		if( !configHelper.GetConfigStringValue("ConnInfo", "HOST", m_host) )
		{
			throw SQLException( configHelper.GetLastErrorMsg() );
		}
		
		if( !configHelper.GetConfigStringValue("ConnInfo", "USER", m_user) )
		{
			throw SQLException( configHelper.GetLastErrorMsg() );
		}
		
		if( !configHelper.GetConfigStringValue("ConnInfo", "PASSWD", m_password) )
		{
			throw SQLException( configHelper.GetLastErrorMsg() );
		}
		
		if( !configHelper.GetConfigStringValue("ConnInfo", "DATABASE", m_database) )
		{
			throw SQLException( configHelper.GetLastErrorMsg() );
		}
		
	}
	catch(CBaseException ex)
	{
		throw SQLException( ex.getMessage() );
	}
	
}

void MysqlConnection::ConnectToDB()
{
	mysql_init(&m_Conn);
	if( !mysql_real_connect(&m_Conn, m_host.c_str(), m_user.c_str(), 
							m_password.c_str(), m_database.c_str(), 0, NULL, 0) )
	{
		string errmsg;
		errmsg.append("connect to database fail.");
		errmsg.append(mysql_error(&m_Conn));
		throw SQLException(errmsg);
	}
}