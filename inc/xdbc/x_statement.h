#ifndef __X_STATEMENT_H__
#define __X_STATEMENT_H__

#include <mysql.h>
#include "sqlException.h"
#include "x_resultset.h"
__USING_WILLOW_NS

/*
* Class declares interfaces for performing SQL statement.
*
* In general,functions you add to this class should be pure virtual functions.
*
*/
class xStatement
{
public:
	virtual ~xStatement()
	{
		
	}
	
	/*
	**<D>：executes the given sql statement.
	**<P>：none
	**<R>：number of rows change,delete,or insert by the statement if it was a update,delete,or insert.
	*/
	virtual int executeUpdate(const string &runSql) DECL_THROW_EXCEPTION(SQLException)=0;
	
	/*
	**<D>:execute the given sql statement.
	**<P>runSql:query statement
	**<R>:return a pointer to the result set in which the results returned by SELECT or SELECT like SQL statement stored
	**remark:A instance of a class Derived by xResultSet will be created in this function by using new operator,in this case,
	**corresponding delete operator must be call by the invoker after calling it.
	*/
	virtual xResultSet* executeQuery(const string &runSql) DECL_THROW_EXCEPTION(SQLException) = 0;

};

#endif