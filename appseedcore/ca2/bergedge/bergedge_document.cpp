#include "StdAfx.h"

namespace bergedge
{

   document::document(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::document(papp),
      ::userbase::document(papp)
   {
      m_pplatformdocument = NULL;
      m_pnaturedocument = NULL;
   }

   BOOL document::on_new_document()
   {
      if (!::userbase::document::on_new_document())
         return FALSE;

   
      update_all_views(NULL, 0);

      return TRUE;
   }

   document::~document()
   {
   }


   #ifdef _DEBUG
   void document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::userbase::document::dump(dumpcontext);
   }
   #endif //_DEBUG



   ::view * document::get_bergedge_view()
   {
      return get_typed_view < ::view > ();
   }

   void document::set_platform(platform::document * pdoc)
   {
      m_pplatformdocument = pdoc;
      //platform_frame * pframe = pdoc->get_platform_frame();
      //pframe->SetParent(get_bergedge_view());
      //pframe->ModifyStyle(0, WS_CHILD);
      //pframe->ShowWindow(SW_RESTORE);
      //pframe->SetWindowPos(NULL, 0, 0, 200, 200, SWP_SHOWWINDOW);
   }

   void document::set_nature(nature::document * pdoc)
   {
      m_pnaturedocument = pdoc;
      //nature_frame * pframe = pdoc->get_nature_frame();
      //pframe->SetParent(get_bergedge_view());
      //pframe->ModifyStyle(0, WS_CHILD);
      //pframe->SetWindowPos(NULL, 200, 200, 400, 400, SWP_SHOWWINDOW);
   }

   ::bergedge::bergedge * document::get_bergedge()
   {
      return m_pbergedge;
   }


} // namespace bergedge