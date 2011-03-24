#include "StdAfx.h"

namespace gen
{

   file_association::file_association(::ca::application * papp) :
      ca(papp)
   {
      m_hkeyClassesRoot = NULL;
   }

   file_association::~file_association()
   {

   }


   HKEY file_association::GetHKEYClassesRoot()
   {
      return m_hkeyClassesRoot;

   }


   bool file_association::Initialize()
   {
      if(ERROR_SUCCESS !=
         RegOpenKey(
            HKEY_CLASSES_ROOT,
            NULL,
            &m_hkeyClassesRoot))
      return false;

      return true;
   }

} // namespace VmsGen
