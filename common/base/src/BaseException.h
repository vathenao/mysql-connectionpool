#ifndef __BASE_EXCEPTION_H__
#define __BASE_EXCEPTION_H__

#include "CoreException.h"
 
__WILLOW_BEGIN_NAMESPACE

class BASE_EXPORT CBaseException : public CoreException
{
public:
	CBaseException();
	CBaseException(const string& message);	
	CBaseException(const char *fmt,...) ;
	virtual ~CBaseException()throw();

public:
	virtual const char*  getClassName() const;

private:
	const static char CLASS_NAME[];
};

__WILLOW_END_NAMESPACE


#endif
