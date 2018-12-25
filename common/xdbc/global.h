#ifndef __XDBC_GLOBAL_H__
#define __XDBC_GLOBAL_H__

#include "base/platform.h"

#if defined(__XDBC_HAS_NAMESPACES) && !defined(__XDBC_NO_NAMESPACES)
#define __XDBC_NS baselib
#define __XDBC_BEGIN_NAMESPACE namespace xdbclib {
#define __XDBC_END_NAMESPACE }
#define __USING_XDBC_NS using namespace xdbclib;
#else
#define __XDBC_NS
#define __XDBC_BEGIN_NAMESPACE
#define __XDBC_END_NAMESPACE
#define __USING_XDBC_NS
#endif

#ifndef XDBC_EXPORT
  #ifndef XDBC_NO_EXPORTS
	#ifdef  XDBC_LIB
	#define XDBC_EXPORT DLL_API_EXPORT
	#else
	#define XDBC_EXPORT DLL_API_IMPORT
	#endif
  #else
	#define XDBC_EXPORT
  #endif
#endif

#endif //__XDBC_GLOBAL_H__