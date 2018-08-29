#include "mysqlResultSet.h"


MysqlResultSet::MysqlResultSet(MYSQL_STMT* stmt):m_pStmt(stmt),m_pResMeta(NULL)
{
	BindResultSet(m_vecBind);
}

MysqlResultSet::~MysqlResultSet()
{	
	for( size_t i = 1; i < m_vecBind.size(); i++ )
	{
		if( m_vecBind[i].buffer )
		{
			free(m_vecBind[i].buffer);
			m_vecBind[i].buffer = NULL;
		}
	}
	
	//free the prepared result metadata
	if( m_pResMeta )
	{
		mysql_free_result(m_pResMeta);
		m_pResMeta = NULL;
	}
}

bool MysqlResultSet::next() DECL_THROW_EXCEPTION(SQLException)
{
	int iRet = mysql_stmt_fetch( m_pStmt );
	
	if(0 == iRet)
	{
		return true;
	}
	else if(1 == iRet)
	{
		char errmsg[256];
		snprintf(errmsg, 250, "database error:%d:%s!", 
		mysql_stmt_errno(m_pStmt), mysql_stmt_error(m_pStmt));
		
		throw SQLException(errmsg);
	}
	else if(MYSQL_NO_DATA == iRet)
	{
		return false;
	}
	else if(MYSQL_DATA_TRUNCATED == iRet)
	{
		char errmsg[256];
		snprintf(errmsg, 250, "MYSQL_DATA_TRUNCATED!");
		throw SQLException(errmsg);
	}
	
	string errormsg = "other database error: ";
	errormsg.append(mysql_stmt_error(m_pStmt));
	throw SQLException(errormsg);
}

char MysqlResultSet::getByte(int index)
{
	if( index <= 0 || index > m_vecBind.size() )
	{
		char errmsg[129];
		snprintf(errmsg, 128, "getInt: Index[%d] of binding param is out of range, not in range(1~%d)", 
		index, m_vecBind.size()-1);
		throw SQLException(errmsg);
	}
	
	if( is_null[index-1] )
	{
		return 0;
	}
	
	char ch = *(char *)m_vecBind[index-1].buffer;
	
	return ch;
}

short MysqlResultSet::getShort(int index)
{
	return getLong(index);
}

int MysqlResultSet::getInt(int index)
{
	return getLong(index);
}

LONG_LONG MysqlResultSet::getLong(int index)
{
	if( index <= 0 || index > m_vecBind.size() )
	{
		char errmsg[129];
		snprintf(errmsg, 128, "getInt: Index[%d] of binding param is out of range, not in range(1~%d)", 
		index, m_vecBind.size()-1);
		throw SQLException(errmsg);
	}
	
	if( is_null[index-1] )
	{
		return 0;
	}
	
	return *(int *)m_vecBind[index-1].buffer;
}

float MysqlResultSet::getFloat(int index)
{
	return getDouble(index);
}

double MysqlResultSet::getDouble(int index)
{
	if( index <= 0 || index > m_vecBind.size() )
	{
		char errmsg[129];
		snprintf(errmsg, 128, "getInt: Index[%d] of binding param is out of range, not in range(1~%d)", 
		index, m_vecBind.size()-1);
		throw SQLException(errmsg);
	}
	
	if( is_null[index-1] )
	{
		return 0;
	}
	
	return *(double *)m_vecBind[index-1].buffer;
}

//The first column is numbered 1,offset is the offset within the data value at which to begin retrieving data
//The beginning of the value is offset 1.
string MysqlResultSet::getString(int index)
{
	if( index <= 0 || index > m_vecBind.size() )
	{
		char errmsg[129];
		snprintf(errmsg, 128, "getString: Index[%d] of binding param is out of range,not in range(0~%d)", 
		index, m_vecBind.size()-1);
		throw SQLException(errmsg);
	}
	
	if( is_null[index-1] )
	{
		cout << "clumn is null" << endl;
		return 0;
	}
	
	string str = (char *)m_vecBind[index-1].buffer;
	return str;
}

string MysqlResultSet::getBlob(int index)
{
	return getString(index);
}

Date MysqlResultSet::getDate(int index)
{
	Date date = getDateTime(index);
	date.setHours(0);
	date.setMinutes(0);
	date.setSeconds(0);
	return date;
}

Date MysqlResultSet::getTime(int index)
{
	return Date(1990,01,01,00,00,00);
}

Date MysqlResultSet::getDateTime(int index)
{
	if( index <= 0 || index > m_vecBind.size() )
	{
		char errmsg[129];
		snprintf(errmsg, 128, "getString: Index[%d] of binding param is out of range,not in range(0~%d)", 
		index, m_vecBind.size()-1);
		throw SQLException(errmsg);
	}
	
	if( is_null[index-1] )
	{
		cout << "clumn is null" << endl;
		return 0;
	}
	
	MYSQL_TIME *ts = (MYSQL_TIME*)m_vecBind[index-1].buffer;
	return Date(ts->year, ts->month, ts->day, ts->hour, ts->minute, ts->second);
}

void MysqlResultSet::BindResultSet(vector<MYSQL_BIND> &vecBind)
{
	vecBind.clear();
	m_pResMeta = mysql_stmt_result_metadata(m_pStmt);
	if( !m_pResMeta )
	{
		string errmsg="The results return by MYSQL is NULL,if the query string you had given is a SQL statement of UPDATE,DELETE,"
		"or any other without result set memadate, please try to use the executeUpdate method for preforming it.";
		throw SQLException(errmsg);
	}
	
	if( mysql_num_fields(m_pResMeta) > VTH_MAX_FEILD )
	{
		char errmsg[512];
		snprintf(errmsg, 500, "The number of columns in a result set is too large(large clumns is %d)."
		"You have to increase the value of VTH_MAX_FEILD", VTH_MAX_FEILD);
		throw SQLException(errmsg);
	}
	
	int index = 0;
	MYSQL_FIELD *field;
	MYSQL_BIND bind;
	while(field = mysql_fetch_field(m_pResMeta))
	{
		
		bind.buffer_type = field->type;
		bind.is_null= &is_null[index];
		bind.length= &length[index];
		bind.error= &error[index];
		
		if( field->type == MYSQL_TYPE_LONG
			|| field->type == MYSQL_TYPE_INT24
			|| field->type == MYSQL_TYPE_SHORT
			|| field->type == MYSQL_TYPE_LONGLONG )
		{
			
			bind.buffer = malloc(sizeof(LONG_LONG));
			bind.buffer_length = 0;
		}
		else if(field->type == MYSQL_TYPE_TINY)
		{
			bind.buffer_type = field->type;
			bind.buffer = malloc(sizeof(char));
			bind.buffer_length = 1;
		}
		else if( field->type == MYSQL_TYPE_STRING
			|| field->type == MYSQL_TYPE_VAR_STRING
			|| field->type == MYSQL_TYPE_NEWDECIMAL
			|| field->type == MYSQL_TYPE_TINY_BLOB
			|| field->type == MYSQL_TYPE_BLOB
			|| field->type == MYSQL_TYPE_MEDIUM_BLOB
			|| field->type == MYSQL_TYPE_LONG_BLOB
			|| field->type == MYSQL_TYPE_BIT )
		{
			bind.buffer = malloc(VTH_MAX_CHAR_SIZE*sizeof(char));
			bind.buffer_length = VTH_MAX_CHAR_SIZE-1;
		}
		else if( field->type == MYSQL_TYPE_TIME
			|| field->type == MYSQL_TYPE_DATE
			|| field->type == MYSQL_TYPE_DATETIME
			|| field->type == MYSQL_TYPE_TIMESTAMP)
		{
			bind.buffer = malloc(sizeof(MYSQL_TIME));
			bind.buffer_length = 0;
		}
		else if( field->type == MYSQL_TYPE_FLOAT
			|| field->type == MYSQL_TYPE_DOUBLE)
		{
			bind.buffer = malloc(sizeof(double));
			bind.buffer_length = 0;
		}
		else
		{
			bind.buffer_type = MYSQL_TYPE_VAR_STRING;
			bind.buffer = malloc(VTH_MAX_CHAR_SIZE*sizeof(char));
			bind.buffer_length = VTH_MAX_CHAR_SIZE-1;
		}
		
		vecBind.push_back(bind);
		index++;
	}
	
	if(mysql_stmt_bind_result(m_pStmt, &vecBind[0]))
	{
		string errmsg = "mysql_stmt_bind_result failed.";
		errmsg.append(mysql_stmt_error(m_pStmt));
		throw SQLException(errmsg);
	}
}

