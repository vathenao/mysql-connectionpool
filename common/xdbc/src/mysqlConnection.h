#ifndef __MYSQL_CONNECTION_H__
#define __MYSQL_CONNECTION_H__

#include <mysql.h>
#include "x_connection.h"

class MysqlPrepareStatement;
class MysqlConnection : public xConnection
{
public:
	MysqlConnection();
	~MysqlConnection();
	
	xPrepareStatement* prepareStatement(const string &sqlStr) DECL_THROW_EXCEPTION(SQLException);

	void ConnectToDB();
	void TransactionStart();
	void TransactionEnd();
	void RollBack();
	void Commit();
	bool IsConnected();
	
private:
	//Shields the copy constructor and the assignment operator
	MysqlConnection( const MysqlConnection &mysql){}
	MysqlConnection &operator=(const MysqlConnection &mysql){}

private:
	MYSQL m_Conn;
	MysqlPrepareStatement *m_pPreStmt;
	bool m_bConned;
};

#endif