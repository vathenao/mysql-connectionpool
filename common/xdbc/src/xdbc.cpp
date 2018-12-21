#include "stdafx.h"
#include "global.h"
#include "xdbc.h"
#include "sqlException.h"

#include <base/configHelper.h>

namespace xdbc
{
	VConfigHelper g_configHelper;
	bool g_inited = false;

	void init()
	{
		if (g_inited)
			return;

		string defaultFileName;
		defaultFileName.append(XDBC_CFG_PATH);
		defaultFileName.append("/xdbc.cfg");
		g_configHelper.ReLoad(defaultFileName);

		g_inited = true;
	}
}

xdbc::XDBC_DB_TYPE xdbc::connpool::GetDbType()
{
	xdbc::init();
	
	XDBC_DB_TYPE type = DB_UNKNOWN_TYPE;
	if (type != DB_UNKNOWN_TYPE)
		return type;

	string result;
	if (!g_configHelper.GetConfigStringValue("ConnPoolConf", "DBTYPE", result))
		throw SQLException(g_configHelper.GetLastErrorMsg());
	
	if (result == "MYSQL")
	{
		type = DB_MYSQL;
	}
	else if (result == "ORACLE")
	{
		type = DB_ORACLE;
	}
	else if (result == "SQLSERVER")
	{
		type = DB_SQLSERVER;
	}
	
	return type;
}

size_t xdbc::connpool::GetMaxConnSize()
{
	xdbc::init();
	static int result = -1;
	if (result != -1)
		return result;

	if (!g_configHelper.GetConfigIntValue("ConnPoolConf", "MAXCONNSIZE", result))
	{
		//handler error
		throw SQLException(g_configHelper.GetLastErrorMsg());
	}

	return static_cast<size_t>(result);
}

size_t xdbc::connpool::GetConnTimeOut()
{
	xdbc::init();
	static int result = -1;
	if (result != -1)
		return result;

	if (!g_configHelper.GetConfigIntValue("ConnPoolConf", "TIMEOUT", result))
	{
		//handler error
		throw SQLException(g_configHelper.GetLastErrorMsg());
	}

	return static_cast<size_t>(result);
}

string xdbc::db::GetHost()
{
	xdbc::init();
	static string result;
	if (!result.empty())
		return result;

	if (!g_configHelper.GetConfigStringValue("ConnInfo", "HOST", result))
	{
		//handler error
		throw SQLException(g_configHelper.GetLastErrorMsg());
	}

	return result;
}

string xdbc::db::GetUser()
{
	xdbc::init();
	static string result;
	if (!result.empty())
		return result;

	if (!g_configHelper.GetConfigStringValue("ConnInfo", "USER", result))
	{
		//handler error
		throw SQLException(g_configHelper.GetLastErrorMsg());
	}

	return result;
}

string xdbc::db::GetPwd()
{
	xdbc::init();
	static string result;
	if (!result.empty())
		return result;

	if (!g_configHelper.GetConfigStringValue("ConnInfo", "PASSWD", result))
	{
		//handler error
		throw SQLException(g_configHelper.GetLastErrorMsg());
	}

	return result;
}

string xdbc::db::GetDatabaseName()
{
	xdbc::init();
	static string result;
	if (!result.empty())
		return result;

	if (!g_configHelper.GetConfigStringValue("ConnInfo", "DATABASE", result))
	{
		//handler error
		throw SQLException(g_configHelper.GetLastErrorMsg());
	}

	return result;
}
