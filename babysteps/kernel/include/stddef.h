#ifndef _STDDEF_H
#define _STDDEF_H

/* Fundamental types */
typedef int ptrdiff_t;
// typedef unsigned int size_t;
typedef unsigned short wchar_t;

#if __SIZEOF_POINTER__ == 8
typedef unsigned long long size_t;
typedef unsigned long long uintptr_t;
#elif __SIZEOF_POINTER__ == 4
typedef unsigned int size_t;
typedef unsigned int uintptr_t;
#endif

/* Null pointer */
#ifndef NULL
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

/* offsetof macro */
#define offsetof(type, member) ((size_t)&(((type)0)->member))

#endif /* _STDDEF_H */
