#ifndef __COREEXCEPTION_H__
#define __COREEXCEPTION_H__

#include "base/libdefs.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <string>
using std::string;

__WILLOW_BEGIN_NAMESPACE
class CoreException
{
public:
  virtual ~CoreException()throw();

  CoreException();

  CoreException(const string& message);

public:
  const string& getMessage() const;

protected:
  string str_detailMessage;

public:
  virtual const char*  getClassName() const;

private:
  const static char CLASS_NAME[];
};

__WILLOW_END_NAMESPACE

#endif