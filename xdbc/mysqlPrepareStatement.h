#ifndef __MYSQL_PREPARESTATEMENT_H__
#define __MYSQL_PREPARESTATEMENT_H__


#include "x_prepareStatement.h"
#include <vector>

class MysqlPrepareStatement:public xPrepareStatement
{
public:
	MysqlPrepareStatement(MYSQL *mysql, const string &sPerpareStr);
	~MysqlPrepareStatement();
	
	/*
	**<D>:executes the given sql statement.
	**<P>:none
	**<R>:number of rows change,delete,or insert by the statement if it was a update,delete,or insert.
	*/
	int executeUpdate(const string &runSql) DECL_THROW_EXCEPTION(SQLException);
	
	/*
	**<D>:execute the given sql statement.
	**<P>:none
	**<R>:return a pointer to the result set in which the results returned by SELECT or SELECT like SQL statement stored
	**remark:A instance of MysqlResultSet class will be created after calling this function by using new operator,in this case,
	**corresponding delete operator must be call by the invoker.
	*/
	xResultSet* executeQuery(const string &runSql) DECL_THROW_EXCEPTION(SQLException);
	
	/*
	**<D>: Binding input data for the parameter markers at specific position in the prepare statement with string.
	**<P>index:the designated offset of markers(?) in the prepare statement.The first marker in the statement is offset 1. 
	**<R>None
	*/
	void setInt(int index, const int &value);
	
	/*
	**<D>: Binding input data for the parameter markers at specific position in the prepare statement with string.
	**<P>index:the designated offset of markers(?) in the prepare statement.The first marker in the statement is offset 1. 
	**<R>None
	*/
	void setString(int index, const string &paramValue);
	
	/*
	**<D>: Binding input data for the parameter markers at specific position in the prepare statement with date.
	**<P>index:the designated offset of markers(?) in the prepare statement.The first marker in the statement is offset 1. 
	**<R>None
	**remark:This function binds the C variable to the prepare statement whit MYSQL_TYPE_DATE type.
	**so, when data describes by datetime-structure was bound to a prepare statement, the time part of it would be lost.
	**Because of this, to bound a complete datatime-structure variable to a prepare statement, you should use the setDateTime function 
	**instead of setDate fucntion.
	*/
	void setDate(int index, const Date &date);
	
	/*
	**<D>: Binding input data for the parameter markers at specific position in the prepare statement with datetime.
	**<P>index:the designated offset of markers(?) in the prepare statement.The first marker in the statement is offset 1. 
	**<R>None
	*/
	void setDateTime(int index, const Date &date);
	
private:
	
	//Prepare the query string for query operatoin.
	void prepareStatement();
	
	//Shields the copy constructor and the assignment operator
	MysqlPrepareStatement &operator=(const MysqlPrepareStatement &mysqlprepar){}
	MysqlPrepareStatement(const MysqlPrepareStatement& mysqlprepar){}
	
	
	
private:
	string m_sPrepareStr;
	MYSQL_STMT* m_pStmt;
	MYSQL_BIND m_bind;	//The prepare Statement has no parameters that marks with '?', in which case m_bind use for parameter of mysql_stmt_param_bind(); 
	vector<MYSQL_BIND> m_vecBind;	//vector that stores the MYSQL_BIND use for binding parameters.	
	int m_paramCount;
	
	MYSQL_BIND m_bindarray[1];
};

#endif