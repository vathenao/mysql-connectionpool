#ifndef __BASE_GLOBAL_H__
#define __BASE_GLOBAL_H__

#include "platform.h"

#if defined(__WILLOW_HAS_NAMESPACES) && !defined(__WILLOW_NO_NAMESPACES)
#   define __WILLOW_NS baselib
#   define __WILLOW_BEGIN_NAMESPACE namespace baselib {
#   define __WILLOW_END_NAMESPACE }
#   define __USING_WILLOW_NS using namespace baselib;
#else
#   define __WILLOW_NS
#   define __WILLOW_BEGIN_NAMESPACE
#   define __WILLOW_END_NAMESPACE
#   define __USING_WILLOW_NS
#endif

#ifndef BASE_EXPORT
  #ifndef BASE_NO_EXPORTS
	#ifdef  BASE_LIB
	#define BASE_EXPORT DLL_API_EXPORT
	#else
	#define BASE_EXPORT DLL_API_IMPORT
	#endif
  #else
	#define BASE_EXPORT
  #endif
#endif

#endif //__BASE_GLOBAL_H__