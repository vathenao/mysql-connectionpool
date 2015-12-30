#ifndef __MYSQL_CONNECTION_H__
#define __MYSQL_CONNECTION_H__

#include <mysql.h>
#include "x_connection.h"

class MysqlConnection : public xConnection
{
public:
	MysqlConnection() DECL_THROW_EXCEPTION(SQLException);
	~MysqlConnection();
	
	xPrepareStatement* prepareStatement(const string &sqlStr) DECL_THROW_EXCEPTION(SQLException);
	
private:
	//Shields the copy constructor and the assignment operator
	MysqlConnection( const MysqlConnection &mysql){}
	MysqlConnection &operator=(const MysqlConnection &mysql){}
	
private:
	MYSQL m_Conn;
};

#endif