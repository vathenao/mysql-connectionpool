#include "stdafx.h"
#include "sqlException.h"

const char SQLException::CLASS_NAME[] = "SQLException";
const char* SQLException::getClassName() const
{
  return  SQLException::CLASS_NAME;
}

SQLException::SQLException()
	: CBaseException()
	, long_vendorCode(0)
{
}

SQLException::SQLException(const string& message)
	: CBaseException(message)
	, long_vendorCode(0)
{
}

SQLException::SQLException(const string& message,const string& SQLState)
	: CBaseException(message)
	, str_SQLState(SQLState)
	, long_vendorCode(0)
{
}

SQLException::SQLException(const string& message,LONG_LONG vendorCode)
	: CBaseException(message)
	, long_vendorCode(vendorCode)
{
}

SQLException::SQLException(const string& message,const string& SQLState,LONG_LONG vendorCode)
	: CBaseException(message)
	, str_SQLState(SQLState)
	, long_vendorCode(vendorCode)
{
}
  
LONG_LONG SQLException::getVendorCode() const
{
  return long_vendorCode;
}

LONG_LONG SQLException::getErrorCode() const
{
  return long_vendorCode;
}

const string& SQLException::getSQLState() const
{
  return str_SQLState;
}

SQLException::~SQLException()throw()
{
}