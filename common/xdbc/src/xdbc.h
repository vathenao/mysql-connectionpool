#ifndef __XDBC_H__
#define __XDBC_H__

#include <iostream>

using namespace std;
namespace xdbc
{
	enum XDBC_DB_TYPE
	{
		DB_UNKNOWN_TYPE = -1,
		DB_MYSQL = 0,
		DB_ORACLE,
		DB_SQLSERVER,
	};

	void init();

	namespace connpool
	{
		xdbc::XDBC_DB_TYPE GetDbType();
		size_t GetMaxConnSize();
		size_t GetConnTimeOut();
	}

	namespace db
	{
		string GetHost();
		string GetUser();
		string GetPwd();
		string GetDatabaseName();
	}
}


#endif // __XDBC_H__