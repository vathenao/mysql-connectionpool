#ifndef  __WILLOW_CONFIG_H__
#define  __WILLOW_CONFIG_H__

//-------------------------------------------------------------------------
// __WILLOW_HAS_NAMESPACES is a hook so that users can disable namespaces
// without having to edit library headers.
//-------------------------------------------------------------------------
#define __WILLOW_HAS_NAMESPACES

//-------------------------------------------------------------------------
// Lifetime Singleton Support
//-------------------------------------------------------------------------
#define ATEXIT_FIXED

//-------------------------------------------------------------------------
// Integer Support
//-------------------------------------------------------------------------
#if defined(__LP64__ ) || defined(__LP64) 
# define __WM_WORD_64 
#endif

#endif /* __WILLOW_CONFIG_H__ */

