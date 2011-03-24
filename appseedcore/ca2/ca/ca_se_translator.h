/*
 Copyright (c) 2001 
 Author: Konstantin Boukreev 
 E-mail: konstantin@mail.primorye.ru 
 Created: 25.12.2001 14:47:20
 Version: 1.0.0
 
 Permission to use, copy, modify, distribute and sell this software
 and its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and
 that both that copyright notice and this permission notice appear
 in supporting documentation.  Konstantin Boukreev makes no representations
 about the suitability of this software for any purpose.
 It is provided "as is" without express or implied warranty.

 wrapper class for _set_se_translator API
 maps Win32 exceptions (C structured exceptions) into C++ typed exceptions.
*/

#pragma once

#ifdef _WIN64
#error Win64 is not supported
#endif

#include <eh.h>
#include "_000ca2api12000/AtlAux2.h"


class se_translator :
   public aux_thunk < se_translator >,
   virtual public ::radix::object
{      
 public:
   se_translator();
   virtual ~se_translator();

   void translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers);
   static string name(unsigned int uiCode);
   static string description(unsigned int uiCode);


   bool attach();
   bool detach();

 private:
    bool                      m_bSet;
    _se_translator_function   m_pfn;
};

