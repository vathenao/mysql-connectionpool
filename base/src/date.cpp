#include "stdafx.h"
#include "date.h"
#include "stringUtils.h"
#include "BaseException.h"

__WILLOW_BEGIN_NAMESPACE

//#include <unistd.h>
#ifdef WIN32
#include <WinSock2.h>
#include <windows.h>
#else
#include <unistd.h>
#endif

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

#define maxTimeBufferSize       128
    // Verifies will fail if the needed buffer size is too large


TimeSpan::TimeSpan()
{
}


TimeSpan::TimeSpan(base_time64_t time)
{ 
    m_timeSpan = time; 
}


TimeSpan::TimeSpan(LONG lDays, long nHours, long nMins, long nSecs)
{ 
    m_timeSpan = nSecs + 60* (nMins + 60* (nHours + 24* lDays)); 
}


TimeSpan::TimeSpan(const TimeSpan& timeSpanSrc)
{ 
    m_timeSpan = timeSpanSrc.m_timeSpan; 
}


const TimeSpan& TimeSpan::operator=(const TimeSpan& timeSpanSrc)
{ 
    m_timeSpan = timeSpanSrc.m_timeSpan; 
    return *this; 
}


LONG TimeSpan::GetDays() const
{ 
    return (LONG)(m_timeSpan / (24*3600L)); 
}


LONG TimeSpan::GetTotalHours() const
	{ return (LONG)(m_timeSpan/3600); }

long TimeSpan::GetHours() const
	{ return (long)(GetTotalHours() - GetDays()*24); }

LONG TimeSpan::GetTotalMinutes() const
	{ return (LONG)(m_timeSpan/60); }

long TimeSpan::GetMinutes() const
	{ return (long)(GetTotalMinutes() - GetTotalHours()*60); }

LONG TimeSpan::GetTotalSeconds() const
	{ return (LONG)m_timeSpan; }

long TimeSpan::GetSeconds() const
	{ return (long)(GetTotalSeconds() - GetTotalMinutes()*60); }

TimeSpan TimeSpan::operator-(const TimeSpan& timeSpan) const
	{ return TimeSpan(m_timeSpan - timeSpan.m_timeSpan); }

TimeSpan TimeSpan::operator+(const TimeSpan& timeSpan) const
	{ return TimeSpan(m_timeSpan + timeSpan.m_timeSpan); }

const TimeSpan& TimeSpan::operator+=(const TimeSpan& timeSpan)
	{ m_timeSpan += timeSpan.m_timeSpan; return *this; }

const TimeSpan& TimeSpan::operator-=(const TimeSpan& timeSpan)
	{ m_timeSpan -= timeSpan.m_timeSpan; return *this; }

bool TimeSpan::operator==(const TimeSpan& timeSpan) const
	{ return m_timeSpan == timeSpan.m_timeSpan; }

bool TimeSpan::operator!=(const TimeSpan& timeSpan) const
	{ return m_timeSpan != timeSpan.m_timeSpan; }

bool TimeSpan::operator<(const TimeSpan& timeSpan) const
	{ return m_timeSpan < timeSpan.m_timeSpan; }

bool TimeSpan::operator>(const TimeSpan& timeSpan) const
	{ return m_timeSpan > timeSpan.m_timeSpan; }

bool TimeSpan::operator<=(const TimeSpan& timeSpan) const
	{ return m_timeSpan <= timeSpan.m_timeSpan; }

bool TimeSpan::operator>=(const TimeSpan& timeSpan) const
	{ return m_timeSpan >= timeSpan.m_timeSpan; }


string TimeSpan::Format(LPCSTR pFormat) const
// formatting timespans is a little trickier than formatting Dates
//  * we are only interested in relative time formats, ie. it is illegal
//      to format anything dealing with absolute time (i.e. years, months,
//         day of week, day of year, timezones, ...)
//  * the only valid formats:
//      %D - # of days -- NEW !!!
//      %H - hour in 24 hour format
//      %M - minute (0-59)
//      %S - seconds (0-59)
//      %% - percent sign
{
    char szBuffer[maxTimeBufferSize];
    char ch;
    LPSTR pch = szBuffer;

    while ((ch = *pFormat++) != '\0')
    {
        BASE_ASSERT(pch < ( szBuffer + maxTimeBufferSize));
        if (ch == '%')
        {
            switch (ch = *pFormat++)
            {
            default:
                BASE_ASSERT(FALSE);      // probably a bad format character
            case '%':
                *pch++ = ch;
                break;
            case 'D':
                pch += sprintf(pch, "%ld", GetDays());
                break;
            case 'H':
                pch += sprintf(pch, "%02d", GetHours());
                break;
            case 'M':
                pch += sprintf(pch, "%02d", GetMinutes());
                break;
            case 'S':
                pch += sprintf(pch, "%02d", GetSeconds());
                break;
            }
        }
        else
        {
            *pch++ = ch;
            /*
            if (_istlead(ch))
            {
                BASE_ASSERT(pch < &szBuffer[maxTimeBufferSize]);
                *pch++ = *pFormat++;
            }
            */
        }
    }

    *pch = '\0';
    return szBuffer;
}




Date::Date(long nYear, long nMonth, long nDay, long nHour, long nMin, long nSec,
    long nDST)
{
    setNotNull();

	if (nYear < 1900) // 发现数据库中有小于1900年的时间，反正也没意义，所以小于1900年的都按1900年处理 --- hxy,20070411
	{
		nYear = 1900;
	}

    struct tm atm;
    atm.tm_sec = (int)nSec;
    atm.tm_min = (int)nMin;
    atm.tm_hour = (int)nHour;
    //BASE_ASSERT(nDay >= 1 && nDay <= 31);
	if (!( nDay >= 1 && nDay <= 31 ))
	throw CBaseException("日期不正确:[%04d-%02d-%02d %02d:%02d:%02d",nYear,nMonth,nDay,nHour,nMin,nSec) ;
    atm.tm_mday = (int)nDay;
    //BASE_ASSERT(nMonth >= 1 && nMonth <= 12);
	if (!( nMonth >= 1 && nMonth <= 12 ))
	throw CBaseException("日期不正确:[%04d-%02d-%02d %02d:%02d:%02d",nYear,nMonth,nDay,nHour,nMin,nSec) ;
    atm.tm_mon = (int)nMonth - 1;        // tm_mon is 0 based
    // BASE_ASSERT(nYear >= 1900); // hxy,20070411
    atm.tm_year = (int)nYear - 1900;     // tm_year is 1900 based
    atm.tm_isdst = (int)nDST;
    m_time = base_mktime64(&atm);
	//m_time = mktime(&atm) ;
	//if ( m_time == -1 )
	//	perror("error") ;
	if ( m_time == -1 )
	throw CBaseException("日期不正确:[%04d-%02d-%02d %02d:%02d:%02d]",nYear,nMonth,nDay,nHour,nMin,nSec) ;
    //BASE_ASSERT(m_time != -1);       // indicates an illegal input time
}


Date::Date(WORD wDosDate, WORD wDosTime, long nDST)
{
    setNotNull();

    struct tm atm;
    atm.tm_sec = (wDosTime & ~0xFFE0) << 1;
    atm.tm_min = (wDosTime & ~0xF800) >> 5;
    atm.tm_hour = wDosTime >> 11;

    atm.tm_mday = wDosDate & ~0xFFE0;
    atm.tm_mon = ((wDosDate & ~0xFE00) >> 5) - 1;
    atm.tm_year = (wDosDate >> 9) + 80;
    atm.tm_isdst = (int)nDST;
    m_time = base_mktime64(&atm);
	if ( m_time == -1 )
	throw CBaseException("日期不正确2:[%04d-%02d-%02d %02d:%02d:%02d]",atm.tm_year,atm.tm_mon,atm.tm_mday,atm.tm_hour,atm.tm_min,atm.tm_sec) ;
	
    //BASE_ASSERT(m_time != -1);       // indicates an illegal input time
}


Date::Date(const TSYSTEMTIME& sysTime, long nDST)
{
    setNotNull();

    if (sysTime.wYear < 1900)
    {
        time_t time0 = 0L;
        Date timeT(time0);
        *this = timeT;
    }
    else
    {
        Date timeT(
            (long)sysTime.wYear, (long)sysTime.wMonth, (long)sysTime.wDay,
            (long)sysTime.wHour, (long)sysTime.wMinute, (long)sysTime.wSecond,
            nDST);
#ifdef WIN32	
		// 这种处理比较不爽
		timeT.setTime(timeT.getTime() + DEFAULT_TIME_ZONE_OFFSET * 3600 ) ;
#endif
        *this = timeT;
    }
}

#ifdef WIN32
#undef GetCurrentTime
#endif

Date Date::GetCurrentTime()
// return the current system time
{
    return Date(::time(NULL));
}


long Date::GetCurrentDate()
{
    Date t(::time(NULL));
    return(t.getYear()*10000+t.getMonth()*100+t.getDay());
}


struct tm* Date::GetGmtTm(struct tm* ptm) const
{
    //if (ptm != NULL)
    //{
    //    *ptm = *gmtime64_r(&m_time);
    //    return ptm;
    //}
    //else
    //    return gmtime(&m_time);
	return base_gmtime64_r(&m_time,ptm) ;

}


struct tm* Date::GetLocalTm(struct tm* ptm) const
{
	//time_t t = m_time ;
 //   if (ptm != NULL)
 //   {
	//	
 //       struct tm* ptmTemp = localtime(&t);
 //       if (ptmTemp == NULL)
 //           return NULL;    // indicates the m_time was not initialized!

 //       *ptm = *ptmTemp;
 //       return ptm;
 //   }
 //   else
 //       return localtime(&t);


	return base_localtime64_r(&m_time,ptm) ;
	
	//return localtime(&m_time) ;

}

// 返回基于1900年的总秒数
long long Date::GetTotalSeconds()
{
	base_time64_t sec1970 = GetTime();
	base_time64_t sec1900 = sec1970 + 2208988800UL;

	return sec1900;
}

// 秒转换为Date,秒基于1900年
Date Date::SecondsToDate( long long sec, long offset, int nTz )
{
	base_time64_t tt = sec - 2208988800UL + offset;

	tt += 3600 * nTz; // 时区转换

	struct tm tm;

	base_gmtime64_r( &tt, &tm );

	m_time = base_mktime64(&tm);
	
	return *this;
}


bool Date::GetAsSystemTime(TSYSTEMTIME& timeDest) const
{
	struct tm tm ;
    struct tm* ptm = GetLocalTm(&tm);
    if (ptm == NULL)
        return FALSE;

    timeDest.wYear = (WORD) (1900 + ptm->tm_year);
    timeDest.wMonth = (WORD) (1 + ptm->tm_mon);
    timeDest.wDayOfWeek = (WORD) ptm->tm_wday;
    timeDest.wDay = (WORD) ptm->tm_mday;
    timeDest.wHour = (WORD) ptm->tm_hour;
    timeDest.wMinute = (WORD) ptm->tm_min;
    timeDest.wSecond = (WORD) ptm->tm_sec;
    timeDest.wMilliseconds = 0;

    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// String formatting


#ifdef _UNICODE
#endif


string Date::Format(LPCSTR pFormat) const
{
    char szBuffer[maxTimeBufferSize];

	struct tm tmTemp ;
    struct tm* ptmTemp = base_localtime64_r(&m_time,&tmTemp );
    if (ptmTemp == NULL ||
        !strftime(szBuffer, _countof(szBuffer), pFormat, ptmTemp))
        szBuffer[0] = '\0';
    return szBuffer;
}


string Date::FormatGmt(LPCSTR pFormat) const
{
    char szBuffer[maxTimeBufferSize];

    //struct tm* ptmTemp = gmtime(&m_time);
	struct tm tmTemp ;
	struct tm *ptmTemp = base_gmtime64_r(&m_time,&tmTemp) ;
    if (ptmTemp == NULL ||
        !strftime(szBuffer, _countof(szBuffer), pFormat, ptmTemp))
        szBuffer[0] = '\0';
    return szBuffer;
}

/*
#ifdef _UNICODE
// These functions are provided for compatibility with MFC 3.x
string Date::Format(LPCSTR pFormat) const
{
    string strFormat(pFormat);
    return Format((LPCSTR)strFormat);
}

string Date::FormatGmt(LPCSTR pFormat) const
{
    string strFormat(pFormat);
    return FormatGmt((LPCSTR)strFormat);
}


#endif // _UNICODE
*/


void Date::WaitSeconds(long nSeconds, long lMicroSeconds/*=0L*/)
{
#ifndef WIN32
    if(nSeconds>0)
        sleep((int)nSeconds);
    else
        usleep((unsigned int)lMicroSeconds);
#else
    //SleepEx(nSeconds*1000+lMicroSeconds,TRUE);
	Sleep(nSeconds*1000+lMicroSeconds) ;
#endif
}

/////////////////////////////////////////////////////////////////////////////

bool Date::GetFromString(const string& strTime,const string& strFormat)
{
    long nYear=0;
    long nYearBytes=0;
    long nMonth=0;
    long nDay=0;
    long nHour=0;
    long nMinute=0;
    long nSecond=0;

	string strTime1 = StringUtils::trim(strTime) ;
	string strFormat1=StringUtils::trim(strFormat) ;
    
    if(strTime1.length()!=strFormat1.length())
    {
        return(FALSE);
    }

	strFormat1 = StringUtils::toLowerCase(strFormat1) ;

    for(size_t i=0;i<strFormat1.length();i++)
    {
        char c=strFormat1.at(i);
		
        switch(c)
        {
        case('y'):
            nYear=nYear*10+strTime1.at(i)-'0';
            ++nYearBytes;
            break;
        case('m'):
            nMonth=nMonth*10+strTime1.at(i)-'0';
            break;
        case('d'):
            nDay=nDay*10+strTime1.at(i)-'0';
            break;
        case('h'):
            nHour=nHour*10+strTime1.at(i)-'0';
            break;
        case('n'):
            nMinute=nMinute*10+strTime1.at(i)-'0';
            break;
        case('s'):
            nSecond=nSecond*10+strTime1.at(i)-'0';
            break;
        }
    }
    
    struct tm tm;
    memset(&tm,0,sizeof(struct tm));
    if(nYearBytes==2)
        tm.tm_year=nYear+2000-1900;
    else if(nYearBytes==4)
        tm.tm_year=nYear-1900;
    else
        return(FALSE);

    tm.tm_mon=nMonth-1;
    tm.tm_mday=nDay;
    tm.tm_hour=nHour;
    tm.tm_min=nMinute;
    tm.tm_sec=nSecond;

    m_time=base_mktime64(&tm);

    if(m_time==-1L)
        return(FALSE);
    else
        return(TRUE);
}


Date Date::GetFromString_S(const string& strTime,const string& strFormat) 
{
	Date d ;
	d.GetFromString(strTime,strFormat) ;
	return d ;
}

base_time64_t Date::PackTime(long nDate,long nTime)
{
    struct tm tm;
    memset(&tm,0,sizeof(struct tm));
    tm.tm_year=(nDate/10000)-1900;
    tm.tm_mon=(nDate/100)%100-1;
    tm.tm_mday=nDate%100;
    tm.tm_hour=nTime/10000;
    tm.tm_min=(nTime/100)%100;
    tm.tm_sec=nTime%100;

    return(base_mktime64(&tm));
}

long Date::GetNextMonth(long nMonth)
{
    if(nMonth>999999)
        nMonth/=100;
    long y=nMonth/100;
    long m=nMonth%100;
    if(m==12)
    {
        m=1;
        y++;
    }
    else
        ++m;

    return(y*100+m);
}

long Date::GetPreviousMonth(long nMonth)
{
    if(nMonth>999999)
        nMonth/=100;
    long y=nMonth/100;
    long m=nMonth%100;
    if(m==1)
    {
        m=12;
        --y;
    }
    else
        --m;

    return(y*100+m);
}

long Date::GetNextMonthFirstDate(long nDate)
{
    long nMonth=GetNextMonth(nDate);
    return(nMonth*100+1);
}

long Date::GetMonthFirstDate(long nDate)
{
    if(nDate<=999999)
        return(nDate*100+1);
    else
        return((nDate/100)*100+1);
}

long Date::GetMonthLastDate(long nDate)
{
    long nNextDate=GetNextMonthFirstDate(nDate);
    return(GetPreviousDate(nNextDate));
}

long Date::GetPreviousDate(long nDate)
{
    long d=nDate%100;
    long m=(nDate/100)%100;
    long y=nDate/10000;

    struct tm at;
    memset(&at,0,sizeof(struct tm));
    at.tm_year=y-1900;
    at.tm_mon=m-1;
    at.tm_mday=d;

    base_time64_t t=base_mktime64(&at);
    t-=24*3600;
	
	struct tm tm ;
    struct tm *pt=base_localtime64_r(&t,&tm);
    return((pt->tm_year+1900)*10000+(pt->tm_mon+1)*100+pt->tm_mday);
}


long Date::GetNextDate(long nDate)
{
    long d=nDate%100;
    long m=(nDate/100)%100;
    long y=nDate/10000;

    struct tm at;
    memset(&at,0,sizeof(struct tm));
    at.tm_year=y-1900;
    at.tm_mon=m-1;
    at.tm_mday=d;

	base_time64_t t=base_mktime64(&at);
	t+=24*3600;

	struct tm tm ;
	struct tm *pt=base_localtime64_r(&t,&tm);
    return((pt->tm_year+1900)*10000+(pt->tm_mon+1)*100+pt->tm_mday);
}

//long GetWeekStart(long nDate);
//long GetPreviousWeekStart(long nDate);
long Date::GetWeekDates(long nDate,long& nWeekStart,long& nWeekStop)
{
    long d=nDate%100;
    long m=(nDate/100)%100;
    long y=nDate/10000;

    struct tm at;
    memset(&at,0,sizeof(struct tm));
    at.tm_year=y-1900;
    at.tm_mon=m-1;
    at.tm_mday=d;

	base_time64_t t=base_mktime64(&at);
	struct tm tm ;
	struct tm *pt=base_localtime64_r(&t,&tm);

    time_t tWeekStart=t-pt->tm_wday*24*3600;
    struct tm *pWeekStart=localtime(&tWeekStart);
    nWeekStart=(pWeekStart->tm_year+1900)*10000+(pWeekStart->tm_mon+1)*100+pWeekStart->tm_mday;

    time_t tWeekStop=tWeekStart+6*24*3600;
    struct tm *pWeekStop=localtime(&tWeekStop);

    nWeekStop=(pWeekStop->tm_year+1900)*10000+(pWeekStop->tm_mon+1)*100+pWeekStop->tm_mday;
    
    return(nWeekStart);
}

//long GetPreviousWeekDates(long nDate,long& nWeekStart,long& nWeekStop);

long Date::DecreaseDate(long nDate,long nDay)
{
    long d=nDate%100;
    long m=(nDate/100)%100;
    long y=nDate/10000;

    struct tm at;
    memset(&at,0,sizeof(struct tm));
    at.tm_year=y-1900;
    at.tm_mon=m-1;
    at.tm_mday=d;

	base_time64_t t=base_mktime64(&at);
    t-=nDay*24*3600;
	struct tm tm ;
	struct tm *pt=base_localtime64_r(&t,&tm);

    return((pt->tm_year+1900)*10000+(pt->tm_mon+1)*100+pt->tm_mday);
}

long Date::IncreaseDate(long nDate,long nDay)
{
    long d=nDate%100;
    long m=(nDate/100)%100;
    long y=nDate/10000;

    struct tm at;
    memset(&at,0,sizeof(struct tm));
    at.tm_year=y-1900;
    at.tm_mon=m-1;
    at.tm_mday=d;

	base_time64_t t=base_mktime64(&at);
	t+=nDay*24*3600;
	struct tm tm ;
	struct tm *pt=base_localtime64_r(&t,&tm);
    return((pt->tm_year+1900)*10000+(pt->tm_mon+1)*100+pt->tm_mday);
}

bool Date::ParseStringTime(LPSTR p,long& d,long& t)
{
    int len=strlen(p);
    LPSTR pm=strchr(p,'-');
    LPSTR pc=strchr(p,':');

    if(pm==NULL&&pc==NULL)
    {
        if(len==8)
        {
            d=atol(p),t=0L;
            return(TRUE);
        }
        else if(len==6)
        {
            d=0L,t=atol(p);
            return(TRUE);
        }
        else if(len==14)
        {
            char sz[9];
            strncpy(sz,p,8);
            sz[8]='\0';
            d=atol(sz);
            t=atol(p+8);
            return(TRUE);
        }
        else return(FALSE);
    }
    else if(pm==NULL&&pc!=NULL)
    {
        char sz[7];
        int i=0;
        while(*p&&(i<6))
        {
            if(*p==':')
                ++p;
            else
            {
                sz[i]=*p;
                ++p;
                ++i;
            }
        }
        sz[i]='\0';
        d=0L,t=atol(sz);
    }
    else if(pm!=NULL&&pc==NULL)
    {
        char sz[20];
        char *q=strchr(p,'-');
        strncpy(sz,p,q-p);
        sz[q-p]='\0';
        long y=atol(sz);
        p=q+1;

        q=strchr(p,'-');
        if(q==NULL)
            return(FALSE);

        strncpy(sz,p,q-p);
        sz[q-p]='\0';
        long m=atol(sz);
        p=q+1;
        long dd=atol(p);
        d=y*10000+m*100+dd;
        t=0L;
        return(TRUE);
    }
    else
    {
        char sz[20];
        char *q=strchr(p,'-');
        strncpy(sz,p,q-p);
        sz[q-p]='\0';
        long y=atol(sz);
        p=q+1;

        q=strchr(p,'-');
        if(q==NULL)
            return(FALSE);

        strncpy(sz,p,q-p);
        sz[q-p]='\0';
        long m=atol(sz);
        p=q+1;
        q=strchr(p,' ');
        strncpy(sz,p,q-p);
        sz[q-p]='\0';
        long dd=atol(sz);
        p=q+1;

        d=y*10000+m*100+dd;
        
        q=strchr(p,':');
        strncpy(sz,p,q-p);
        sz[q-p]='\0';
        long h=atol(sz);
        p=q+1;

        q=strchr(p,':');
        strncpy(sz,p,q-p);
        sz[q-p]='\0';
        long n=atol(sz);
        p=q+1;
        
        t=h*10000+n*100+atol(p);

        return(TRUE);
    }
    return(FALSE);
}

long Date::DifferentDays(long nDate1,long nDate2)
{
    time_t t1=PackTime(nDate1,0L);
    time_t t2=PackTime(nDate2,0L);
    return static_cast<long>((t2-t1)/86400L);
}

#undef inline
#define inline

// Date and TimeSpan





//2011-4-14 构造时默认为空，拷贝时增加拷贝m_isNull
Date::Date()
{ 
    m_time = time(NULL); 
    setNotNull();
}

Date::Date(base_time64_t time)
{ 
    m_time = time;
    setNotNull();
}

Date::Date(const Date& timeSrc)
{ 
    m_time = timeSrc.m_time; 
    m_isNull = timeSrc.m_isNull; 
}

//2011-04-17 增加此构造函数 by hch
Date::Date(const Date& timeSrc, bool isNull)
{
    m_time = timeSrc.m_time; 
    m_isNull = isNull; 
}

const Date& Date::operator=(const Date& timeSrc)
{ 
    m_time = timeSrc.m_time; 
    m_isNull = timeSrc.m_isNull; 
    return *this; 
}

const Date& Date::operator=(time_t t)
{ 
    m_time = t; 
    setNotNull();
    return *this; 
}

base_time64_t Date::getTime() const
	{ return m_time; }

base_time64_t Date::GetTime() const
{
	return m_time; 
}

int Date::getYear() const
{
	return (int)GetYear() ;
}

long Date::GetYear() const
{
	struct tm tm ;
	return GetLocalTm(&tm)->tm_year + 1900; 
}

int Date::getMonth() const
{
	return GetMonth() ;
}
long Date::GetMonth() const
{
	struct tm tm ;
	return GetLocalTm(&tm)->tm_mon + 1; 
}

int Date::getDay() const
{
	return (int)GetDay() ;
}

long Date::GetDay() const
{
	struct tm tm ;
	return GetLocalTm(&tm)->tm_mday; 
}

long Date::getDate() const
{
	return (long)getDay() ;
}


int Date::getHours() const
{
	return (int)GetHour() ;
}

long Date::GetHour() const
{
	struct tm tm ;
	return GetLocalTm(&tm)->tm_hour; 	
}


int Date::getMinutes() const
{
	return (int)GetMinute() ;
}

long Date::GetMinute() const
{
	struct tm tm ;
	return GetLocalTm(&tm)->tm_min; 
}

int Date::getSeconds() const
{ 
	return (int)GetSecond() ;
}
long Date::GetSecond() const
{ 
	struct tm tm ;
	return GetLocalTm(&tm)->tm_sec; 
}


void Date::GetDate(int& year,int& month,int& day, int& hour,int& minute,int& second) 
{
	struct tm Tm;
	struct tm* pTm = GetLocalTm(&Tm) ;
	year = pTm->tm_year + 1900 ;
	month = pTm->tm_mon + 1 ;
	day = pTm->tm_mday ;
	hour = pTm->tm_hour ;
	minute = pTm->tm_min ;
	second = pTm->tm_sec; 
}

long Date::GetDayOfWeek() const
	{ return GetLocalTm(NULL)->tm_wday + 1; }

long Date::GetDate8() const
{
    return(GetYear()*10000+GetMonth()*100+GetDay());
}

long Date::GetDate6() const
{
    return((GetYear()%100)*10000+GetMonth()*100+GetDay());
}

long Date::GetTime6() const
{
    return(GetHour()*10000+GetMinute()*100+GetSecond());
}


void Date::setTime(base_time64_t t) 
{
	this->m_time = t ;
}

void Date::setYear(int year) 
{
    if (year < 1900)
    {
        time_t time0 = 0L;
        Date timeT(time0);
        *this = timeT;
    }
    else
    {
        Date timeT(
            year, getMonth(), getDay(),
            getHours(), getMinutes(),getSeconds() 
            );
        *this = timeT;
    }
}

void Date::setMonth(int month) 
{
    if (month > 12 )
	{
		month = 12 ;
	}
	else if ( month < 1 )
	{
		month = 1 ;
	}

    {
        Date timeT(
            getYear(), month, getDay(),
            getHours(), getMinutes(),getSeconds());
        *this = timeT;
    }
}

void Date::setDate(int day)
{
	setDay(day) ;
}

void Date::setDay(int day)
{
    if (day > 31 )
	{
		day = 12 ;
	}
	else if ( day < 1 )
	{
		day = 1 ;
	}
	// 检查不严格tobefixed
    {
        Date timeT(
            getYear(), getMonth(), day,
            getHours(), getMinutes(),getSeconds());
        *this = timeT;
    }
}

void Date::setHours(int hours) 
{
	if ( hours > 23 ) hours = 23 ;
	else if ( hours < 0 ) hours = 0 ;
	
    {
        Date timeT(
            getYear(), getMonth(), getDay(),
            hours, getMinutes(),getSeconds());
        *this = timeT;
    }
}

void Date::setMinutes(int minutes) 
{
	if ( minutes > 59 ) minutes = 59 ;
	else if ( minutes < 0 ) minutes = 0 ;
	
    {
        Date timeT(
            getYear(), getMonth(), getDay(),
            getHours(), minutes,getSeconds());
        *this = timeT;
    }
}

void Date::setSeconds(int seconds) 
{
	if ( seconds > 59 ) seconds = 59 ;
	else if ( seconds < 0 ) seconds = 0 ;
	
    {
        Date timeT(
            getYear(), getMonth(), getDay(),
            getHours(), getMinutes(),seconds);
        *this = timeT;
    }
}

TimeSpan Date::operator-(const Date& time) const
	{ return TimeSpan(m_time - time.m_time); }

Date Date::operator-(const TimeSpan& timeSpan) const
	{ return Date(m_time - timeSpan.m_timeSpan); }

Date Date::operator+(const TimeSpan& timeSpan) const
	{ return Date(m_time + timeSpan.m_timeSpan); }

const Date& Date::operator+=(const TimeSpan& timeSpan)
	{ m_time += timeSpan.m_timeSpan; return *this; }

const Date& Date::operator-=(const TimeSpan& timeSpan)
	{ m_time -= timeSpan.m_timeSpan; return *this; }

bool Date::operator==(const Date& time) const
	{ return m_time == time.m_time; }

bool Date::operator!=(const Date& time) const
	{ return m_time != time.m_time; }

bool Date::operator<(const Date& time) const
	{ return m_time < time.m_time; }

bool Date::operator>(const Date& time) const
	{ return m_time > time.m_time; }

bool Date::operator<=(const Date& time) const
	{ return m_time <= time.m_time; }

bool Date::operator>=(const Date& time) const
	{ return m_time >= time.m_time; }



string  Date::toString() const 
{ 
  //2011-4-14 如果为空则返回空串 by hch
  if (ifNull())
  {
    return "";
  }

  //YYYY-MM-DD hh:mm:ss(19) 
  char result[30];
  memset(result,0,30);

  struct tm tm ;
  GetLocalTm(&tm) ;
  sprintf(result,"%04d-%02d-%02d %02d:%02d:%02d",
	  tm.tm_year + 1900 ,
	  tm.tm_mon + 1 ,
	  tm.tm_mday,
	  tm.tm_hour,
	  tm.tm_min,
      tm.tm_sec) ;
	  

  return result;
}

Date Date::GetNextMonthFirstDateTime(const Date& DateIn) // 如传入2011-12-01 12:12:12 则得到2012-01-01 00:00:00
{
    long y=DateIn.getYear();
    long m=DateIn.getMonth();
    if(m==12)
    {
        m=1;
        y++;
    }
    else
        ++m;

    return Date(y, m, 1, 0, 0, 0);
}

__WILLOW_END_NAMESPACE
