#include "StdAfx.h"

namespace user
{

   button::button(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp)
   {
      m_iHover    = -1;
      m_bEnabled  = true;
      m_echeck    = check::unchecked;
   }

   button::~button(void)
   {
      
   }


   void button::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::user::window_interface::_001InstallMessageHandling(pinterface);

   //   IGUI_WIN_MSG_LINK(WM_SIZE                    , pinterface, this, &button::OnParentSize);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN             , pinterface, this, &button::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP               , pinterface, this, &button::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE               , pinterface, this, &button::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_MOUSELEAVE              , pinterface, this, &button::_001OnMouseLeave);
      IGUI_WIN_MSG_LINK(WM_SIZE                    , pinterface, this, &button::_001OnSize);
      //IGUI_WIN_MSG_LINK(WM_CREATE                  , pinterface, this, &button::_001OnCreate);
   //   IGUI_WIN_MSG_LINK(CVmsGenApp::APPM_LANGUAGE  , pinterface, this, &button::_001OnAppLanguage);
   }

   void button::_001OnDraw(::ca::graphics * pdc)
   {
      string str(m_langstrButtonText.get(get_app()));

      pdc->SelectObject(_001GetFont());

      rect rectClient;
      GetClientRect(rectClient);
      pdc->FillSolidRect(rectClient, RGB(127, 127, 127));
      if(m_iHover == 0)
      {
         pdc->SetTextColor(RGB(0, 100, 255));
      }
      else
      {
         pdc->SetTextColor(RGB(0, 0, 0));
      }
      pdc->DrawText(str, m_rectText, DT_LEFT | DT_TOP);
   }

   void button::_001OnLButtonDown(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      if(hit_test(pmouse->m_pt) >= 0)
      {
         g_pwndLastLButtonDown = this;
         pmouse->set_lresult(1);
         pobj->m_bRet = true;
      }
   }

   bool button::_001IsPressed()
   {
      return g_pwndLastLButtonDown == this;
   }

   void button::_001OnLButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      if(hit_test(pmouse->m_pt) >= 0 && g_pwndLastLButtonDown == this)
      {
         g_pwndLastLButtonDown = NULL;
         ::user::control_event ev;
         ev.m_puie = this;
         ev.m_eevent = ::user::event_button_clicked;
         if(get_form() != NULL)
         {
            get_form()->SendMessage(
               ::user::message_event, 0, (LPARAM) &ev);
         }
         else
         {
            GetParent()->SendMessage(
               ::user::message_event, 0, (LPARAM) &ev);
         }
         pobj->m_bRet = true;
         pmouse->set_lresult(1);
      }
      
   }

   void button::_001OnMouseMove(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      if(get_form_list() == NULL)
      {
         int iHover = hit_test(pmouse->m_pt);
         if(iHover != m_iHover)
         {
            int iOldHover = m_iHover;
            m_iHover = iHover;
            _001RedrawWindow();
            if(iOldHover == -1)
            {
               ::user::control_event ev;
               ev.m_puie = this;
               ev.m_eevent = ::user::event_mouse_enter;
               GetParent()->SendMessage(
                 ::user::message_event, 0, (LPARAM) &ev);
            }
            else if(iHover == -1)
            {
               ::user::control_event ev;
               ev.m_puie = this;
               ev.m_eevent = ::user::event_mouse_leave;
               GetParent()->SendMessage(
                 ::user::message_event, 0, (LPARAM) &ev);
            }
            track_mouse_hover();
         }
         pobj->m_bRet = false;
      }
   }

   void button::_001OnMouseLeave(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)
      if(get_form_list() == NULL)
      {
         int iOldHover = m_iHover;
         m_iHover = -1;
         if(iOldHover >= 0)
         {
            _001RedrawWindow();
            ::user::control_event ev;
            ev.m_puie = this;
            ev.m_eevent = ::user::event_mouse_leave;
            if(GetParent() != NULL)
            {
               GetParent()->SendMessage(message_event, 0, (LPARAM) &ev);
            }
            track_mouse_leave();
         }
         pbase->m_bRet = false;
      }
   }

   int button::hit_test(point pt)
   {
      rect rectWindow;
      GetWindowRect(rectWindow);
      if(rectWindow.contains(pt))
         return 0;
      else
         return -1;
   }

   ::ca::font * button::_001GetFont(void)
   {
      return NULL;
   }

   void button::ResizeToFit()
   {
   }

   void button::_001SetButtonText(const char * lpcszText)
   {
      m_langstrButtonText.set_text(lpcszText);
   }

   void button::_001SetButtonTextId(const char * lpcszText)
   {
      m_langstrButtonText.set_text_id(lpcszText);
   }


   bool button::_001IsWindowEnabled()
   {
      return m_bEnabled;
   }

   void button::_001EnableWindow(bool bEnable)
   {
      m_bEnabled = bEnable;
   }

   void button::_001SetCheck(check::e_check echeck, bool bUser)
   {
      UNREFERENCED_PARAMETER(bUser);
      m_echeck = echeck;
   }


   check::e_check button::_001GetCheck()
   {
      return m_echeck;
   }

   void button::_001SetState(state::state state, bool bUser)
   {
      UNREFERENCED_PARAMETER(bUser);
      m_state = state;
   }

   state::state button::_001GetState()
   {
      return m_state;
   }

   void button::_001OnSize(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)
      _001Layout();
      pbase->m_bRet = false;
   }

   void button::_001Layout()
   {
      rect rect;
      GetClientRect(rect);
      rect.left   += 5;
      rect.top    += 5;

      m_rectText = rect;
   }

   string button::_001GetButtonText()
   {
      return m_langstrButtonText.get(get_app());
   }


   void button::VirtualOnSize()
   {
      _001Layout();
   }

   bool button::create_control(class control::descriptor * pdescriptor)
   {
      if(!create(
         NULL,
         NULL,
         WS_VISIBLE | WS_CHILD, 
         rect(0, 0, 0, 0), 
         pdescriptor->m_pform, 
         pdescriptor->m_id))
      {
         TRACE("Failed to create control");
         return false;
      }
      return control::create_control(pdescriptor);
   }

   int button::get_hover()
   {
      POINT pt;
      // netshare
      // System.get_cursor_position(&pt);
      System.get_cursor_pos(&pt);
      return hit_test(pt);
   }

} // namespace user