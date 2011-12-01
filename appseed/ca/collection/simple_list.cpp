#include "StdAfx.h"

/////////////////////////////////////////////////////////////////////////////
// simple_list

void simple_list::add_head(void * p)
{
   ASSERT(p != NULL);
   ASSERT(*GetNextPtr(p) == NULL);

   *GetNextPtr(p) = m_pHead;
   m_pHead = p;
}

BOOL simple_list::remove(void * p)
{
   ASSERT(p != NULL);

   if (m_pHead == NULL)
      return FALSE;

   BOOL bResult = FALSE;
   if (m_pHead == p)
   {
      m_pHead = *GetNextPtr(p);
      DEBUG_ONLY(*GetNextPtr(p) = NULL);
      bResult = TRUE;
   }
   else
   {
      void * pTest = m_pHead;
      while (pTest != NULL && *GetNextPtr(pTest) != p)
         pTest = *GetNextPtr(pTest);
      if (pTest != NULL)
      {
         *GetNextPtr(pTest) = *GetNextPtr(p);
         DEBUG_ONLY(*GetNextPtr(p) = NULL);
         bResult = TRUE;
      }
   }
   return bResult;
}

