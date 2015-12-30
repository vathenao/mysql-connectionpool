/** 
 *  date.h
 *
 *  Copyright:vathene
 * 
 *	version: v1.0.0
 *
 **/
 
#ifndef __WILLOW_DATE_H__
#define __WILLOW_DATE_H__

#include "libdefs.h"
#include "base/libbase.h"
#include "base/date2038.h"
#include <string>

__WILLOW_BEGIN_NAMESPACE

//#include <afx.h>
#include <time.h>

#ifdef WIN32
#undef GetCurrentTime
#endif

#define DATE_REMOTE 20101231L

#define DEFAULT_TIME_ZONE 8 // 默认时区, xff 20090912
#define DEFAULT_TIME_OFFSET 0 // 默认偏移时间, 以小时为单位

/////////////////////////////////////////////////////////////////////////////
// TimeSpan and Date
/**
 *
 */
class TimeSpan 
{
public:

// Constructors
	
	/** 
	 * 构造函数
	 */
	TimeSpan();
	
	/**
	 * 构造函数
	 */ 
	TimeSpan(base_time64_t time);
	
	/**
	 * 构造函数
	 */
	TimeSpan(LONG lDays, long nHours, long nMins, long nSecs);

	
	/**
	 * 拷贝构造函数
	 */
	TimeSpan(const TimeSpan& timeSpanSrc);
	
	/**
	 * 拷贝函数
	 */
	const TimeSpan& operator=(const TimeSpan& timeSpanSrc);


public:
// Attributes
	// extract parts
	/**
	 * 得到天数
	 */
	LONG GetDays() const;   // total # of days
	
	/**
	 * 得到总的小时数
	 */
	LONG GetTotalHours() const;
	
	/**
	 * 得到小时数
	 */
	long GetHours() const;
	
	/**
	 * 得到总的分钟数	 
	 */
	LONG GetTotalMinutes() const;
	
	/**
	 * 得到分钟数
	 */
	long GetMinutes() const;
	
	/**
	 * 得到总的秒数
	 */
	LONG GetTotalSeconds() const;
	
	/**
	 * 得到秒数
	 */
	long GetSeconds() const;

// Operations
	// time math
	
	/**
	 * 减法操作符实现
	 */
	TimeSpan operator-(const TimeSpan& timeSpan) const;
	
	/**
	 * 加法操作符实现
	 */
	TimeSpan operator+(const TimeSpan& timeSpan) const;
	
	/**
	 * 加等于操作符实现
	 */
	const TimeSpan& operator+=(const TimeSpan& timeSpan);
	
	/**
	 * 减等于操作符实现
	 */
	const TimeSpan& operator-=(const TimeSpan& timeSpan);
	
	/**
	 * 相等判断
	 */
	bool operator==(const TimeSpan& timeSpan) const;
	
	/**
	 * 不等判断
	 */
	bool operator!=(const TimeSpan& timeSpan) const;
	
	/**
	 * 小于判断
	 */
	bool operator<(const TimeSpan& timeSpan) const;
	
	/**
	 * 大于判断
	 */
	bool operator>(const TimeSpan& timeSpan) const;
	
	/**
	 * 小于等于判断
	 */
	bool operator<=(const TimeSpan& timeSpan) const;
	
	/**
	 * 大于等于判断
	 */
	bool operator>=(const TimeSpan& timeSpan) const;

	/**
	 * 格式化成字符串，可以自己填写格式
	 * 支持
	 * %D  日期
	 * %H  小时
	 * %M  分钟
     * %S  秒
	 */
	std::string Format(LPCSTR pFormat) const;

private:
	
	base_time64_t m_timeSpan;
	friend class Date;
};


class Date //: public CObject
{
public:

// Constructors
	/**
	 * 获取当前时间
	 */
	static Date GetCurrentTime();
    
    
	/**
	 * 取当前日期(返回数值YYYYMMDD)
	 */	
    static long GetCurrentDate();

	/** 
	 * 构造函数
	 */
	Date();
	
	/**
	 * 构造函数
	 */
	Date(base_time64_t time);
	
	/**
	 * 构造函数
	 */
	Date(long nYear, long nMonth, long nDay, long nHour, long nMin, long nSec,
		long nDST = -1);
	
	/**
	 * 构造函数
	 */
	Date(WORD wDosDate, WORD wDosTime, long nDST = -1);

	/**
	 * 拷贝构造函数
	 */	
	Date(const Date& timeSrc);

    //2011-04-17 增加此构造函数 by hch
    /**
	 * 拷贝构造函数
	 */	
	Date(const Date& timeSrc, bool isNull);

   	/**
	 * 构造函数
	 */
	Date(const TSYSTEMTIME& sysTime, long nDST = -1);

	/**
	 * 拷贝函数
	 */
	const Date& operator=(const Date& timeSrc);
	
	/**
	 * 拷贝函数
	 */
	const Date& operator=(time_t t);

	
	/**
	 * 获取格林制日期
	 */
	struct tm* GetGmtTm(struct tm* ptm = NULL) const;
	
	/**
	 * 获取本地日期
	 */
	struct tm* GetLocalTm(struct tm* ptm = NULL) const;
	
	/**
	 * 获取总的秒数,基于1900年, xff 20090912
	 */
	long long GetTotalSeconds();

	/** 
	 * 秒转换为Date,秒基于1900年, xff 20090912
	 */
	Date SecondsToDate( long long sec, long offset=DEFAULT_TIME_OFFSET, int nTz=DEFAULT_TIME_ZONE );

	/**
	 * 返回系统时间格式
	 */
	bool GetAsSystemTime(TSYSTEMTIME& timeDest) const;

	/**
	 * 获取整数时间，相对于1970-1-1 0:0:0
	 */	
	base_time64_t GetTime() const;
	base_time64_t getTime() const;

	/**
	 * 获取年月日时分秒
	 */	
	void GetDate(int& year,int& month,int& day, int& hour,int& minute,int& second) ;

	
	/**
	 * 获取年
	 */	
	long GetYear() const;
	int  getYear() const;

	/**
	 * 获取月
	 */	
	long GetMonth() const;
	int  getMonth() const;       // month of year (1 = Jan)
	
	/**
	 * 获取日
	 */	
	long GetDay() const;
	int  getDay() const;         // day of month
	
	long getDate() const ;
	/**
	 * 获取时
	 */	
	long GetHour() const;
	int  getHours() const;

	/**
	 * 获取分
	 */	
	long GetMinute() const;
	int  getMinutes() const;
	
	/**
	 * 获取秒
	 */	
	long GetSecond() const;
	int  getSeconds() const;
	
	/**
	 * 获取星期几
	 */	
	long GetDayOfWeek() const;   // 1=Sun, 2=Mon, ..., 7=Sat
    
	/**
	 * 获取8位整数日期，格式为YYYYMMDD
	 */	
    long GetDate8() const;
	
	/**
	 * 获取8位整数日期，格式为YYMMDD
	 */	
    long GetDate6() const;

	/**
	 * 获取6位整数时间，格式为HHMMSS
	 */	
    long GetTime6() const;

	/**
	 * 设置整数时间，相对于1970-1-1 0:0:0
	 */	
	void setTime(base_time64_t t) ;

	/**
	 * 设置年
	 */	
	void setYear(int year) ;
	/**
	 * 设置月
	 */	
	void setMonth(int month) ;
	/**
	 * 设置日
	 */	
	void setDay(int day) ;
	void setDate(int day) ;
	/**
	 * 设置小时
	 */	
	void setHours(int hours) ;
	/**
	 * 设置分钟
	 */	
	void setMinutes(int minutes) ;
	/**
	 * 设置秒
	 */	
	void setSeconds(int seconds) ;
	/**
	 * 转换成字符串，格式为 YYYY-MM-DD HH:MI:SS
	 */	
	virtual string toString() const;  
	
	
	
	// Operations
	// time math
	
	/**
	 * 减去一个日期，得到偏移量
	 */	
	TimeSpan operator-(const Date& time) const;
	
	/**
	 * 减去一个偏移量，得到一个日期
	 */	
	Date operator-(const TimeSpan& timeSpan) const;
	
	/**
	 * 加一个偏移量，得到一个日期
	 */	
	Date operator+(const TimeSpan& timeSpan) const;
	
	/**
	 * 加等于操作符
	 */	
	const Date& operator+=(const TimeSpan& timeSpan);
	
	/**
	 * 减等于操作符
	 */	
	const Date& operator-=(const TimeSpan& timeSpan);
	
	/**
	 * 相等判断
	 */	
	bool operator==(const Date& time) const;
	
	/**
	 * 不等判断
	 */	
	bool operator!=(const Date& time) const;
	
	/**
	 * 小于判断
	 */	
	bool operator<(const Date& time) const;
	
	/**
	 * 大于判断
	 */	
	bool operator>(const Date& time) const;
	
	/**
	 * 小于等于判断
	 */	
	bool operator<=(const Date& time) const;
	
	/**
	 * 大于等于判断
	 */	
	bool operator>=(const Date& time) const;

	// formatting using "C" strftime
	
	/**
	 * 格式化成字符串，内部调用strftime
	 */	
	string Format(LPCSTR pFormat) const;
	
	/** 
	 * 格式化成格林制时间字符串，内部调用strftime
	 */
	string FormatGmt(LPCSTR pFormat) const;

public:
	/**
	 * 根据字符串得到时间，格式可以支持
	 * %y 年
	 * %m 月
	 * %d 日
	 * %h 时
	 * %n 分
	 * %s 秒
	 */
    bool GetFromString(const string& strTime,const string& strFormat);

	static Date GetFromString_S(const string& strTime,const string& strFormat) ;


private:
    //2011-4-14 增加m_isNull 标志对象是否为空
	bool m_isNull; //是否为空
	base_time64_t m_time;

public:
	/**
	 * 等待时间（秒和毫秒）
	 */
	static void WaitSeconds(long nSeconds,long lMicroSeconds=0L);

	/** 
	 * 把整数日期和时间变成时间
	 * 整数时间和日期的格式为 YYYYMMDD HHMMSS
	 */
	static base_time64_t PackTime(long nDate,long nTime);

public:
    // 日期操作函数
	/**
	 * 获取下个月，输入和返回格式YYYYMM
	 */
    static long GetNextMonth(long nMonth);

	/**
	 * 得到前个月，输入和返回格式YYYYMM
	 */
    static long GetPreviousMonth(long nMonth);

	/**
	 * 获取下一天，输入和返回格式YYYYMMDD
	 */
    static long GetNextDate(long nDate);

	/**
	 * 获取前一天，输入和返回格式YYYYMMDD
	 */
    static long GetPreviousDate(long nDate);

	/**
	 * 获取下个月的第一天，输入和返回格式YYYYMMDD
	 */
    static long GetNextMonthFirstDate(long nDate);

	/**
	 * 获取本月的第一天，输入和返回格式YYYYMMDD
	 */
    static long GetMonthFirstDate(long nDate);

	/**
	 * 获取本月的最后一天，输入和返回格式YYYYMMDD
	 */
    static long GetMonthLastDate(long nDate);

	/**
	 * 减少n天，输入和返回格式YYYYMMDD
	 */
    static long DecreaseDate(long nDate,long nDay);

	/**
	 * 增加n天，输入和返回格式YYYYMMDD
	 */
    static long IncreaseDate(long nDate,long nDay);

	/**
	 * 两个日期的相差天数
	 */
    static long DifferentDays(long nDate1,long nDate2);
        
	/**
	 * 没有实现
	 */
    static long GetWeekStart(long nDate);
	/**
	 * 没有实现
	 */
    static long GetPreviousStart(long nDate);
	/**
	 * 得到本周的开始和结束日，输入输出格式为YYYYMMDD
	 */
    static long GetWeekDates(long nDate,long& nWeekStart,long& nWeekStop);

	/**
	 * 没有实现
	 */
    static long GetPreviousWeekDates(long nDate,long& nWeekStart,long& nWeekStop);

	/**
	 * 根据字符串格式的时间日期串得到整数的时间和日期（时间和日期格式为YYYYMMDD)
	 * 字符串格式为 YYYY-MM-DD HH:MI:SS
	 */
    static bool ParseStringTime(LPSTR p,long& d,long& t);

public:
    
public:
    //2011-4-14 增加对日期类型是否为空的相关操作 by hch

    /*!
    * @brief 对象是否非空
    * @return 空则返回true，否则返回false
    */
    bool ifNull() const
    {
        return m_isNull;
    }

    /*!
    * @brief 设置对象为空
    */
    void setNull()
    {
        m_isNull = true;
    }

    /*!
    * @brief 设置对象为非空
    */
    void setNotNull()
    {
        m_isNull = false;
    }
    
    static Date GetNextMonthFirstDateTime(const Date& DateIn);
};

__WILLOW_END_NAMESPACE
#endif
