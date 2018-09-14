#include "stdafx.h"
#include "xdbc/libxdbc.h"
#include <iostream>

void insert2Table()
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

void queryFromTable()
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
		insert2Table();
		queryFromTable();
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