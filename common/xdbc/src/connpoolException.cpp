#include "stdafx.h"
#include "connpoolException.h"

const char ConnpollException::CLASS_NAME[] = "ConnpollException";
const char* ConnpollException::getClassName() const
{
  return  ConnpollException::CLASS_NAME;
}

ConnpollException::ConnpollException()
	: CBaseException()
	, long_vendorCode(0)
{
}

ConnpollException::ConnpollException(const string& message)
	: CBaseException(message)
	, long_vendorCode(0)
{
}

ConnpollException::ConnpollException(const string& message,const string& SQLState)
	: CBaseException(message)
	, str_SQLState(SQLState)
	, long_vendorCode(0)
{
}

ConnpollException::ConnpollException(const string& message,LONG_LONG vendorCode)
	: CBaseException(message)
	, long_vendorCode(vendorCode)
{
}

ConnpollException::ConnpollException(const string& message,const string& SQLState,LONG_LONG vendorCode)
	: CBaseException(message)
	, str_SQLState(SQLState)
	, long_vendorCode(vendorCode)
{
}
  
LONG_LONG ConnpollException::getVendorCode() const
{
  return long_vendorCode;
}

LONG_LONG ConnpollException::getErrorCode() const
{
  return long_vendorCode;
}

const string& ConnpollException::getSQLState() const
{
  return str_SQLState;
}

ConnpollException::~ConnpollException()throw()
{
}