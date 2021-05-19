#ifndef __CONNPOOL_EXCEPTION_H__
#define __CONNPOOL_EXCEPTION_H__

#include "global.h"
#include "base/exception.h"

class XDBC_EXPORT ConnpollException: public CBaseException
{
public:
	ConnpollException();
	ConnpollException(const string &message);
	ConnpollException(const string &message, const string& SQLState);
	ConnpollException(const string& message,LONG_LONG vendorCode);
	ConnpollException(const string& message,const string& SQLState,LONG_LONG vendorCode);
	
	virtual ~ConnpollException()throw();
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