#pragma once

#include "bzlib.h"

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef libbsdif_DLL
   #define libbsdif_API  __declspec(dllexport)
#elif defined(USE_BZ_DLL)
   #define libbsdif_API  __declspec(dllimport)
#elif defined(libbsdif_LIB)
   #define libbsdif_API  extern
#else 
   #define libbsdif_API  extern
#endif

template<class T1, class T2>
int err(int i, const char* str, T1 arg1, T2 arg2) {
   char lastErrorTxt[1024];
   FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,GetLastError(),0,lastErrorTxt,1024,NULL);
   printf("%s",lastErrorTxt);
   printf(str, arg1, arg2);
   return (i);
}
template<class T>
int err(int i, const char* str, T arg) {
   char lastErrorTxt[1024];
   FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,GetLastError(),0,lastErrorTxt,1024,NULL);
   printf("%s",lastErrorTxt);
   printf(str, arg);
   return (i);
}
int err(int i, const char* str);
template<class T>
int errx(int i, const char* str, T arg) {
   printf(str, arg);
   return (i);
}
int errx(int i, const char* str);

libbsdif_API int bsdiff(const char * oldfile, const char * newfile, const char * patchfile);
libbsdif_API int bspatch(const char * oldfile, const char * newfile, const char * patchfile);