#ifndef __LIBDEFS_H__
#define __LIBDEFS_H__

#include "libmarco.incl"
#include "libbase.h"
#include "libconfig.h"
#include <iostream>
#include "libalgo.incl"


# if defined(__WILLOW_HAS_NAMESPACES) && !defined(__WILLOW_NO_NAMESPACES)
#   define __WILLOW_NS baselib
#   define __WILLOW_BEGIN_NAMESPACE namespace baselib {
#   define __WILLOW_END_NAMESPACE }
#   define __USING_WILLOW_NS using namespace baselib;
# else
#   define __WILLOW_NS
#   define __WILLOW_BEGIN_NAMESPACE
#   define __WILLOW_END_NAMESPACE
#   define __USING_WILLOW_NS
# endif

#endif