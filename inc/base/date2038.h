#ifndef DATE2038_H
#define DATE2038_H

#include <time.h>


#define DEFAULT_TIME_ZONE_OFFSET 8

typedef long long base_time64_t ;

base_time64_t base_pivot_time_t (const time_t * now, base_time64_t *t);
base_time64_t base_mktime64 (struct tm *t);
struct tm *base_localtime64_r (const base_time64_t *t, struct tm *p);
struct tm *base_pivotal_localtime_r (const time_t * now, const time_t * t, struct tm *p);
struct tm *base_gmtime64_r (const base_time64_t *t, struct tm *p);
struct tm *base_pivotal_gmtime_r (const time_t * now, const time_t * t, struct tm *p);

#endif
