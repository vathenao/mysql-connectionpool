#ifndef __XDBC_DEFINES_H__
#define __XDBC_DEFINES_H__

#if defined(__XDBC_HAS_NAMESPACES) && !defined(__XDBC_NO_NAMESPACES)
#   define __XDBC_NS baselib
#   define __XDBC_BEGIN_NAMESPACE namespace xdbclib {
#   define __XDBC_END_NAMESPACE }
#   define __USING_XDBC_NS using namespace xdbclib;
#else
#   define __XDBC_NS
#   define __XDBC_BEGIN_NAMESPACE
#   define __XDBC_END_NAMESPACE
#   define __USING_XDBC_NS
#endif

#endif