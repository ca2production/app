#include "framework.h"
#include <dlfcn.h>


   base_library::base_library(sp(::aura::application) papp) :
      ::object(papp)
   {

      m_plibrary = NULL;

      m_bAutoClose = false;

   }


   base_library::base_library(sp(::aura::application) papp, const char * pszOpen) :
      ::object(papp)
   {

      m_plibrary = NULL;

      m_bAutoClose = false;

      open(pszOpen);

   }


   base_library::~base_library()
   {

      if(m_bAutoClose)
      {

         close();

      }

   }


   bool base_library::open(const char * pszPath, bool bAutoClose)
   {

      if(m_bAutoClose)
      {

         close();

      }

      m_bAutoClose = bAutoClose;

      string strPath(pszPath);

      if(strPath == "os")
      {
         strPath = "ca2os";
      }
      else if(strPath == "os2")
      {
         strPath = "ca2os2";
      }

      if(!str_ends_dup(strPath, ".dylib"))
         strPath += ".dylib";

      if(!str_begins_dup(strPath, "lib"))
         strPath = "lib" + strPath;

      m_plibrary = dlopen(strPath, RTLD_LOCAL | RTLD_LAZY);

      return true;

   }


   bool base_library::close()
   {

      if(m_plibrary != NULL)
      {

         dlclose(m_plibrary);

      }

      return true;

   }


   void * base_library::raw_get(const char * pszElement)
   {

      return dlsym(m_plibrary, pszElement);

   }


   bool base_library::is_opened()
   {

      return m_plibrary != NULL;

   }


   bool base_library::is_closed()
   {

      return m_plibrary == NULL;

   }


   ca2_library::ca2_library(sp(::aura::application) papp) :
      ::object(papp),
      base_library(papp)
   {

   }


   ca2_library::ca2_library(sp(::aura::application) papp, const char * pszOpen) :
      ::object(papp),
      base_library(papp, pszOpen)
   {

   }


   ca2_library::~ca2_library()
   {

   }


   bool ca2_library::open(const char * pszPath, bool bAutoClose)
   {

      return base_library::open(pszPath, bAutoClose);

   }


