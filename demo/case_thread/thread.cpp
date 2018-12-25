#include "stdafx.h"

#include <iostream>
#include <pthread.h>

#include "xdbc/libxdbc.h"
#include "base/platform.h"


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
	dbConn.setInt(iPos++, 1);
	dbConn.setString(iPos++, "tom");
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

	//_Sleep(1000);
}


pthread_mutex_t g_lock;
int g_exceptionCount;
void lock()
{
	pthread_mutex_lock(&g_lock);
}

void unlock()
{
	pthread_mutex_unlock(&g_lock);
}

void recordCount()
{
	lock();
	g_exceptionCount++;
	unlock();
}

void* worker_thread(void *)
{
	try
	{
		case_query();
	}
	catch (CoreException ex)
	{
		recordCount();
		std::cout << ex.getMessage() << std::endl;
	}
	catch (...)
	{
		recordCount();
		std::cout << "未知异常" << std::endl;
	}

	XDBC_Sleep(0);
	return 0;
}

pthread_t create_worker()
{
	pthread_t work;
	pthread_create(&work, NULL, worker_thread, NULL);

	return work;
	
}

void* worker_thread2(void *)
{
	try
	{
		case_query();
	}
	catch (CoreException ex)
	{
		recordCount();
		std::cout << ex.getMessage() << std::endl;
	}
	catch (...)
	{
		recordCount();
		std::cout << "未知异常" << std::endl;
	}

	return 0;
}

pthread_t create_worker2()
{
	pthread_t work;
	pthread_create(&work, NULL, worker_thread2, NULL);

	return work;

}

int main(int argc, char* argv[])
{
	pthread_mutex_init(&g_lock,NULL);
	g_exceptionCount = 0;
	try
	{
		case_createTable();
		case_insert();
		case_update();
		for (int j = 0; j < 100; j++)
		{
			list<pthread_t> lstHandle;
			lstHandle.clear();
			for (int i = 0; i < 100; i++) //同时开的线程数应要小于数据库支持的连接数，不然会出现卡在mysql_ping语句上面，目前不知道原因为何
			{
				pthread_t work = create_worker();

#ifdef WIN32
				if (!work.p)
					continue;
#endif //WIN32

				lstHandle.push_back(work);
			}

			for (list<pthread_t>::iterator handle = lstHandle.begin(); handle != lstHandle.end(); handle++)
			{
				pthread_join(*handle, NULL);
			}
		}
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