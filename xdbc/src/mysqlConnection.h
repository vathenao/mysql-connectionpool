#ifndef __MYSQL_CONNECTION_H__
#define __MYSQL_CONNECTION_H__

#include <mysql.h>
#include "x_connection.h"

class MysqlPrepareStatement;
class MysqlConnection : public xConnection
{
public:
	MysqlConnection() DECL_THROW_EXCEPTION(SQLException);
	MysqlConnection(const string &host, const string &user, const string &password, const string &database);
	~MysqlConnection();
	
	xPrepareStatement* prepareStatement(const string &sqlStr) DECL_THROW_EXCEPTION(SQLException);
	void TransactionStart();
	void TransactionEnd();
	void RollBack();
	void Commit();
	
private:
	//Shields the copy constructor and the assignment operator
	MysqlConnection( const MysqlConnection &mysql){}
	MysqlConnection &operator=(const MysqlConnection &mysql){}
	
	void LoadConnectionInfo(const string &fileName="");
	void ConnectToDB();
	
private:
	MYSQL m_Conn;
	string m_host;
	string m_user;
	string m_password;
	string m_database;
	MysqlPrepareStatement *m_pPreStmt;
};

#endif