#include "StdAfx.h"

namespace html
{
   reader::reader()
   {
      m_ptag = NULL;
      m_ptagMain = NULL;
   }

   void reader::BeginParse(DWORD dwAppData, bool &bAbort)
   {
      m_ptag = NULL;
      m_ptagMain = NULL;
      UNUSED_ALWAYS(dwAppData);
      bAbort = false;
   }

   void reader::StartTag(lite_html_tag *pTag, DWORD dwAppData, bool &bAbort)
   {
      UNREFERENCED_PARAMETER(dwAppData);
      if(m_ptag == NULL)
      {
         m_ptag = new html::tag(NULL);
         m_ptagMain = m_ptag;
      }
      else
      {
         html::tag * ptag = new html::tag(m_ptag);
         m_ptag->baseptra().add(ptag);
         m_ptag = ptag;
      }
      m_ptag->set_name(pTag->getTagName());
      if(pTag->getAttributes() != NULL)
      {
         for(int i = 0; i < pTag->getAttributes()->getCount(); i++)
         {
            attribute * pattr = m_ptag->attra().add_new();
            pattr->set_name(pTag->getAttributes()->getAttribute(i).getName().make_lower());
            pattr->set_value(pTag->getAttributes()->getAttribute(i).getValue());
         }
      }
      if(m_ptag->parent() != NULL && pTag->getTagName() == "visual")
      {
         m_ptag = m_ptag->parent();
      }
      bAbort = false;
   }

   void reader::EndTag(lite_html_tag *pTag, DWORD dwAppData, bool &bAbort)
   {
      UNUSED_ALWAYS(pTag);
      UNUSED_ALWAYS(dwAppData);
      if(m_ptag->parent() != NULL && pTag->getTagName() != "visual")
      {
         m_ptag = m_ptag->parent();
      }

      bAbort = false;
   }
   
   void reader::Characters(const string &rText, DWORD dwAppData, bool &bAbort)
   {
      UNREFERENCED_PARAMETER(dwAppData);
      if(m_ptag != NULL)
      {
         html::value * pvalue = new html::value(m_ptag);
         m_ptag->baseptra().add(pvalue);
         pvalue->set_value(rText);
      }
      bAbort = false;
   }
   
   void reader::Comment(const string &rComment, DWORD dwAppData, bool &bAbort)
   {
      UNUSED_ALWAYS(rComment);
      UNUSED_ALWAYS(dwAppData);
      bAbort = false;
   }

   void reader::EndParse(DWORD dwAppData, bool bIsAborted)
   {
      UNUSED_ALWAYS(dwAppData);
      UNUSED_ALWAYS(bIsAborted);
   }

} // namespace html