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

#ifndef DLL_API_EXPORT
#if defined WIN32
#define DLL_API_EXPORT	__declspec(dllexport)
#else
#define DLL_API_EXPORT  
#endif
#endif

#ifndef DLL_API_IMPORT
#if defined WIN32
#define DLL_API_IMPORT	__declspec(dllimport)
#else
#define DLL_API_IMPORT
#endif
#endif

#endif /* __PLATFORM_DEFINES_H__ */

