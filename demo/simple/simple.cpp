#include "stdafx.h"
#include "xdbc/libxdbc.h"
#include <iostream>

void case_createTable()
{
	string sqlStr = "DROP TABLE IF EXISTS tb_test";

	DbConnect dbConn;
	dbConn.SetSqlText(sqlStr);
	dbConn.executeUpdate();

	sqlStr = "CREATE TABLE tb_test ("
		"id int(10) unsigned NOT NULL,"
		"name varchar(65) NOT NULL,"
		"address varchar(129) NOT NULL,"
		"createtime datetime NOT NULL,"
		"PRIMARY KEY(id)"
		") ENGINE = InnoDB DEFAULT CHARSET = latin1";
	dbConn.SetSqlText(sqlStr);
	dbConn.executeUpdate();
	std::cout << "create table success" << std::endl;
}

void case_delete()
{
	string sqlStr = "delete from tb_test where id in(?,?)";

	DbConnect dbConn;
	dbConn.SetSqlText(sqlStr);

	int iPos = 1;
	dbConn.setInt(iPos++, 1);
	dbConn.setInt(iPos++, 2);

	if (dbConn.executeUpdate() < 1)
	{
		//delete failed,if you catch the exception with SQLException,this may not be output because of 
		//executeUpdate function will throw the SQLException exception
		std::cout << "delete failed" << std::endl;
	}
}

void case_insert()
{
	string strSql = "insert into tb_test(id, name,createtime,address) values(?,?,now(),?)";

	DbConnect dbConn;
	dbConn.SetSqlText(strSql);

	int iPos = 1;
	dbConn.setInt(iPos++,1);
	dbConn.setString(iPos++,"tom");
	dbConn.setString(iPos++, "GuangDong China");

	if (1 != dbConn.executeUpdate())
	{
		//insert failed,if you catch the exception with SQLException,this may not be output because of 
		//executeUpdate function will throw the SQLException exception
		std::cout << "insert failed with name tom" << std::endl;
	}

	dbConn.SetSqlText(strSql);

	iPos = 1;
	dbConn.setInt(iPos++, 2);
	dbConn.setString(iPos++, "smith");
	dbConn.setString(iPos++, "BeiJing China");
	if (1 != dbConn.executeUpdate())
	{
		std::cout << "insert failed with name smith" << std::endl;
	}
}

void case_update()
{
	string sqlStr = "update tb_test t set t.address = ? where name = ?";

	DbConnect dbConn;
	dbConn.SetSqlText(sqlStr);

	int iPos = 1;
	dbConn.setString(iPos++, "WuHan China");
	dbConn.setString(iPos++, "tom");

	if (dbConn.executeUpdate() < 1)
	{
		//update failed,if you catch the exception with SQLException,this may not be output because of 
		//executeUpdate function will throw the SQLException exception
		std::cout << "update failed." << std::endl;
	}
}

void case_query()
{
	string sqlStr = "select id, name,createtime,address from tb_test where name in(?,?)";

	DbConnect dbConn;
	dbConn.SetSqlText(sqlStr);

	int iPos = 1;
	dbConn.setString(iPos++, "tom");
	dbConn.setString(iPos++, "smith");

	dbConn.executeQuery();
	while (dbConn.next())
	{
		iPos = 1;
		cout << "id: " << dbConn.getInt(iPos++) << endl;
		cout << "name: " << dbConn.getString(iPos++) << endl;
		cout << "createtime: " << dbConn.getDateTime(iPos++).toString() << endl;
		cout << "address: " << dbConn.getString(iPos++) << endl;
	}
}


int main(int argc, char* argv[])
{
	try
	{
		case_createTable();
		case_insert();
		case_update();

		cout << "query before delete" << endl;
		case_query();
		case_delete();

		cout << "query after delete" << endl;
		case_query();
	}
	catch (SQLException ex)
	{
		cout << ex.getMessage() << endl;
	}
	catch (CoreException ex)
	{
		cout << ex.getMessage() << endl;
	}
	catch (...)
	{
		cout << "other exception" << endl;
	}

	system("pause");
}