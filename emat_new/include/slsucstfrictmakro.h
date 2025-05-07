#pragma once

#if !defined(SL_EXP)
 #if defined(WIN32) || defined(WIN64)
   #ifdef SL_EXPORT
   #ifdef SL_FRICT
    #define SL_EXP  __declspec(dllexport)
   #else 
    #define SL_EXP
   #endif
  #else
    #ifdef SL_FRICT
     #define SL_EXP  __declspec(dllimport)
    #else
     #define SL_EXP
    #endif
  #endif
 #else
  #define SL_EXP
 #endif
#endif

