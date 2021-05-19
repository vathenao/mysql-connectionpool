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

#include "global.h"
#include "date2038.h"

__WILLOW_BEGIN_NAMESPACE

#ifdef WIN32
#undef GetCurrentTime
#endif

#define DATE_REMOTE 20101231L

#define DEFAULT_TIME_ZONE 8 // Ĭ��ʱ��, xff 20090912
#define DEFAULT_TIME_OFFSET 0 // Ĭ��ƫ��ʱ��, ��СʱΪ��λ

/////////////////////////////////////////////////////////////////////////////
// TimeSpan and Date
/**
 *
 */
class BASE_EXPORT TimeSpan
{
public:

// Constructors
	
	/** 
	 * ���캯��
	 */
	TimeSpan();
	
	/**
	 * ���캯��
	 */ 
	TimeSpan(base_time64_t time);
	
	/**
	 * ���캯��
	 */
	TimeSpan(LONG lDays, long nHours, long nMins, long nSecs);

	
	/**
	 * �������캯��
	 */
	TimeSpan(const TimeSpan& timeSpanSrc);
	
	/**
	 * ��������
	 */
	const TimeSpan& operator=(const TimeSpan& timeSpanSrc);


public:
// Attributes
	// extract parts
	/**
	 * �õ�����
	 */
	LONG GetDays() const;   // total # of days
	
	/**
	 * �õ��ܵ�Сʱ��
	 */
	LONG GetTotalHours() const;
	
	/**
	 * �õ�Сʱ��
	 */
	long GetHours() const;
	
	/**
	 * �õ��ܵķ�����	 
	 */
	LONG GetTotalMinutes() const;
	
	/**
	 * �õ�������
	 */
	long GetMinutes() const;
	
	/**
	 * �õ��ܵ�����
	 */
	LONG GetTotalSeconds() const;
	
	/**
	 * �õ�����
	 */
	long GetSeconds() const;

// Operations
	// time math
	
	/**
	 * ����������ʵ��
	 */
	TimeSpan operator-(const TimeSpan& timeSpan) const;
	
	/**
	 * �ӷ�������ʵ��
	 */
	TimeSpan operator+(const TimeSpan& timeSpan) const;
	
	/**
	 * �ӵ��ڲ�����ʵ��
	 */
	const TimeSpan& operator+=(const TimeSpan& timeSpan);
	
	/**
	 * �����ڲ�����ʵ��
	 */
	const TimeSpan& operator-=(const TimeSpan& timeSpan);
	
	/**
	 * ����ж�
	 */
	bool operator==(const TimeSpan& timeSpan) const;
	
	/**
	 * �����ж�
	 */
	bool operator!=(const TimeSpan& timeSpan) const;
	
	/**
	 * С���ж�
	 */
	bool operator<(const TimeSpan& timeSpan) const;
	
	/**
	 * �����ж�
	 */
	bool operator>(const TimeSpan& timeSpan) const;
	
	/**
	 * С�ڵ����ж�
	 */
	bool operator<=(const TimeSpan& timeSpan) const;
	
	/**
	 * ���ڵ����ж�
	 */
	bool operator>=(const TimeSpan& timeSpan) const;

	/**
	 * ��ʽ�����ַ����������Լ���д��ʽ
	 * ֧��
	 * %D  ����
	 * %H  Сʱ
	 * %M  ����
     * %S  ��
	 */
	std::string Format(LPCSTR pFormat) const;

private:
	
	base_time64_t m_timeSpan;
	friend class Date;
};


class BASE_EXPORT Date //: public CObject
{
public:

// Constructors
	/**
	 * ��ȡ��ǰʱ��
	 */
	static Date GetCurrentTime();
    
    
	/**
	 * ȡ��ǰ����(������ֵYYYYMMDD)
	 */	
    static long GetCurrentDate();

	/** 
	 * ���캯��
	 */
	Date();
	
	/**
	 * ���캯��
	 */
	Date(base_time64_t time);
	
	/**
	 * ���캯��
	 */
	Date(long nYear, long nMonth, long nDay, long nHour, long nMin, long nSec,
		long nDST = -1);
	
	/**
	 * ���캯��
	 */
	Date(WORD wDosDate, WORD wDosTime, long nDST = -1);

	/**
	 * �������캯��
	 */	
	Date(const Date& timeSrc);

    //2011-04-17 ���Ӵ˹��캯�� by hch
    /**
	 * �������캯��
	 */	
	Date(const Date& timeSrc, bool isNull);

   	/**
	 * ���캯��
	 */
	Date(const TSYSTEMTIME& sysTime, long nDST = -1);

	/**
	 * ��������
	 */
	const Date& operator=(const Date& timeSrc);
	
	/**
	 * ��������
	 */
	const Date& operator=(time_t t);

	
	/**
	 * ��ȡ����������
	 */
	struct tm* GetGmtTm(struct tm* ptm = NULL) const;
	
	/**
	 * ��ȡ��������
	 */
	struct tm* GetLocalTm(struct tm* ptm = NULL) const;
	
	/**
	 * ��ȡ�ܵ�����,����1900��, xff 20090912
	 */
	long long GetTotalSeconds();

	/** 
	 * ��ת��ΪDate,�����1900��, xff 20090912
	 */
	Date SecondsToDate( long long sec, long offset=DEFAULT_TIME_OFFSET, int nTz=DEFAULT_TIME_ZONE );

	/**
	 * ����ϵͳʱ���ʽ
	 */
	bool GetAsSystemTime(TSYSTEMTIME& timeDest) const;

	/**
	 * ��ȡ����ʱ�䣬�����1970-1-1 0:0:0
	 */	
	base_time64_t GetTime() const;
	base_time64_t getTime() const;

	/**
	 * ��ȡ������ʱ����
	 */	
	void GetDate(int& year,int& month,int& day, int& hour,int& minute,int& second) ;

	
	/**
	 * ��ȡ��
	 */	
	long GetYear() const;
	int  getYear() const;

	/**
	 * ��ȡ��
	 */	
	long GetMonth() const;
	int  getMonth() const;       // month of year (1 = Jan)
	
	/**
	 * ��ȡ��
	 */	
	long GetDay() const;
	int  getDay() const;         // day of month
	
	long getDate() const ;
	/**
	 * ��ȡʱ
	 */	
	long GetHour() const;
	int  getHours() const;

	/**
	 * ��ȡ��
	 */	
	long GetMinute() const;
	int  getMinutes() const;
	
	/**
	 * ��ȡ��
	 */	
	long GetSecond() const;
	int  getSeconds() const;
	
	/**
	 * ��ȡ���ڼ�
	 */	
	long GetDayOfWeek() const;   // 1=Sun, 2=Mon, ..., 7=Sat
    
	/**
	 * ��ȡ8λ�������ڣ���ʽΪYYYYMMDD
	 */	
    long GetDate8() const;
	
	/**
	 * ��ȡ8λ�������ڣ���ʽΪYYMMDD
	 */	
    long GetDate6() const;

	/**
	 * ��ȡ6λ����ʱ�䣬��ʽΪHHMMSS
	 */	
    long GetTime6() const;

	/**
	 * ��������ʱ�䣬�����1970-1-1 0:0:0
	 */	
	void setTime(base_time64_t t) ;

	/**
	 * ������
	 */	
	void setYear(int year) ;
	/**
	 * ������
	 */	
	void setMonth(int month) ;
	/**
	 * ������
	 */	
	void setDay(int day) ;
	void setDate(int day) ;
	/**
	 * ����Сʱ
	 */	
	void setHours(int hours) ;
	/**
	 * ���÷���
	 */	
	void setMinutes(int minutes) ;
	/**
	 * ������
	 */	
	void setSeconds(int seconds) ;
	/**
	 * ת�����ַ�������ʽΪ YYYY-MM-DD HH:MI:SS
	 */	
	virtual string toString() const;  
	
	
	
	// Operations
	// time math
	
	/**
	 * ��ȥһ�����ڣ��õ�ƫ����
	 */	
	TimeSpan operator-(const Date& time) const;
	
	/**
	 * ��ȥһ��ƫ�������õ�һ������
	 */	
	Date operator-(const TimeSpan& timeSpan) const;
	
	/**
	 * ��һ��ƫ�������õ�һ������
	 */	
	Date operator+(const TimeSpan& timeSpan) const;
	
	/**
	 * �ӵ��ڲ�����
	 */	
	const Date& operator+=(const TimeSpan& timeSpan);
	
	/**
	 * �����ڲ�����
	 */	
	const Date& operator-=(const TimeSpan& timeSpan);
	
	/**
	 * ����ж�
	 */	
	bool operator==(const Date& time) const;
	
	/**
	 * �����ж�
	 */	
	bool operator!=(const Date& time) const;
	
	/**
	 * С���ж�
	 */	
	bool operator<(const Date& time) const;
	
	/**
	 * �����ж�
	 */	
	bool operator>(const Date& time) const;
	
	/**
	 * С�ڵ����ж�
	 */	
	bool operator<=(const Date& time) const;
	
	/**
	 * ���ڵ����ж�
	 */	
	bool operator>=(const Date& time) const;

	// formatting using "C" strftime
	
	/**
	 * ��ʽ�����ַ������ڲ�����strftime
	 */	
	string Format(LPCSTR pFormat) const;
	
	/** 
	 * ��ʽ���ɸ�����ʱ���ַ������ڲ�����strftime
	 */
	string FormatGmt(LPCSTR pFormat) const;

public:
	/**
	 * �����ַ����õ�ʱ�䣬��ʽ����֧��
	 * %y ��
	 * %m ��
	 * %d ��
	 * %h ʱ
	 * %n ��
	 * %s ��
	 */
    bool GetFromString(const string& strTime,const string& strFormat);

	static Date GetFromString_S(const string& strTime,const string& strFormat) ;


private:
    //2011-4-14 ����m_isNull ��־�����Ƿ�Ϊ��
	bool m_isNull; //�Ƿ�Ϊ��
	base_time64_t m_time;

public:
	/**
	 * �ȴ�ʱ�䣨��ͺ��룩
	 */
	static void WaitSeconds(long nSeconds,long lMicroSeconds=0L);

	/** 
	 * ���������ں�ʱ����ʱ��
	 * ����ʱ������ڵĸ�ʽΪ YYYYMMDD HHMMSS
	 */
	static base_time64_t PackTime(long nDate,long nTime);

public:
    // ���ڲ�������
	/**
	 * ��ȡ�¸��£�����ͷ��ظ�ʽYYYYMM
	 */
    static long GetNextMonth(long nMonth);

	/**
	 * �õ�ǰ���£�����ͷ��ظ�ʽYYYYMM
	 */
    static long GetPreviousMonth(long nMonth);

	/**
	 * ��ȡ��һ�죬����ͷ��ظ�ʽYYYYMMDD
	 */
    static long GetNextDate(long nDate);

	/**
	 * ��ȡǰһ�죬����ͷ��ظ�ʽYYYYMMDD
	 */
    static long GetPreviousDate(long nDate);

	/**
	 * ��ȡ�¸��µĵ�һ�죬����ͷ��ظ�ʽYYYYMMDD
	 */
    static long GetNextMonthFirstDate(long nDate);

	/**
	 * ��ȡ���µĵ�һ�죬����ͷ��ظ�ʽYYYYMMDD
	 */
    static long GetMonthFirstDate(long nDate);

	/**
	 * ��ȡ���µ����һ�죬����ͷ��ظ�ʽYYYYMMDD
	 */
    static long GetMonthLastDate(long nDate);

	/**
	 * ����n�죬����ͷ��ظ�ʽYYYYMMDD
	 */
    static long DecreaseDate(long nDate,long nDay);

	/**
	 * ����n�죬����ͷ��ظ�ʽYYYYMMDD
	 */
    static long IncreaseDate(long nDate,long nDay);

	/**
	 * �������ڵ��������
	 */
    static long DifferentDays(long nDate1,long nDate2);
        
	/**
	 * û��ʵ��
	 */
    static long GetWeekStart(long nDate);
	/**
	 * û��ʵ��
	 */
    static long GetPreviousStart(long nDate);
	/**
	 * �õ����ܵĿ�ʼ�ͽ����գ����������ʽΪYYYYMMDD
	 */
    static long GetWeekDates(long nDate,long& nWeekStart,long& nWeekStop);

	/**
	 * û��ʵ��
	 */
    static long GetPreviousWeekDates(long nDate,long& nWeekStart,long& nWeekStop);

	/**
	 * �����ַ�����ʽ��ʱ�����ڴ��õ�������ʱ������ڣ�ʱ������ڸ�ʽΪYYYYMMDD)
	 * �ַ�����ʽΪ YYYY-MM-DD HH:MI:SS
	 */
    static bool ParseStringTime(LPSTR p,long& d,long& t);

public:
    
public:
    //2011-4-14 ���Ӷ����������Ƿ�Ϊ�յ���ز��� by hch

    /*!
    * @brief �����Ƿ�ǿ�
    * @return ���򷵻�true�����򷵻�false
    */
    bool ifNull() const
    {
        return m_isNull;
    }

    /*!
    * @brief ���ö���Ϊ��
    */
    void setNull()
    {
        m_isNull = true;
    }

    /*!
    * @brief ���ö���Ϊ�ǿ�
    */
    void setNotNull()
    {
        m_isNull = false;
    }
    
    static Date GetNextMonthFirstDateTime(const Date& DateIn);
};

__WILLOW_END_NAMESPACE
#endif
