#include "base/stringBuffer.h"
//#include "base/libnumber.h"

__USING_STL_NS

__WILLOW_BEGIN_NAMESPACE

//--------------------------------------------------------------------------
// Capacity methods
//-------------------------------------------------------------------------- 
StringBuffer::StringBuffer(){}

StringBuffer::StringBuffer(const string& str):m_cache_str(str){}

StringBuffer::StringBuffer(const char* __s)
{
  m_cache_str.assign(__s,strlen(__s));
}

StringBuffer::StringBuffer(const char* __s,size_t length)
{
  m_cache_str.assign(__s,length);
}

StringBuffer::StringBuffer(const StringBuffer& str):m_cache_str(str.m_cache_str){}

//--------------------------------------------------------------------------
// Capacity methods
//-------------------------------------------------------------------------- 
size_t StringBuffer::length() const
{
  return m_cache_str.length();
}

size_t StringBuffer::capacity() const
{
  return m_cache_str.capacity();
} 

void StringBuffer::resize(size_t __n)
{
  m_cache_str.resize(__n);
} 

void StringBuffer::clear()
{
  m_cache_str.clear();
}

bool StringBuffer::empty() const
{
  return m_cache_str.empty();
}

//--------------------------------------------------------------------------
// Element access
//--------------------------------------------------------------------------
const char& StringBuffer::operator[] (size_t __pos) const
{
  return m_cache_str[__pos];
}

char& StringBuffer::operator[](size_t __pos)
{
  return m_cache_str[__pos];
}

const char& StringBuffer::at(size_t __n) const
{
  return m_cache_str.at(__n);
}

char& StringBuffer::at(size_t __n)
{
  return m_cache_str.at(__n);
}

const string& StringBuffer::str() const
{
  return m_cache_str;
}

string StringBuffer::toString() const
{
  return m_cache_str;
}
 
//--------------------------------------------------------------------------
// Modifiers methods (+=)
//--------------------------------------------------------------------------

StringBuffer& StringBuffer::operator+=(const StringBuffer& __str)
{
  return this->append(__str);
}

StringBuffer& StringBuffer::operator+=(const string& __str)
{
  return this->append(__str);
}

StringBuffer& StringBuffer::operator+=(const char*  __s)
{
  return this->append(__s);
}

StringBuffer& StringBuffer::operator+=(const char&  __c)
{
  return this->append(__c);
}

StringBuffer& StringBuffer::operator+=(const bool& __n)
{
  return this->append(__n);
}

StringBuffer& StringBuffer::operator+=(const short& __n)
{
  return this->append(__n);
}
StringBuffer& StringBuffer::operator+=(const unsigned short& __n)
{
  return this->append(__n);
}

StringBuffer& StringBuffer::operator+=(const int& __n)
{
  return this->append(__n);
}
StringBuffer& StringBuffer::operator+=(const unsigned int& __n)
{
  return this->append(__n);
}

StringBuffer& StringBuffer::operator+=(const long& __n)
{
  return this->append(__n);
}
StringBuffer& StringBuffer::operator+=(const unsigned long& __n)
{
  return this->append(__n);
}

#if defined(LONG_LONG_IS_LONG)
StringBuffer& StringBuffer::operator+=(const long long & __n)
{
  return this->append(__n);
}
StringBuffer& StringBuffer::operator+=(const unsigned long long & __n)
{
  return this->append(__n);
}
#else
StringBuffer& StringBuffer::operator+=(const LONG_LONG & __n)
{
  return this->append(__n);
}
StringBuffer& StringBuffer::operator+=(const ULONG_LONG & __n)
{
  return this->append(__n);
}
#endif 

StringBuffer& StringBuffer::operator+=(const float& __n)
{
  return this->append(__n);
}
StringBuffer& StringBuffer::operator+=(const double& __n)
{
  return this->append(__n);
}

//--------------------------------------------------------------------------
// Modifiers methods (<<)
//--------------------------------------------------------------------------

StringBuffer& StringBuffer::operator<<(const StringBuffer& __str)
{
  return this->append(__str);
}

StringBuffer& StringBuffer::operator<<(const string& __str)
{
  return this->append(__str);
}

StringBuffer& StringBuffer::operator<<(const char*  __s)
{
  return this->append(__s);
}

StringBuffer& StringBuffer::operator<<(const char&  __c)
{
  return this->append(__c);
}

StringBuffer& StringBuffer::operator<<(const bool& __n)
{
  return this->append(__n);
}

StringBuffer& StringBuffer::operator<<(const short& __n)
{
  return this->append(__n);
}
StringBuffer& StringBuffer::operator<<(const unsigned short& __n)
{
  return this->append(__n);
}

StringBuffer& StringBuffer::operator<<(const int& __n)
{
  return this->append(__n);
}
StringBuffer& StringBuffer::operator<<(const unsigned int& __n)
{
  return this->append(__n);
}

StringBuffer& StringBuffer::operator<<(const long& __n)
{
  return this->append(__n);
}
StringBuffer& StringBuffer::operator<<(const unsigned long& __n)
{
  return this->append(__n);
}

#if defined(LONG_LONG_IS_LONG)
StringBuffer& StringBuffer::operator<<(const long long & __n)
{
  return this->append(__n);
}
StringBuffer& StringBuffer::operator<<(const unsigned long long & __n)
{
  return this->append(__n);
}
#else
StringBuffer& StringBuffer::operator<<(const LONG_LONG & __n)
{
  return this->append(__n);
}
StringBuffer& StringBuffer::operator<<(const ULONG_LONG & __n)
{
  return this->append(__n);
}
#endif

StringBuffer& StringBuffer::operator<<(const float& __n)
{
  return this->append(__n);
}
StringBuffer& StringBuffer::operator<<(const double& __n)
{
  return this->append(__n);
}

//--------------------------------------------------------------------------
// Modifiers methods (StringBuffer::append)
//--------------------------------------------------------------------------
StringBuffer& StringBuffer::append(const StringBuffer& __str)
{
  m_cache_str.append(__str.m_cache_str);
  return *this;
}

StringBuffer& StringBuffer::append(const string& __str)
{
  m_cache_str.append(__str);
  return *this;
}

StringBuffer& StringBuffer::append(const char*  __s)
{
  m_cache_str.append(__s);
  return *this;
}

StringBuffer& StringBuffer::append(const char&  __c)
{
  m_cache_str.append(&__c,1);
  return *this;
}

StringBuffer& StringBuffer::append(const bool& __n)
{
  return this->insert(length(),__n);
}

StringBuffer& StringBuffer::append(const short& __n)
{
  return this->insert(length(),__n);
}

StringBuffer& StringBuffer::append(const unsigned short& __n)
{
  return this->insert(length(),__n);
}

StringBuffer& StringBuffer::append(const int& __n)
{
  return this->insert(length(),__n);
}

StringBuffer& StringBuffer::append(const unsigned int& __n)
{
  return this->insert(length(),__n);
}

StringBuffer& StringBuffer::append(const long& __n)
{
  return this->insert(length(),__n);
}

StringBuffer& StringBuffer::append(const unsigned long& __n)
{
  return this->insert(length(),__n);
}

#if defined(LONG_LONG_IS_LONG)
StringBuffer& StringBuffer::append(const long long & __n)
{
  return this->insert(length(),__n);
}
StringBuffer& StringBuffer::append(const unsigned long long & __n)
{
  return this->insert(length(),__n);
}
#else
StringBuffer& StringBuffer::append(const LONG_LONG & __n)
{
  return this->insert(length(),__n);
}
StringBuffer& StringBuffer::append(const ULONG_LONG & __n)
{
  return this->insert(length(),__n);
}
#endif

StringBuffer& StringBuffer::append(const float& __n)
{
  return this->insert(length(),__n);
}
StringBuffer& StringBuffer::append(const double& __n)
{
  return this->insert(length(),__n);
}  

//--------------------------------------------------------------------------
// Modifiers methods (StringBuffer::insert)
//--------------------------------------------------------------------------
StringBuffer& StringBuffer::insert(size_t __pos,const StringBuffer& __str)
{
 m_cache_str.insert(__pos,__str.m_cache_str);  
  return *this;
}  
StringBuffer& StringBuffer::insert(size_t __pos,const string& __str)
{
  m_cache_str.insert(__pos,__str);  
  return *this;
}  
StringBuffer& StringBuffer::insert(size_t __pos,const char*  __s)
{
  m_cache_str.insert(__pos,__s);
  return *this;
} 
 
StringBuffer& StringBuffer::insert(size_t __pos,const char&  __c)
{
  m_cache_str.insert(__pos,&__c,1); 
  return *this;
}  

StringBuffer& StringBuffer::insert(size_t __pos,const bool&  __c)
{
  if(__c)
  {
    m_cache_str.insert(__pos,"true"); 
  }
  else
  {
    m_cache_str.insert(__pos,"false"); 
  }
  
  return *this;

}

StringBuffer& StringBuffer::insert(size_t __pos,const short& __n)
{
  //m_cache_str.insert(__pos,Number::toString((int)__n));
  m_cache_str.insert(__pos,number_to_str(__n)) ;

  return *this;
}  

StringBuffer& StringBuffer::insert(size_t __pos,const unsigned short& __n)
{
  //m_cache_str.insert(__pos,Number::toString((unsigned int)__n));
  m_cache_str.insert(__pos,number_to_str(__n)) ;
  return *this;
}  

StringBuffer& StringBuffer::insert(size_t __pos,const int& __n)
{
  //m_cache_str.insert(__pos,Number::toString(__n));
  m_cache_str.insert(__pos,number_to_str(__n)) ;
  return *this;
} 
 
StringBuffer& StringBuffer::insert(size_t __pos,const unsigned int& __n)
{
  //m_cache_str.insert(__pos,Number::toString(__n));
  m_cache_str.insert(__pos,number_to_str(__n)) ;
  return *this;
}  

StringBuffer& StringBuffer::insert(size_t __pos,const long& __n)
{
  //m_cache_str.insert(__pos,Number::toString((LONG_LONG)__n));
  m_cache_str.insert(__pos,number_to_str(__n)) ;
  return *this;
} 
 
StringBuffer& StringBuffer::insert(size_t __pos,const unsigned long& __n)
{
  //m_cache_str.insert(__pos,Number::toString((ULONG_LONG)__n));
  m_cache_str.insert(__pos,number_to_str(__n)) ;
  return *this;
} 

#if defined(LONG_LONG_IS_LONG)
StringBuffer& StringBuffer::insert(size_t __pos,const long long & __n)
{
  //m_cache_str.insert(__pos,Number::toString(__n));
  m_cache_str.insert(__pos,number_to_str(__n)) ;
  return *this;
}

StringBuffer& StringBuffer::insert(size_t __pos,const unsigned long long & __n)
{
  //m_cache_str.insert(__pos,Number::toString(__n));
  m_cache_str.insert(__pos,number_to_str(__n)) ;
  return *this;
}
#else
StringBuffer& StringBuffer::insert(size_t __pos,const LONG_LONG & __n)
{
  //m_cache_str.insert(__pos,Number::toString(__n));
  m_cache_str.insert(__pos,number_to_str(__n)) ;
  return *this;
}  

StringBuffer& StringBuffer::insert(size_t __pos,const ULONG_LONG & __n)
{
  //m_cache_str.insert(__pos,Number::toString(__n));
  m_cache_str.insert(__pos,number_to_str(__n)) ;
  return *this;
}  
#endif
      
StringBuffer& StringBuffer::insert(size_t __pos,const float& __n)
{
  //m_cache_str.insert(__pos,Number::toString(__n));
  m_cache_str.insert(__pos,float_to_str(__n)) ;
  return *this;
}  

StringBuffer& StringBuffer::insert(size_t __pos,const double& __n)
{
  //m_cache_str.insert(__pos,Number::toString(__n));
  m_cache_str.insert(__pos,float_to_str(__n)) ;
  return *this;
}  

//--------------------------------------------------------------------------
// Modifiers methods (delete)
//-------------------------------------------------------------------------- 
StringBuffer& StringBuffer::erase(size_t __pos,size_t __n)
{
  m_cache_str.erase(__pos,__n);
  
  return *this;
}

//--------------------------------------------------------------------------
// Modifiers methods (replace)
//--------------------------------------------------------------------------
StringBuffer& StringBuffer::replace(size_t __pos, size_t __n, const string& __str)
{
  m_cache_str.replace(__pos,__n,__str);
  return *this;  
}

StringBuffer& StringBuffer::replaceAll(size_t __pos,const string& __src, const string& __dst)
{
  size_t prevPos = __pos;
  size_t newPos  = 0;
  
  while((newPos = m_cache_str.find(__src,prevPos)) != string::npos)
  {
    //if(newPos == prevPos)
    //{
    //  break;
    //}
    
    prevPos = newPos;
    m_cache_str.replace(newPos,__src.length(),__dst);
  }

  return *this;  
}

//--------------------------------------------------------------------------
// Finders methods (substring)
//--------------------------------------------------------------------------
size_t StringBuffer::indexOf(const string& __str) const
{
  return m_cache_str.find_first_of(__str);
}

size_t StringBuffer::indexOf(const string& __str,size_t __pos) const
{
  return m_cache_str.find_first_of(__str,__pos);  
}

size_t StringBuffer::lastIndexOf(const string& __str) const
{
  return m_cache_str.find_last_of(__str);   
}

size_t StringBuffer::lastIndexOf(const string& __str,size_t __pos) const
{
  return m_cache_str.find_last_of(__str,__pos); 
} 

size_t StringBuffer::indexOf(int ch) const
{
  return m_cache_str.find_first_of((char)ch);
}

size_t StringBuffer::indexOf(int ch,size_t __pos) const
{
  return m_cache_str.find_first_of((char)ch,__pos);  
}

size_t StringBuffer::lastIndexOf(int ch) const
{
  return m_cache_str.find_last_of((char)ch);  
}

size_t StringBuffer::lastIndexOf(int ch,size_t __pos) const
{
  return m_cache_str.find_last_of((char)ch,__pos); 
}
  
//--------------------------------------------------------------------------
// substring methods
//--------------------------------------------------------------------------

StringBuffer StringBuffer::substring(size_t __pos, size_t __n ) const
{
  StringBuffer temp;  
  temp += m_cache_str.substr(__pos,__n); 
  return temp;
}

//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------

int StringBuffer::compare(const StringBuffer& __str) const
{
  return m_cache_str.compare(__str.m_cache_str);
}

int StringBuffer::compare(const string& __str) const
{
  return m_cache_str.compare(__str);  
}

int StringBuffer::compare(const char* __s) const
{
  return m_cache_str.compare(__s);  
}
           
//--------------------------------------------------------------------------
//
//--------------------------------------------------------------------------

void StringBuffer::swap(StringBuffer& sh)
{
  m_cache_str.swap(sh.m_cache_str);
}

void StringBuffer::swap(string& str)
{
  m_cache_str.swap(str);
}


//===============================================================
//===============================================================
const StringBuffer operator+(const StringBuffer& lhs,const StringBuffer& __str)
{
  StringBuffer temp(lhs);
  temp += __str;  
  return temp;
}

const StringBuffer operator+(const StringBuffer& lhs,const string& __str)
{
  StringBuffer temp(lhs);
  temp += __str;  
  return temp;
}

const StringBuffer operator+(const StringBuffer& lhs,const char*  __s)
{
  StringBuffer temp(lhs);
  temp += __s;  
  return temp;
}

const StringBuffer operator+(const StringBuffer& lhs,const char&  __c)
{
  StringBuffer temp(lhs);
  temp += __c;  
  return temp;
}

const StringBuffer operator+(const StringBuffer& lhs,const bool& __n)
{
  StringBuffer temp(lhs);
  temp += __n;  
  return temp;
}

const StringBuffer operator+(const StringBuffer& lhs,const short& __n)
{
  StringBuffer temp(lhs);
  temp += __n;  
  return temp;
}

const StringBuffer operator+(const StringBuffer& lhs,const unsigned short& __n)
{
  StringBuffer temp(lhs);
  temp += __n;  
  return temp;
}

const StringBuffer operator+(const StringBuffer& lhs,const int& __n)
{
  StringBuffer temp(lhs);
  temp += __n;  
  return temp;
}

const StringBuffer operator+(const StringBuffer& lhs,const unsigned int& __n)
{
  StringBuffer temp(lhs);
  temp += __n;  
  return temp;
}

const StringBuffer operator+(const StringBuffer& lhs,const long& __n)
{
  StringBuffer temp(lhs);
  temp += __n;  
  return temp;
}

const StringBuffer operator+(const StringBuffer& lhs,const unsigned long& __n)
{
  StringBuffer temp(lhs);
  temp += __n;  
  return temp;
}

#if defined(LONG_LONG_IS_LONG)
const StringBuffer operator+(const StringBuffer& lhs,const long long& __n)
{
  StringBuffer temp(lhs);
  temp += __n;
  return temp;
}

const StringBuffer operator+(const StringBuffer& lhs,const unsigned long long& __n)
{
  StringBuffer temp(lhs);
  temp += __n;
  return temp;
}
#else
const StringBuffer operator+(const StringBuffer& lhs,const LONG_LONG& __n)
{
  StringBuffer temp(lhs);
  temp += __n;  
  return temp;
}

const StringBuffer operator+(const StringBuffer& lhs,const ULONG_LONG& __n)
{
  StringBuffer temp(lhs);
  temp += __n;  
  return temp;
}
#endif
      
const StringBuffer operator+(const StringBuffer& lhs,const float& __n)
{
  StringBuffer temp(lhs);
  temp += __n;  
  return temp;
}

const StringBuffer operator+(const StringBuffer& lhs,const double& __n)
{
  StringBuffer temp(lhs);
  temp += __n;  
  return temp;
}

__WILLOW_END_NAMESPACE
