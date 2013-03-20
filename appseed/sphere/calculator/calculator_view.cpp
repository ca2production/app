﻿#include "framework.h"


namespace calculator
{


   view::view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp)
   {

   }


   view::~view()
   {

   }


   void view::install_message_handling(::ca::message::dispatch * pinterface)
   {

      ::userbase::view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);

      //   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &view::_001OnTabClick);
      IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &view::_001OnWavePlayerEvent);
      //connect_command(ID_FILE_PRINT, ::userbase::view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_DIRECT, ::userbase::view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_PREVIEW, ::userbase::view::OnFilePrintPreview)
      //  IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
      //   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);


   }

#ifdef DEBUG
   void view::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
#endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // view message handlers

   // vmpLightView.cpp : implementation of the view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // view


   bool view::pre_create_window(CREATESTRUCT& cs)
   {

      cs.style &= ~WS_EX_CLIENTEDGE;

      return ::userbase::view::pre_create_window(cs);

   }


   void view::_001OnInitialUpdate(::ca::signal_object * pobj)
   {
      ::userbase::view::_001OnInitialUpdate(pobj);


   }

   ::user::interaction* view::get_guie()
   {
      return this;
   }

   void view::on_update(::view* pSender, LPARAM lHint, ::ca::object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }

   ::user::interaction* view::BackViewGetWnd()
   {
      return this;
   }
   void view::_001OnDestroy(::ca::signal_object * pobj)
   {
      ::userbase::view::_001OnDestroy(pobj);

   }



   void view::_001OnSize(::ca::signal_object * pobj)
   {
      
      UNREFERENCED_PARAMETER(pobj);

   }

   void view::_001OnPaint(::ca::signal_object * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   void view:: _001OnDraw(::ca::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
   }

   void view::_001OnCreate(::ca::signal_object * pobj)
   {
      if(pobj->previous())
         return;


   }
   void view::_001OnContextMenu(::ca::signal_object * pobj)
   {
//      SCAST_PTR(::ca::message::context_menu, pcontextmenu, pobj)
//         point point = pcontextmenu->GetPoint();

   }


   void view::_001OnTabClick(int32_t iTab)
   {
      if(iTab == 1)
      {
         System.simple_message_box(NULL, "Playlist");
      }
   }

   void view::_001OnWavePlayerEvent(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::ca::message::base, pbase, pobj)
   }

   void view::_001OnUpdateViewEncoding(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::ca::message::update_cmd_ui, pupdatecmdui, pobj)
   }
   void view::_001OnViewEncoding(::ca::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::ca::message::command, pcommand, pobj)
   }


   /*xxxvoid view::data_on_after_change(int32_t iConfigurationId, ::database::id & idIndex CVmsDataUpdateHint * puh)
   {
   if(iConfigurationId == _vmsp::CConfiguration::CfgKaraokeEncoding)
   {
   PrepareLyricLines();
   RedrawWindow();
   }
   }*/


   void view::_001OnSetCursor(::ca::signal_object * pobj)
   {

      SCAST_PTR(::ca::message::mouse, pmouse, pobj)

      pmouse->m_ecursor = ::visual::cursor_arrow;

   }


   document * view::get_document()
   {

      return dynamic_cast < document * > (::userbase::view::get_document());

   }


} // namespace calculator




