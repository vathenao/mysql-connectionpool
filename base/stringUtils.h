/** 
 *  stringUtils.h
 *
 *  Copyright vathena
 *
 *  vathena  huangchengmao@gmail.com
 */
 
 
#ifndef __WILLOW_STRINGUTILS_H__
#define __WILLOW_STRINGUTILS_H__

#include "libcommon.h"

__WILLOW_BEGIN_NAMESPACE

class StringUtils
{
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
private:
  StringUtils();

//--------------------------------------------------------------------------
// static methods
//--------------------------------------------------------------------------
public: 
  static string  toUpperCase(const string& __s);
  static string  toLowerCase(const string& __s);

public:
  static string  ltrim(const string& __s);
  static string  rtrim(const string& __s);
  static string  trim(const string& __s);

public:
  static string  replace(const string& __s,size_t __pos, size_t __n, const string& __str);
  static string  replaceAll(const string& __s,size_t __pos,const string& __src, const string& __dst);

public:
  static bool equalsIgnoreCase(const string& __s1, const string& __s2);
  static int  compareNoCase(const string& __s1, const string& __s2) ;

public:
  static bool endsWith(const string& __s, const string& __suffix);
  static bool startsWith(const string& __s, const string& __prefix); 

public:
  static string format(const char* format, ...);
  static string format(const char* format,va_list& ap);

public:
  static string left(const string& __s,int len) ;
  static string mid(const string& __s,int from,int len=-1) ;
  static string right(const string& __s,int len) ;


};

__WILLOW_END_NAMESPACE


#endif
