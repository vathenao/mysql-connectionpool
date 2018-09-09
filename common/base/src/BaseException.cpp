#include "stdafx.h"
#include "BaseException.h"

__WILLOW_BEGIN_NAMESPACE

const char CBaseException::CLASS_NAME[] = "CBaseException";
const char* CBaseException::getClassName() const
{
	return  CBaseException::CLASS_NAME;
}

CBaseException::CBaseException():CoreException()
{
}

CBaseException::CBaseException(const string& message):CoreException(message)
{
}

CBaseException::CBaseException(const char*fmt,...)
{
	char errcause_[4096] ;
	errcause_[4096-1] = 0;
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(errcause_, sizeof(errcause_)-1, fmt, ap);
	va_end(ap);
	str_detailMessage = errcause_ ;
}

CBaseException::~CBaseException()throw()
{
}

__WILLOW_END_NAMESPACE
