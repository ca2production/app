#include "framework.h"


#ifndef METROWIN

#if defined(LINUX) || defined(ANDROID)
#include <fcntl.h>
#include <unistd.h>
#endif


namespace core
{


   pipe::pipe(bool bInherit)
   {

      m_pchBuf = NULL;

#ifdef WINDOWS

      m_sa.nLength = sizeof(SECURITY_ATTRIBUTES);
      m_sa.bInheritHandle = bInherit ? TRUE : FALSE;
      m_sa.lpSecurityDescriptor = NULL;
      m_hRead = NULL;
      m_hWrite = NULL;

#else

      m_fd[0] = -1;
      m_fd[1] = -1;

#endif


   }

   pipe::~pipe()
   {

      if(m_pchBuf != NULL)
      {
         free(m_pchBuf);
      }

#ifdef WINDOWS

      ::CloseHandle(m_hRead);
      ::CloseHandle(m_hWrite);

