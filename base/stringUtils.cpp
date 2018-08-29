#include "stringUtils.h"
#include "stringBuffer.h"

#ifdef WIN32

#else
#include <inttypes.h>
#endif
#include <ctype.h>

#include <cstddef>
#include <algorithm>

__WILLOW_BEGIN_NAMESPACE


//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
StringUtils::StringUtils()
{}

//--------------------------------------------------------------------------
// static methods
//--------------------------------------------------------------------------
string StringUtils::toUpperCase(const string& s)
{
  string d;
  std::transform(s.begin(),s.end(),
  std::insert_iterator<string>(d, d.begin()), (int(*)(int))toupper);
  return d;
}

string StringUtils::toLowerCase(const string& s)
{
  string d;
  std::transform(s.begin(), s.end(),
  std::insert_iterator<string>(d, d.begin()), (int(*)(int))tolower);
  return d;
}

string StringUtils::ltrim(const string& s)
{
  string::size_type pos = s.find_first_not_of(' ');
  if (pos == string::npos)
  {
    return string();
  }

  return s.substr(pos);
}

string StringUtils::rtrim(const string& s)
{
  string::size_type pos = s.find_first_not_of(' ');
  if (pos == string::npos)
  {
    return string();
  }

  
  string::size_type n = s.find_last_not_of(' ') + 1;
  return s.substr(0, n);
}


string StringUtils::trim(const string& s)
{
  string::size_type pos = s.find_first_not_of(' ');
  if (pos == string::npos)
  {
    return string();
  }

  string::size_type n = s.find_last_not_of(' ') - pos + 1;
  return s.substr(pos, n);
}

string  StringUtils::replace(const string& __s,size_t __pos, size_t __n, const string& __str)
{
  StringBuffer sb(__s);
  return sb.replace(__pos,__n,__str).str();
}

string  StringUtils::replaceAll(const string& __s,size_t __pos,const string& __src, const string& __dst)
{
  StringBuffer sb(__s);
  return sb.replaceAll(__pos,__src,__dst).str();
}

bool StringUtils::equalsIgnoreCase(const string& s1, const string& s2)
{
  return toLowerCase(s1) == toLowerCase(s2);
}

int StringUtils::compareNoCase(const string& s1,const string& s2)
{
	return strcasecmp(s1.c_str(),s2.c_str()) ;
}

bool StringUtils::endsWith(const string& s, const string& suffix)
{
  return (s.length() - s.rfind(suffix)) == suffix.length();
}

bool StringUtils::startsWith(const string& s, const string& prefix)
{
  return (s.find(prefix) == 0);
}

string StringUtils::format(const char* format, ...)
{
  va_list ap;

//--------------------------------------------
  int size=1024;
  int n=0;
  char* p = 0;
  if ((p = (char*)malloc (size)) == 0)
  {
    return string();
  }

  while(true)
  {
    va_start(ap,format);
    n = vsnprintf(p,size,format,ap);
    va_end(ap);

    if(n > -1 && n < size)
    {
      string str(p,n);
      free(p);
      return str;
    }

    if(n>-1)
    {
      size = n + 1;
    }
    else
    {
      size *= 2;
    }

    if ((p = (char*)realloc (p, size)) == 0)
    {
      return string();
    }
  }
//--------------------------------------------

  return string();
}

string StringUtils::format(const char* format,va_list& ap)
{
//--------------------------------------------
  int size=1024;
  int n=0;
  char* p = 0;
  if ((p = (char*)malloc (size)) == 0)
  {
    return string();
  }

  while(true)
  {
    n = vsnprintf(p,size,format,ap);

    if(n > -1 && n < size)
    {
      string str(p,n);
      free(p);
      return str;
    }

    if(n>-1)
    {
      size = n + 1;
    }
    else
    {
      size *= 2;
    }

    if ((p = (char*)realloc (p, size)) == 0)
    {
      return string();
    }
  }
//--------------------------------------------
}

string StringUtils::left(const string& s , int len)
{
	return s.substr(0,len) ;
}

string StringUtils::mid(const string& s, int from,int len)
{
	return s.substr(from,len) ;
}

string StringUtils::right(const string& s , int len) 
{
	return s.substr(s.length()-len) ;
}

__WILLOW_END_NAMESPACE
