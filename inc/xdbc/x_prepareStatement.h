#ifndef __X_PREPARESTATEMENT_H__
#define __X_PREPARESTATEMENT_H__

#include "x_statement.h"
#include "base/date.h"

class xPrepareStatement : public xStatement
{
public:
	xPrepareStatement()
	{
		
	}
	virtual ~xPrepareStatement()
	{
		
	}

	//binding input data for the parameter markers at specific position 
	//in the prepare statement with an integer.
	virtual void setInt(int index, const int &value)=0;
	
	//binding input data for the parameter markers at specific position 
	//in the prepare statement with a string.
	virtual void setString(int index, const string &paramValue)=0;
	
	//binding input data for the parameter markers at specific position 
	//in the prepare statement with date.
	virtual void setDate(int index, const Date &date)=0;
	
	//binding input data for the parameter markers at specific position 
	//in the prepare statement with datetime.
	virtual void setDateTime(int index, const Date &date)=0;
};

#endif