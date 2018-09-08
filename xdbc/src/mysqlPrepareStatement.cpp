#include "stdafx.h"
#include "mysqlPrepareStatement.h"
#include "mysqlResultSet.h"

MysqlPrepareStatement::MysqlPrepareStatement(MYSQL *mysql, const string &sPerpareStr):m_pStmt(NULL),m_sPrepareStr(sPerpareStr),m_paramCount(0)
{
	this->m_vecBind.clear();
	
	//create a MYSQL_STMT handle
	this->m_pStmt = mysql_stmt_init(mysql);
	if( !this->m_pStmt )
	{
		throw SQLException("An error(out of memory)  was occured when creating a handle of MYSQL_STMT.");
	}
	
	prepareStatement();
	m_paramCount = mysql_stmt_param_count(m_pStmt);
}

MysqlPrepareStatement::~MysqlPrepareStatement()
{
	if( this->m_pStmt )
	{
		mysql_stmt_close(this->m_pStmt);
		this->m_pStmt = NULL;
	}
	
	for( size_t iBind = 0; iBind < m_vecBind.size(); iBind++ )
	{
		free(m_vecBind[iBind].buffer);
		m_vecBind[iBind].buffer = NULL;
		
		if( MYSQL_TYPE_STRING == m_vecBind[iBind].buffer_type )
		{
			free(m_vecBind[iBind].length);
			m_vecBind[iBind].length = NULL;
		}
	}
	
	m_vecBind.clear();
}

int MysqlPrepareStatement::executeUpdate(const string &runSql) DECL_THROW_EXCEPTION(SQLException)
{
	if( m_paramCount != m_vecBind.size() )
	{
		throw SQLException("Bind paramenters,Invalid parameter count returned by MySQL.");
	}
	
	if( m_paramCount > 0 )
	{
		if( 0 != mysql_stmt_bind_param(m_pStmt, &m_vecBind[0] ) ) /*&m_vecBind[0]*/
		{
			string errmsg;
			errmsg.append("mysql_stmt_bind_param faild,");
			errmsg.append(mysql_stmt_error(m_pStmt));
			errmsg.append(". error sql: ");
			errmsg.append(m_sPrepareStr);
			throw SQLException(errmsg);
		}
		
	}
	else if(m_paramCount == 0)
	{
		if( 0 != mysql_stmt_bind_param(m_pStmt, &m_bind) )
		{
			string errmsg;
			errmsg.append("mysql_stmt_bind_param faild,");
			errmsg.append(mysql_stmt_error(m_pStmt));
			errmsg.append(". error sql: ");
			errmsg.append(m_sPrepareStr);
			throw SQLException(errmsg);
		}
	}
	else
	{
		throw SQLException("invalid count of binding paramenters.");
	}
	
	if( 0 != mysql_stmt_execute(m_pStmt) )
	{
		string errmsg;
		errmsg.append("mysql_stmt_bind_param faild,");
		errmsg.append(mysql_stmt_error(m_pStmt));
		errmsg.append(". error sql: ");
		errmsg.append(m_sPrepareStr);
		throw SQLException(errmsg);
	}
	
	return (int)mysql_stmt_affected_rows(m_pStmt);
	
}

xResultSet* MysqlPrepareStatement::executeQuery(const string &runSql) DECL_THROW_EXCEPTION(SQLException)
{	
	if( m_paramCount != m_vecBind.size() )
	{
		throw SQLException("Bind paramenters,Invalid parameter count returned by MySQL.");
	}
	
	if( m_paramCount > 0 )
	{
		if( 0 != mysql_stmt_bind_param(m_pStmt, &m_vecBind[0]) )
		{
			string errmsg;
			errmsg.append("mysql_stmt_bind_param faild,");
			errmsg.append(mysql_stmt_error(m_pStmt));
			errmsg.append(". error sql: ");
			errmsg.append(m_sPrepareStr);
			throw SQLException(errmsg);
		}
	}
	else if(m_paramCount == 0)
	{
		if( 0 != mysql_stmt_bind_param(m_pStmt, &m_bind) )
		{
			string errmsg;
			errmsg.append("mysql_stmt_bind_param faild,");
			errmsg.append(mysql_stmt_error(m_pStmt));
			errmsg.append(". error sql: ");
			errmsg.append(m_sPrepareStr);
			throw SQLException(errmsg);
		}
	}
	else
	{
		throw SQLException("invalid count of binding paramenters.");
	}
	
	if( 0 != mysql_stmt_execute(m_pStmt) )
	{
		string errmsg;
		errmsg.append("mysql_stmt_bind_param faild,");
		errmsg.append(mysql_stmt_error(m_pStmt));
		errmsg.append(". error sql: ");
		errmsg.append(m_sPrepareStr);
		throw SQLException(errmsg);
	}
	
	return new MysqlResultSet(m_pStmt);
}

/*
**<D>:Prepare SQL statement for querying
**<P>:None
**<R>:None
*/
void MysqlPrepareStatement::prepareStatement()
{
	if( !this->m_pStmt )
	{
		throw SQLException("Prepare SQL statement befor geting the MYSQL_STMT handle.");
	}
	
	int iRet = mysql_stmt_prepare(m_pStmt, m_sPrepareStr.c_str(), m_sPrepareStr.length());
	if( iRet != 0 )
	{
		string errmsg;
		errmsg.append("Prepare SQL statement fail,");
		errmsg.append(mysql_stmt_error(m_pStmt));
		errmsg.append(". error sql: ");
		errmsg.append(m_sPrepareStr);
		throw SQLException(errmsg);
	}
}

/*
**<D>:Binding input data for the parameter markers at specific position in the SQL statement 
**that was passed to mysql_stmt_prepare() with an integer.
**<P>index:Position of parameter markers in the SQL statement
**<P>value:Value that is used to bound to the parameter markers is specified by index
**<R>:None
**remark:The index paramter indexe from 1
*/
void MysqlPrepareStatement::setInt(size_t index, const int &value)
{
	if( index == 0 || index > m_paramCount )
	{
		char errmsg[65];
		snprintf(errmsg, 64, "Index[%d] of binding param is out of range,not in range(1~%d)", index, m_paramCount);
		throw SQLException(errmsg);
	}
	
	MYSQL_BIND bind;	
	bind.buffer_type = MYSQL_TYPE_LONG;
	bind.is_null = (my_bool*)0;
	bind.length = 0;
	bind.buffer = malloc(sizeof(long));
	
	*(int *)bind.buffer = value;
	m_vecBind.push_back(bind);
}

/*
**<D>:Binding input data for the parameter markers at specific position in the SQL statement 
**that was passed to mysql_stmt_prepare() with a string.
**<P>index:Position of parameter markers in the SQL statement
**<P>value:Value that is used to bound to the parameter markers is specified by index
**<R>:None
**remark:The index paramter indexe from 1
*/
void MysqlPrepareStatement::setString(size_t index, const string &value)
{
	if( index == 0 || index > m_paramCount )
	{
		char errmsg[65];
		snprintf(errmsg, 64, "Index[%d] of binding param is out of range,not in range(1~%d)", 
		index, m_paramCount);
		throw SQLException(errmsg);
	}
	
	MYSQL_BIND bind;
	bind.buffer_type= MYSQL_TYPE_STRING;
	bind.is_null = (my_bool*)0;
	bind.length = (unsigned long *)malloc(sizeof(unsigned long));
	bind.buffer = malloc(value.length()*sizeof(char) + 1);
	
	*(unsigned long *)bind.length = value.length();
	strcpy( (char *)bind.buffer, value.c_str() );
	
	m_vecBind.push_back(bind);
}

void MysqlPrepareStatement::setDate(size_t index, const Date &date)
{	
	if( index == 0 || index > m_paramCount )
	{
		char errmsg[65];
		snprintf(errmsg, 64, "Index[%d] of binding param is out of range,not in range(1~%d)", 
		index, m_paramCount);
		throw SQLException(errmsg);
	}
	
	MYSQL_TIME *ts = (MYSQL_TIME *)malloc(sizeof(MYSQL_TIME));
	ts->year = date.getYear();
	ts->month = date.getMonth();
	ts->day = date.getDay();
	
	ts->hour = date.getHours();
	ts->minute = date.getMinutes();
	ts->second = date.getSeconds();
	
	MYSQL_BIND bind;
	bind.buffer_type= MYSQL_TYPE_DATE;
	bind.buffer = (char *)ts;
	bind.is_null = (my_bool*)0;
	bind.length = 0;
	
	m_vecBind.push_back(bind);
	
}

void MysqlPrepareStatement::setDateTime(size_t index, const Date &date)
{	
	if( index == 0 || index > m_paramCount )
	{
		char errmsg[65];
		snprintf(errmsg, 64, "Index[%d] of binding param is out of range,not in range(1~%d)", 
		index, m_paramCount);
		throw SQLException(errmsg);
	}
	
	//string dateStr = date.Format("%Y-%m-%d %H:%M:%S");
	string dateStr = date.Format("%F %T");
	setString(index, dateStr);
	
	/*MYSQL_BIND bind;
	bind.buffer_type= MYSQL_TYPE_DATETIME;
	bind.is_null = (my_bool*)0;
	bind.length = 0;
	bind.buffer = (char *)malloc(sizeof(MYSQL_TIME));
	
	MYSQL_TIME *ts = (MYSQL_TIME *)bind.buffer;
	ts->year = date.getYear();
	ts->month = date.getMonth();
	ts->day = date.getDay();
	
	ts->hour = date.getHours();
	ts->minute = date.getMinutes();
	ts->second = date.getSeconds();
	
	m_vecBind.push_back(bind);*/
}