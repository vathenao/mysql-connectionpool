/** 
 *  stringBuffer.h
 *
 *  Copyright vathena
 *
 *  vathena
 */
 
 
#ifndef __WILLOW_STRINGBUFFER_H__
#define __WILLOW_STRINGBUFFER_H__

#include "libcommon.h"

__WILLOW_BEGIN_NAMESPACE


class StringBuffer
{
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
public:
  explicit StringBuffer(const string& str);
  explicit StringBuffer(const char* __s);
  explicit StringBuffer(const char* __s,size_t length);

  StringBuffer();
  StringBuffer(const StringBuffer& str);

//--------------------------------------------------------------------------
// Capacity methods
//--------------------------------------------------------------------------
public:
  size_t length() const; 
  size_t capacity() const;
  
  void resize(size_t __n);  
  void clear();
  
  bool empty() const;

//--------------------------------------------------------------------------
// Element access
//--------------------------------------------------------------------------
public:
  const char& operator[] (size_t __pos) const;
  char& operator[](size_t __pos);
  
  const char& at(size_t __n) const;
  char& at(size_t __n);

  const string& str() const;

  string toString() const;   

//--------------------------------------------------------------------------
// Modifiers methods (+=)
//--------------------------------------------------------------------------
public:
  StringBuffer& operator+=(const StringBuffer& __str);
  StringBuffer& operator+=(const string& __str);
  StringBuffer& operator+=(const char*  __s);
  StringBuffer& operator+=(const char&  __c);

  StringBuffer& operator+=(const bool& __n);
  
  StringBuffer& operator+=(const short& __n);
  StringBuffer& operator+=(const unsigned short& __n);

  StringBuffer& operator+=(const int& __n);
  StringBuffer& operator+=(const unsigned int& __n);

  StringBuffer& operator+=(const long& __n);
  StringBuffer& operator+=(const unsigned long& __n);

#if defined(LONG_LONG_IS_LONG)
  StringBuffer& operator+=(const long long& __n);
  StringBuffer& operator+=(const unsigned long long& __n);
#else
  StringBuffer& operator+=(const LONG_LONG & __n);
  StringBuffer& operator+=(const ULONG_LONG & __n);
#endif

  StringBuffer& operator+=(const float& __n);
  StringBuffer& operator+=(const double& __n);
  
//--------------------------------------------------------------------------
// Modifiers methods (append)
//--------------------------------------------------------------------------
public:
  StringBuffer& append(const StringBuffer& __str);
  StringBuffer& append(const string& __str);
  StringBuffer& append(const char*  __s);
  StringBuffer& append(const char&  __c);

  StringBuffer& append(const bool& __n);
  
  StringBuffer& append(const short& __n);
  StringBuffer& append(const unsigned short& __n);

  StringBuffer& append(const int& __n);
  StringBuffer& append(const unsigned int& __n);

  StringBuffer& append(const long& __n);
  StringBuffer& append(const unsigned long& __n);

#if defined(LONG_LONG_IS_LONG)
  StringBuffer& append(const long long& __n);
  StringBuffer& append(const unsigned long long& __n);
#else
  StringBuffer& append(const LONG_LONG & __n);
  StringBuffer& append(const ULONG_LONG & __n);
#endif

  StringBuffer& append(const float& __n);
  StringBuffer& append(const double& __n);    
  
//--------------------------------------------------------------------------
// Modifiers methods (insert)
//--------------------------------------------------------------------------
public:
  StringBuffer& insert(size_t __pos,const StringBuffer& __str);
  StringBuffer& insert(size_t __pos,const string& __str);
  StringBuffer& insert(size_t __pos,const char*  __s);
  StringBuffer& insert(size_t __pos,const char&  __c);

  StringBuffer& insert(size_t __pos,const bool& __n);
  
  StringBuffer& insert(size_t __pos,const short& __n);
  StringBuffer& insert(size_t __pos,const unsigned short& __n);

  StringBuffer& insert(size_t __pos,const int& __n);
  StringBuffer& insert(size_t __pos,const unsigned int& __n);

  StringBuffer& insert(size_t __pos,const long& __n);
  StringBuffer& insert(size_t __pos,const unsigned long& __n);

#if defined(LONG_LONG_IS_LONG)
  StringBuffer& insert(size_t __pos,const long long& __n);
  StringBuffer& insert(size_t __pos,const unsigned long long& __n);
#else
  StringBuffer& insert(size_t __pos,const LONG_LONG & __n);
  StringBuffer& insert(size_t __pos,const ULONG_LONG & __n);
#endif

  StringBuffer& insert(size_t __pos,const float& __n);
  StringBuffer& insert(size_t __pos,const double& __n);  
 
//--------------------------------------------------------------------------
// Modifiers methods (<<)
//--------------------------------------------------------------------------
public:
  StringBuffer& operator<<(const StringBuffer& __str);
  StringBuffer& operator<<(const string& __str);
  StringBuffer& operator<<(const char*  __s);
  StringBuffer& operator<<(const char&  __c);

  StringBuffer& operator<<(const bool& __n);
  
  StringBuffer& operator<<(const short& __n);
  StringBuffer& operator<<(const unsigned short& __n);

  StringBuffer& operator<<(const int& __n);
  StringBuffer& operator<<(const unsigned int& __n);

  StringBuffer& operator<<(const long& __n);
  StringBuffer& operator<<(const unsigned long& __n);

#if defined(LONG_LONG_IS_LONG)
  StringBuffer& operator<<(const long long& __n);
  StringBuffer& operator<<(const unsigned long long& __n);
#else
  StringBuffer& operator<<(const LONG_LONG & __n);
  StringBuffer& operator<<(const ULONG_LONG & __n);
#endif
    
  StringBuffer& operator<<(const float& __n);
  StringBuffer& operator<<(const double& __n);
 
//--------------------------------------------------------------------------
// Modifiers methods (delete)
//--------------------------------------------------------------------------
public:
  StringBuffer& erase(size_t __pos,size_t __n);
  
//--------------------------------------------------------------------------
// Modifiers methods (replace)
//--------------------------------------------------------------------------
public:
  StringBuffer& replace(size_t __pos, size_t __n, const string& __str);
  StringBuffer& replaceAll(size_t __pos,const string& __src, const string& __dst);  
  
//--------------------------------------------------------------------------
// Finders methods (indexOf)
//--------------------------------------------------------------------------
public:
  size_t indexOf(const string& __str) const;
  size_t indexOf(const string& __str,size_t __pos) const;
  
  size_t lastIndexOf(const string& __str) const;
  size_t lastIndexOf(const string& __str,size_t __pos) const;  

  size_t indexOf(int ch) const;
  size_t indexOf(int ch,size_t __pos) const;
  
  size_t lastIndexOf(int ch) const;
  size_t lastIndexOf(int ch,size_t __pos) const;  
  
//--------------------------------------------------------------------------
// Substring methods
//--------------------------------------------------------------------------
public:   
  StringBuffer substring(size_t __pos, size_t __n = string::npos) const;
  
//--------------------------------------------------------------------------
// Relationship operation methods 
//--------------------------------------------------------------------------
public:
  int compare(const StringBuffer& __str) const;
  int compare(const string& __str) const;
  int compare(const char* __s) const;
                  
//--------------------------------------------------------------------------
//Swap methods
//--------------------------------------------------------------------------
public:
  void swap(StringBuffer& sh);
  void swap(string& str);

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
private:
  string m_cache_str;  
};

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
const StringBuffer operator+(const StringBuffer& lhs,const StringBuffer& __str);
const StringBuffer operator+(const StringBuffer& lhs,const string& __str);
const StringBuffer operator+(const StringBuffer& lhs,const char*  __s);
const StringBuffer operator+(const StringBuffer& lhs,const char&  __c);

const StringBuffer operator+(const StringBuffer& lhs,const bool& __n);

const StringBuffer operator+(const StringBuffer& lhs,const short& __n);
const StringBuffer operator+(const StringBuffer& lhs,const unsigned short& __n);

const StringBuffer operator+(const StringBuffer& lhs,const int& __n);
const StringBuffer operator+(const StringBuffer& lhs,const unsigned int& __n);

const StringBuffer operator+(const StringBuffer& lhs,const long& __n);
const StringBuffer operator+(const StringBuffer& lhs,const unsigned long& __n);

#if defined(LONG_LONG_IS_LONG)
const  StringBuffer operator+(const StringBuffer& lhs,const long long& __n);
const  StringBuffer operator+(const StringBuffer& lhs,const unsigned long long& __n);
#else
const  StringBuffer operator+(const StringBuffer& lhs,const LONG_LONG & __n);
const  StringBuffer operator+(const StringBuffer& lhs,const ULONG_LONG & __n);
#endif

const StringBuffer operator+(const StringBuffer& lhs,const float& __n);
const StringBuffer operator+(const StringBuffer& lhs,const double& __n);

__WILLOW_END_NAMESPACE


#endif
