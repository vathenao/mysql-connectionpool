#ifndef  __PLATFORM_DEFINES_H__
#define  __PLATFORM_DEFINES_H__

#ifdef linux
#define _Sleep(x) usleep((x)*1000) 
#elif WIN32
#define _Sleep Sleep
#endif

#ifdef WIN32
#define SEMHANDLE HANDLE
#elif linux
#define SEMHANDLE sem_t
#endif //WIN32

#endif /* __PLATFORM_DEFINES_H__ */

