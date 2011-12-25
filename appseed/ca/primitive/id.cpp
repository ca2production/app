#include "StdAfx.h"



id::id(const char * psz)
{
   operator = (::radix::system::id(psz));
}

#ifdef _AMD64_
id::id(int i)
{
   operator = (::radix::system::id(i));
}
#endif

id::id(unsigned int user)
{
   operator = (::radix::system::id((index)user));
}

id::id(index i)
{
   operator = (::radix::system::id(i));
}

id::id(const string & str)
{
   operator = (::radix::system::id((const char * ) str));
}

id::id(const string_interface & str)
{
   operator = (::radix::system::id(string(str)));
}

id & id::operator = (const char * psz)
{
   operator = (::radix::system::id(psz));
   return *this;
}

id & id::operator = (const string & str)
{
   operator = (::radix::system::id(str));
   return *this;
}

id & id::operator = (const string_interface & str)
{
   operator = (::radix::system::id(string(str)));
   return *this;
}


id_space::id_space()
{
   m_pmutex = new mutex();
   m_pida = new sort_array < id, const id & >;
}

// id_space is static, it goes aways only and with the application
// so avoid freeing errors when even crash translators does not exist.

id_space::~id_space()
{

   /*try
   {
      if(m_pmutex != NULL)
      {
         delete m_pmutex;
      }
   }
   catch(...)
   {
   }

   try
   {
      for(index i = 0; i < this->get_count(); i++)
      {
         try
         {
            if(this->element_at(i).is_text())
            {
               free((void *) this->element_at(i).m_psz);
            }
         }
         catch(...)
         {
         }
      }
   }
   catch(...)
   {
   }*/
}

id id_space::operator()(const char * psz)
{
   single_lock sl(m_pmutex, TRUE);
   id idSearch;
   idSearch.raw_set(psz);
   index iIndex = 0;
   if(!m_pida->BaseSortFind(idSearch, iIndex))
   {
      if(idSearch.is_text())
      {
         id id;
         id.raw_set(_strdup(psz));
         m_pida->insert_at(iIndex, id);
      }
      else
      {
         m_pida->insert_at(iIndex, idSearch);
      }
   }
   return m_pida->element_at(iIndex);
}

id id_space::operator()(index i)
{
   single_lock sl(m_pmutex, TRUE);
   id idSearch;
   idSearch.raw_set((uint64_t) i);
   index iIndex = 0;
   if(!m_pida->BaseSortFind(idSearch, iIndex))
   {
      m_pida->insert_at(iIndex, idSearch);
   }
   return m_pida->element_at(iIndex);
}

string id::str()
{
   if(m_chType == IDTYPE_TYPE_TEXT)
      return m_psz;
   else if(m_chType == IDTYPE_TYPE_NUMBER)
   {
      string str;
      str.Format("%d", m_ui);
      return str;
   }
   else
      return "";
 }
