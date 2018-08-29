#include "stdafx.h"
#include "CoreException.h"

__WILLOW_BEGIN_NAMESPACE
const char CoreException::CLASS_NAME[] = "CoreException";
const char* CoreException::getClassName() const
{
  return  CoreException::CLASS_NAME;
}

CoreException::~CoreException()throw()
{

}

CoreException::CoreException()
{

}

CoreException::CoreException(const string& message):str_detailMessage(message)
{

}

const string& CoreException::getMessage() const
{
  return str_detailMessage;
}

__WILLOW_END_NAMESPACE