#ifndef  __PLATFORM_DEFINES_H__
#define  __PLATFORM_DEFINES_H__

#ifdef linux
#define XDBC_Sleep(x) usleep((x)*1000) 
#elif WIN32
#define XDBC_Sleep Sleep
#endif

#ifdef WIN32
#define SEMHANDLE HANDLE
#elif linux
#define SEMHANDLE sem_t
#endif //WIN32

#endif /* __PLATFORM_DEFINES_H__ */

