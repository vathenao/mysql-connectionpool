#ifndef __X_SQLEXCEPTION_H__
#define __X_SQLEXCEPTION_H__

#include "base/CoreException.h"

__USING_WILLOW_NS

class SQLException: public CoreException
{
public:
	SQLException();
	SQLException(const string &message);
	SQLException(const string &message, const string& SQLState);
	SQLException(const string& message,LONG_LONG vendorCode);
	SQLException(const string& message,const string& SQLState,LONG_LONG vendorCode);
	
	virtual ~SQLException()throw();
	virtual const char*  getClassName() const;
	LONG_LONG     getVendorCode() const;
	LONG_LONG     getErrorCode() const;
	const string& getSQLState() const;
	
private:
	const static char CLASS_NAME[];
	LONG_LONG     long_vendorCode;
	string        str_SQLState;
	
};

#endif