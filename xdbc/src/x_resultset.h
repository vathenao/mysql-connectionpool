#ifndef __X_RESULTSET_H__
#define __X_RESULTSET_H__

#include <mysql.h>
#include <base/date.h>
#include "sqlException.h"


class xResultSet
{
public:
	virtual ~xResultSet(){}
	
public:
	/*
	**description£ºmoves the cursor to the next row from its current position
	**parameter£ºnone
	**return£ºif the new current row of resultset has data the function return true, otherwise it return false
	*/
	virtual bool next() DECL_THROW_EXCEPTION(SQLException)=0;
	
	/*
	** Description£ºreceives the value of the designated cloum in the current row 
	** of this resultset as a byte-data
	** Parameter: column index of current row , the first column is 1, the second is 2, ...
	** Return£ºreturn the column value
	*/
	virtual char getByte(size_t index) = 0;
	
	/*
	** Description£ºreceives the value of the designated cloum in the current row 
	** of this resultset as a short-data
	** Parameter: column index of current row , the first column is 1, the second is 2, ...
	** Return£ºreturn the column value
	*/
	virtual short getShort(size_t index) = 0;
	
	/*
	** Description£ºreceives the value of the designated cloum in the current row 
	** of this resultset as a internal-data
	** Parameter: column index of current row , the first column is 1, the second is 2, ...
	** Return£ºreturn the column value
	*/
	virtual int getInt(size_t index) = 0;
	
	/*
	** Description£ºreceives the value of the designated cloum in the current row 
	** of this resultset as a longlong-data
	** Parameter: column index of current row , the first column is 1, the second is 2, ...
	** Return£ºreturn the column value
	*/
	virtual long long getLong(size_t index) = 0;
	
	/*
	** Description£ºreceives the value of the designated cloum in the current row 
	** of this resultset as a float-data
	** Parameter: column index of current row , the first column is 1, the second is 2, ...
	** Return£ºreturn the column value
	*/
	virtual float getFloat(size_t index) = 0;
	
	/*
	** Description£ºreceives the value of the designated cloum in the current row 
	** of this resultset as a double-data
	** Parameter: column index of current row , the first column is 1, the second is 2, ...
	** Return£ºreturn the column value
	*/
	virtual double getDouble(size_t index) = 0;
	
	/*
	** Description£ºreceives the value of the designated cloum in the current row 
	** of this resultset as a string object
	** Parameter: column index of current row , the first column is 1, the second is 2, ...
	** Return£ºreturn the column value
	*/
	virtual string getString(size_t index) = 0;
	
	/*
	** Description£ºreceives the value of the designated cloum in the current row 
	** of this resultset as string object
	** Parameter: column index of current row , the first column is 1, the second is 2, ...
	** Return£ºreturn the column value
	*/
	virtual string getBlob(size_t index) = 0;
	
	/*
	** Description£ºreceives the value of the designated cloum in the current row 
	** of this resultset as Date those format like '2015/05/23'
	** Parameter: column index of current row , the first column is 1, the second is 2, ...
	** Return£ºreturn the column value
	*/
	virtual Date getDate(size_t index) = 0;
	
	/*
	** Description£ºreceives the value of the designated cloum in the current row 
	** of this resultset as Date those format like '17:27:30'
	** Parameter: column index of current row , the first column is 1, the second is 2, ...
	** Return£ºreturn the column value
	*/
	virtual Date getTime(size_t index) = 0;
	
	/*
	** Description£ºreceives the value of the designated cloum in the current row 
	** of this resultset as Date those format like '2015/05/23 17:27:30'
	** Parameter: column index of current row , the first column is 1, the second is 2, ...
	** Return£ºreturn the column value
	*/
	virtual Date getDateTime(size_t index) = 0;
	
	/*
	** Description£ºreceives the value of the designated cloum in the current row 
	** of this resultset as a timestamp
	** Parameter: column index of current row , the first column is 1, the second is 2, ...
	** Return£ºreturn the column value
	*/
	//virtual Date getTimestamp(int index)=0;
	
	
	
};

#endif