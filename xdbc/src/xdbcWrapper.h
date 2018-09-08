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
	char getByte(size_t index);
	short getShort(size_t index);
	int getInt(size_t index);
	LONG_LONG getLong(size_t index);
	float getFloat(size_t index);
	double getDouble(size_t index);
	string getString(size_t index);
	string getBlob(size_t index);
	Date getDate(size_t index);
	Date getTime(size_t index);
	Date getDateTime(size_t index);
	
private:
	xResultSet *m_rs;
};

#endif


