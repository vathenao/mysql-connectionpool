#ifndef __XDBC_WRAPPER_H__
#define __XDBC_WRAPPER_H__

#include "x_prepareStatement.h"
#include "x_resultset.h"
#include "sqlException.h"

class xStmtWrapper
{
public:
	xStmtWrapper(xPrepareStatement* pStmt = NULL,const string &runSql="") DECL_THROW_EXCEPTION(SQLException);
	~xStmtWrapper();
	
	
	void ReSet(xPrepareStatement* pStmt = NULL,const string &runSql="");
	int executeUpdate() DECL_THROW_EXCEPTION(SQLException);
	xResultSet * executeQuery() DECL_THROW_EXCEPTION(SQLException);
	
	void setInt(int index, const int &value);
	void setString(int index, const string &paramValue);
	void setDate(int index, const Date &date);
	void setDateTime(int index, const Date &date);
	
private:
	xStmtWrapper(const xStmtWrapper &stmtWrapper){}
	xStmtWrapper &operator=(const xStmtWrapper &stmtWrapper){}
	
private:
	xPrepareStatement *m_pStmt;
	string m_runSql;
};


class xRsWrapper
{
public:
	xRsWrapper(xResultSet * rs = NULL);
	~xRsWrapper();
	
	void ReSet(xResultSet * rs = NULL);
	bool next() DECL_THROW_EXCEPTION(SQLException);
	char getByte(int index);
	short getShort(int index);
	int getInt(int index);
	LONG_LONG getLong(int index);
	float getFloat(int index);
	double getDouble(int index);
	string getString(int index);
	string getBlob(int index);
	Date getDate(int index);
	Date getTime(int index);
	Date getDateTime(int index);
	
private:
	xResultSet *m_rs;
};

#endif


