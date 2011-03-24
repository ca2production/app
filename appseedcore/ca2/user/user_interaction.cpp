#include "StdAfx.h"



namespace user
{

   interaction * interaction::g_pguieMouseMoveCapture = NULL;

   interaction::interaction()
   {
      m_eappearance           = appearance_normal;
      m_pimpl                 = NULL;
      m_bCursorInside         = false;
      m_nFlags                = 0;
      m_pguieOwner            = NULL;
      m_pguie                 = this; // initially set to this
      m_pthread               = NULL;
      m_ecursor               = ::visual::cursor_default;
      m_iModal                = 0;
      m_iModalCount           = 0;
      m_bRectOk               = false;
      m_bVisible              = true;
   }

   interaction::interaction(::ca::application * papp) :
      ca(papp),
      ::user::window_interface(papp)
   {
      m_eappearance           = appearance_normal;
      m_pimpl                 = NULL;
      m_bCursorInside         = false;
      m_nFlags                = 0;
      m_pguieOwner            = NULL;
      m_pguie                 = this; // initially set to this
      m_pthread               = NULL;
      m_ecursor               = ::visual::cursor_default;
      m_iModal                = 0;
      m_iModalCount           = 0;
      m_bRectOk               = false;
      m_bVisible              = true;
   }

   interaction::~interaction()
   {
      CSingleLock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      m_uiptraChild.remove_all();
      ::radix::object * pobjTwf = NULL;
      if(m_papp != NULL && &System != NULL)
      {
         pobjTwf = System.get_twf();
      }
      ::ca::lock lock(pobjTwf);
/*      if(GetTopLevelParent() != NULL
      && GetTopLevelParent() != this)
      {
         ::ca::window * pwnd = GetTopLevelParent()->get_wnd();
         if(pwnd != NULL)
         {
            
//            GetTopLevelParent()->get_wnd()->mouse_hover_remove(this);
         }
      }*/
/*      if(m_pthread != NULL)
      {
         m_pthread->remove(this);
      }
      else
      {
   //      TRACE0("interaction::m_pthread null");
      }*/
/*      if(get_app() != NULL && &System != NULL)
      {
         try
         {
            System.GetThread()->remove(this);
         }
         catch(...)
         {
         }
         try
         {
            System.remove(this);
         }
         catch(...)
         {
         }
      }*/
      if(m_pimpl != NULL && m_pimpl != this)
      {
         gen::del(m_pimpl);
      }
   }

   ::ca::graphics * interaction::GetDC()
   {
     if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->GetDC();
   }

   BOOL interaction::ReleaseDC(::ca::graphics * pdc)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->ReleaseDC(pdc);
   }

   BOOL interaction::IsChild(interaction * pWnd)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsChild(pWnd);
   }

   window_interface * interaction::window_interface_get_parent()
   {
      return GetParent();
   }

   interaction * interaction::GetParent()
   {
      if(m_pimpl == NULL || m_pimpl == this)
         return NULL;
      else
         return m_pimpl->GetParent();
   }

   interaction * interaction::SetParent(interaction * pguieParent)
   {
      if(pguieParent == this
      || pguieParent == m_pguie
      || pguieParent == m_pimpl)
      {
         return GetParent();
      }
      ::ca::window * pwindowImpl = dynamic_cast < ::ca::window * > (m_pimpl);
      interaction * pparentOld = GetParent();
      if(pparentOld != NULL)
         pparentOld->m_uiptraChild.remove(this);
      if(pwindowImpl != NULL)
      {
         if(pguieParent != NULL)
         {
            rect rect;
            GetWindowRect(rect);
            pguieParent->ScreenToClient(rect);
            if(!create(NULL, NULL, WS_VISIBLE, rect, pguieParent, m_id, NULL))
               return NULL;
         }
         else
         {
            if(m_pimpl == NULL || m_pimpl->SetParent(pguieParent) == NULL)
               return NULL;
         }
      }
      else
      {
         if(m_pimpl == NULL || m_pimpl->SetParent(pguieParent) == NULL)
            return NULL;
      }
      on_set_parent(pguieParent);
      return pparentOld;
   }

   void interaction::GetClientRect(LPRECT lprect)
   {
      lprect->left      = (LONG) 0;
      lprect->top       = (LONG) 0;
      lprect->right     = (LONG) m_rectParentClient.width();
      lprect->bottom    = (LONG) m_rectParentClient.height();
   }

   void interaction::GetWindowRect(LPRECT lprect)
   {
      rect64 rectWindow;
      GetWindowRect(rectWindow);
      lprect->left      = (LONG) rectWindow.left;
      lprect->top       = (LONG) rectWindow.top;
      lprect->right     = (LONG) rectWindow.right;
      lprect->bottom    = (LONG) rectWindow.bottom;
   }

   void interaction::GetClientRect(__rect64 * lprect)
   {
      lprect->left      = 0;
      lprect->top       = 0;
      lprect->right     = m_rectParentClient.width();
      lprect->bottom    = m_rectParentClient.height();
   }

   void interaction::GetWindowRect(__rect64 * lprect)
   {
      *lprect = m_rectParentClient;
      if(GetParent() != NULL)
      {
         GetParent()->ClientToScreen(lprect);
      }
   }

   bool interaction::SetWindowPos(int z, int x, int y,
               int cx, int cy, UINT nFlags)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->SetWindowPos(z, x, y, cx, cy, nFlags);
   }


   id interaction::GetDlgCtrlId()
   {
      if(m_pimpl == NULL)
         return "";
      else
         return m_pimpl->GetDlgCtrlId();
   }

   void interaction::_001InstallMessageHandling(win::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(WM_CREATE      , pinterface, this, &interaction::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_DESTROY     , pinterface, this, &interaction::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE        , pinterface, this, &interaction::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_MOVE        , pinterface, this, &interaction::_001OnMove);
      IGUI_WIN_MSG_LINK(WM_USER + 184  , pinterface, this, &interaction::_001OnUser184);
   }

   void interaction::_001OnDestroy(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      
      raw_array < user::interaction  * > uiptra;
      CSingleLock sl(&m_pthread->m_mutex, TRUE);
      m_uiptraChild.get_array(uiptra);
      sl.Unlock();
      for(int i = 0; i < uiptra.get_count(); i++)
      {
         user::interaction  * pui = uiptra[i];
         pui->DestroyWindow();
      }
   }

   void interaction::_001OnSize(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_001OnMove(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   void interaction::_001DrawThis(::ca::graphics * pgraphics)
   {
      if(m_pguie != NULL)
      {
         rect64 rectWindow;
         GetWindowRect(rectWindow);
         pgraphics->SetViewportOrg(point(rectWindow.top_left()));
         pgraphics->SelectClipRgn(NULL);
         m_pguie->_001OnDraw(pgraphics);
      }
      else
      {
         _001OnDraw(pgraphics);
      }
   }

   void interaction::_001DrawChildren(::ca::graphics *pdc)
   {
      
      if(m_pguie != NULL && m_pguie != this)
      {
         m_pguie->_001DrawChildren(pdc);
      }
      else
      {
         ::user::interaction * pui = get_bottom_child();
         while(pui != NULL)
         {
            try
            {
               if(pui->m_bVisible)
               {
                  pui->_000OnDraw(pdc);
               }
            }
            catch(...)
            {
            }
            try
            {
               pui = pui->above_sibling();
            }
            catch(...)
            {
               break;
            }
         }
      }
   }

   void interaction::_000OnDraw(::ca::graphics *pdc)
   {
      if(!m_bVisible)
         return;
      if(m_pguie != NULL && m_pguie != this)
      {
         m_pguie->_000OnDraw(pdc);
      }
      else
      {
         _001DrawThis(pdc);
         _001DrawChildren(pdc);
      }
   }

   void interaction::_001OnCreate(::gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      if(GetParent() == NULL)
      {
         System.add_frame(this);
      }

   }




   void interaction::_000OnMouse(::user::win::message::mouse * pmouse)
   {
      try
      {
         if(!_001IsPointInside(pmouse->m_pt))
            return;
      }
      catch(...)
      {
         return;
      }
      // these try catchs are needed for multi threading : multi threaded windows: the hell
      // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
      user::interaction * pui = get_top_child();
      int iSize;
      try
      {
         while(pui != NULL)
         {
            try
            {
               if(pui->IsWindowVisible() && pui->_001IsPointInside(pmouse->m_pt))
               {
                  try
                  {
                     pui->_000OnMouse(pmouse);
                     if(pmouse->m_bRet)
                        return;
                  }
                  catch(...)
                  {
                  }
               }
               pui = pui->under_sibling();
            }
            catch(...)
            {
            }
         }
      }
      catch(...)
      {
      }
      try
      {
         if(m_pimpl == NULL)
            return;
         (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < gen::signal_object * > (pmouse));
         if(pmouse->get_lresult() != 0)
            return;
      }
      catch(...)
      {
      }
   }

   void interaction::_000OnKey(::user::win::message::key * pkey)
   {
      point ptCursor;
      System.get_cursor_pos(&ptCursor);
      if(!pkey->m_bRet)
      {
         // these try catchs are needed for multi threading : multi threaded windows: the hell
         // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
         ::user::interaction * pui = get_top_child();
         int iSize;
         try
         {
            while(pui != NULL)
            {
               try
               {
                  if(pui->IsWindowVisible())
                  {
                     try
                     {
                        pui->_000OnKey(pkey);
                        if(pkey->m_bRet)
                           return;
                     }
                     catch(...)
                     {
                     }
                  }
                  pui = pui->under_sibling();
               }
               catch(...)
               {
               }
            }
         }
         catch(...)
         {
         }
         try
         {
            (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < gen::signal_object * > (pkey));
            if(pkey->get_lresult() != 0)
               return;
         }
         catch(...)
         {
         }
      }
   }

   void interaction::_001OnMouseEnter(gen::signal_object * pobj)
   {
      /*
      for(int i = 0; i < m_uiptra.get_size(); i++)
      {
         if(m_uiptra[i]->_001IsVisible()
            && m_uiptra[i]->_001IsPointInside(point)
            && !m_uiptra[i]->m_bCursorInside)
         {
            m_uiptra[i]->m_bCursorInside = true;
            m_uiptra[i]->_001OnMouseEnter(wparam, lparam, lresult);
         }
      }
      */
      pobj->m_bRet = false;
   }


   void interaction::_001OnMouseLeave(gen::signal_object * pobj)
   {

      interaction * pui = get_top_child();
      while(pui != NULL)
      {
         if(pui->m_bCursorInside)
         {
            pui->m_bCursorInside = false;
            pui->_001OnMouseLeave(pobj);
            pui->_002OnMouseLeave(pobj);
         }
         pui = pui->under_sibling();
      }
      pobj->m_bRet = false;
   }

   interaction * interaction::_001FromPoint(point64 pt, bool bTestedIfParentVisible)
   {
      if(bTestedIfParentVisible)
      {
         if(!m_bVisible 
         || !_001IsPointInside(pt)) // inline version - do not need pointer to the function
            return NULL;
      }
      else
      {
         if(!IsWindowVisible()
         || !_001IsPointInside(pt)) // inline version - do not need pointer to the function
         return NULL;
      }
      interaction * pui = get_top_child();
      while(pui != NULL)
      {
         interaction * puie = pui->_001FromPoint(pt, true);
         if(puie != NULL)
            return puie;
         pui = pui->under_sibling();
      }
      return this;
   }

   bool interaction::_001IsPointInside(point64 pt)
   {
      rect64 rect;
      GetWindowRect(rect);
      return rect.contains(pt);
   }

   void interaction::_001OnKeyDown(gen::signal_object * pobj)
   {
      if(System.get_keyboard_focus() != this
         && System.get_keyboard_focus() != NULL)
      {
         System.get_keyboard_focus()->keyboard_focus_OnKeyDown(pobj);
      }
   }

   void interaction::_001OnKeyUp(gen::signal_object * pobj)
   {
      if(System.get_keyboard_focus() != this
         && System.get_keyboard_focus() != NULL)
      {
         System.get_keyboard_focus()->keyboard_focus_OnKeyUp(pobj);
      }
   }

   void interaction::_001OnChar(gen::signal_object * pobj)
   {
      if(System.get_keyboard_focus() != this
         && System.get_keyboard_focus() != NULL)
      {
         System.get_keyboard_focus()->keyboard_focus_OnChar(pobj);
      }
   }

   //void interaction::_001OnTimer(gen::signal_object * pobj)
   //{
      /*for(int i = 0; i < m_uiptra.get_size(); i++)
      {
         m_uiptra[i]->_001OnTimer(pobj);
         m_uiptra[i]->_002OnTimer(pobj);
      }*/
     // pobj->m_bRet = false;
   //}


   void interaction::on_delete(::ca::ca * pca)
   {
   }

   interaction * interaction::GetChildByName(const char * pszName, int iLevel)
   {
      interaction * pui = get_top_child();
      while(pui != NULL)
      {
         if(pui->m_strName == pszName)
         {
            return pui;
         }
         pui = pui->under_sibling();
      }
      interaction * pchild;
      if(iLevel > 0 || iLevel == -1)
      {
         if(iLevel > 0)
         {
            iLevel--;
         }
         interaction * pui = get_top_child();
         while(pui != NULL)
         {
            pchild = pui->GetChildByName(pszName, iLevel);
            if(pchild != NULL)
               return pchild;
            pui = pui->under_sibling();
         }
      }
      return NULL;
   }


   interaction * interaction::GetChildById(id id, int iLevel)
   {
      interaction * pui = get_top_child();
      while(pui != NULL)
      {
         if(pui->m_id == id)
         {
            return pui;
         }
         pui = pui->under_sibling();
      }
      interaction * pchild;
      if(iLevel > 0 || iLevel == -1)
      {
         if(iLevel > 0)
         {
            iLevel--;
         }
         interaction * pui = get_top_child();
         while(pui != NULL)
         {
            pchild = pui->GetChildById(id, iLevel);
            if(pchild != NULL)
               return pchild;
            pui = pui->under_sibling();
         }
      }
      return NULL;
   }

   /*
   void interaction::_001SetWindowPos(const ::ca::window* pWndInsertAfter, int x, int y,
               int cx, int cy, UINT nFlags)
   {
      SetWindowPos(pWndInsertAfter, x, y, cx, cy, nFlags);
   }

   void interaction::_001SetFocus()
   {
   //   SetFocus();
   }

   void interaction::_001ShowWindow(int iShow)
   {
      _001SetVisible(iShow != SW_HIDE);
   }

   void interaction::_001ScreenToClient(LPPOINT lppoint)
   {
      ScreenToClient(lppoint);
   }
   */




   void interaction::_002OnLButtonDown(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnLButtonUp(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnMouseMove(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnMouseEnter(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnMouseLeave(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnKeyDown(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnKeyUp(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_002OnTimer(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   // pbase object should be allocated with new in
   // base or derived object and will be delete after
   // handling
   LRESULT interaction::SendMessage(win::message::base * pbase)
   {
      message_handler(pbase);
      return pbase->get_lresult();
   }

   // pbase object should be allocated with new in
   // base or derived object and will be delete after
   // handling
   BOOL interaction::PostMessage(win::message::base * pbase)
   {
      return PostMessage(WM_APP + 2014, 1, (LPARAM) pbase);
   }

   LRESULT interaction::SendMessage(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else 
         return m_pimpl->SendMessage(uiMessage, wparam, lparam);
   }

   BOOL interaction::IsWindowVisible()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else 
         return m_pimpl->IsWindowVisible();
   }

   BOOL interaction::EnableWindow(BOOL bEnable)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else 
         return m_pimpl->EnableWindow(bEnable);
   }

   BOOL interaction::ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else 
         return m_pimpl->ModifyStyle(dwRemove, dwAdd,  nFlags);
   }

   BOOL interaction::ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else 
         return m_pimpl->ModifyStyleEx(dwRemove, dwAdd, nFlags);
   }

   BOOL interaction::ShowWindow(int nCmdShow)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else 
      {
         BOOL b = m_pimpl->ShowWindow(nCmdShow);
         return b;
      }

   }

   BOOL interaction::IsFrameWnd()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else 
         return m_pimpl->IsFrameWnd();
   }

   BOOL interaction::IsWindowEnabled()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else 
         return m_pimpl->IsWindowEnabled();
   }

   frame_window* interaction::GetTopLevelFrame()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else 
         return m_pimpl->GetTopLevelFrame();
   }

   void interaction::SendMessageToDescendants(UINT message, WPARAM wparam, LPARAM lparam, BOOL bDeep, BOOL bOnlyPerm)
   {
      if(m_pimpl == NULL)
         return;
      else 
         return m_pimpl->SendMessageToDescendants(message, wparam, lparam, bDeep, bOnlyPerm);
   }


   void interaction::pre_translate_message(gen::signal_object * pobj)
   {
      if(m_pimpl == NULL)
         return;
      else 
         return m_pimpl->pre_translate_message(pobj);
   }

   HWND interaction::_get_handle()
   {
      try
      {
         if(get_wnd() == NULL)
            return NULL;
      }
      catch(...)
      {
         return NULL;
      }
      return (HWND) get_wnd()->get_os_data();
   }


   bool interaction::subclass_window(void * posdata)
   {
      if(IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
      interaction * pimplOld = m_pimpl;
      ::ca::window * pimplNew = NULL;
      pimplNew = dynamic_cast < ::ca::window * > (System.alloc(typeid(::ca::window)));
      pimplNew->m_pguie = this;
      if(!pimplNew->SubclassWindow((HWND) posdata))
      {
         delete pimplNew;
         pimplNew = NULL;
      }
      if(pimplNew != NULL)
      {
         if(pimplOld != NULL)
         {
            pimplOld->m_pguie = NULL;
            pimplOld->_001ClearMessageHandling();
            ::ca::window * pwindowOld = dynamic_cast < ::ca::window * > (pimplOld);
            if(pwindowOld != NULL)
            {
               pwindowOld->_001InstallMessageHandling(pimplOld);
            }
            delete pimplOld;
         }
         pimplNew->m_pthread = System.GetThread();
         m_pthread = System.GetThread();
         m_pimpl = pimplNew;
         return true;
      }
      else
      {
         return false;
      }
   }
   
   void * interaction::unsubclass_window()
   {
      ::ca::window * pwindow = dynamic_cast < ::ca::window * > (m_pimpl);
      if(pwindow != NULL)
      {
         return pwindow->UnsubclassWindow();
      }
      return NULL;
   }


   bool interaction::create(interaction *pparent, id id)
   {
      if(IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
      m_pimpl = new virtual_user_interface(get_app());
      m_pimpl->m_pguie = this;
      m_pguie = this;
      if(!m_pimpl->create(pparent, id))
      {
         delete m_pimpl;
         m_pimpl = NULL;
         return false;
      }
      //_001InstallMessageHandling(this);
      return true;
   }

   BOOL interaction::create_window(
      const char * lpszClassName,
      const char * lpszWindowName, DWORD dwStyle,
      const RECT& rect,
      interaction* pParentWnd, id id,
      create_context* pContext)
   {
      if(IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
      interaction * pimplOld = m_pimpl;
      interaction * pimplNew = NULL;
      pimplNew = dynamic_cast < ::ca::window * > (System.alloc(typeid(::ca::window)));
      pimplNew->m_pguie = this;
      if(!pimplNew->create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, pContext))
      {
         delete pimplNew;
         pimplNew = NULL;
      }
      if(pimplNew != NULL)
      {
         if(pimplOld != NULL)
         {
            pimplOld->m_pguie = NULL;
            pimplOld->_001ClearMessageHandling();
            ::ca::window * pwindowOld = dynamic_cast < ::ca::window * > (pimplOld);
            if(pwindowOld != NULL)
            {
               pwindowOld->_001InstallMessageHandling(pimplOld);
            }
            delete pimplOld;
         }
         return true;
      }
      else
      {
         return false;
      }
   }



   BOOL interaction::create(const char * lpszClassName,
         const char * lpszWindowName, DWORD dwStyle,
         const RECT& rect,
         interaction* pParentWnd, id id,
         create_context* pContext)
   {
      //if(IsWindow())
      //{
        // DestroyWindow();
      //}
      m_signalptra.remove_all();
      interaction * pimplOld = m_pimpl;
      interaction * pimplNew = NULL;
      if(pParentWnd == NULL || pParentWnd->get_safe_handle() == HWND_MESSAGE)
      {
         pimplNew = dynamic_cast < ::ca::window * > (System.alloc(typeid(::ca::window)));
         pimplNew->m_pguie = this;
         m_pimpl = pimplNew;
         if(!pimplNew->create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, pContext))
         {
            m_pimpl = NULL;
            delete pimplNew;
            pimplNew = NULL;
         }
      }
      else
      {
         pimplNew = new virtual_user_interface(get_app());
         pimplNew->m_pguie = this;
         if(!pimplNew->create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, pContext))
         {
            delete pimplNew;
            pimplNew = NULL;
         }
      }
      if(pimplNew != NULL)
      {
         if(pimplOld != NULL)
         {
            pimplOld->m_pguie = NULL;
            pimplOld->_001ClearMessageHandling();
            ::ca::window * pwindowOld = dynamic_cast < ::ca::window * > (pimplOld);
            if(pwindowOld != NULL)
            {
               pwindowOld->_001InstallMessageHandling(pimplOld);
            }
            CSingleLock sl(&m_pthread->m_mutex, TRUE);
            pimplNew->m_uiptraChild = pimplOld->m_uiptraChild;
            pimplOld->m_uiptraChild.remove_all();
            sl.Unlock();
            if(pParentWnd != NULL)
            {
               on_set_parent(pParentWnd);
            }
            gen::del(pimplOld);
         }
         return true;
      }
      else
      {
         return false;
      }
   }


   BOOL interaction::create_window_ex(DWORD dwExStyle, const char * lpszClassName,
         const char * lpszWindowName, DWORD dwStyle,
         const RECT& rect,
         interaction* pParentWnd, id id,
         LPVOID lpParam)
   {
      if(IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
      m_pimpl = dynamic_cast < ::ca::window * > (System.alloc(typeid(::ca::window)));
      m_pimpl->m_pguie = this;
      if(!m_pimpl->CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, lpParam))
      {
         delete m_pimpl;
         m_pimpl = NULL;
         return false;
      }
      //_001InstallMessageHandling(this);
      return true;
   }
      

   BOOL interaction::CreateEx(DWORD dwExStyle, const char * lpszClassName,
         const char * lpszWindowName, DWORD dwStyle,
         const RECT& rect,
         interaction* pParentWnd, id id,
         LPVOID lpParam)
   {
      if(IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
      if(pParentWnd == NULL)
      {
         m_pimpl = dynamic_cast < ::ca::window * > (System.alloc(typeid(::ca::window)));
         m_pimpl->m_pguie = this;
         dwStyle &= ~WS_CHILD;
         if(!m_pimpl->CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, lpParam))
         {
            delete m_pimpl;
            m_pimpl = NULL;
            return false;
         }
         //_001InstallMessageHandling(this);
         return true;
      }
      else
      {
         m_pimpl = new virtual_user_interface(get_app());
         m_pimpl->m_pguie = this;
         if(!m_pimpl->CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, id, lpParam))
         {
            delete m_pimpl;
            m_pimpl = NULL;
            return false;
         }
         //_001InstallMessageHandling(this);
         return true;
      }

   }




   void interaction::BringWindowToTop()
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->BringWindowToTop();

   }

   BOOL interaction::IsWindow()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsWindow();
   }

   LONG interaction::GetWindowLong(int nIndex)
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetWindowLong(nIndex);
   }

   LONG interaction::SetWindowLong(int nIndex, LONG lValue)
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->SetWindowLong(nIndex, lValue);
   }


   BOOL interaction::RedrawWindow(LPCRECT lpRectUpdate,
         ::ca::rgn* prgnUpdate,
         UINT flags)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->RedrawWindow(lpRectUpdate, prgnUpdate, flags);
   }


   interaction * interaction::ChildWindowFromPoint(POINT point)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->ChildWindowFromPoint(point);
   }

   interaction * interaction::ChildWindowFromPoint(POINT point, UINT nFlags)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->ChildWindowFromPoint(point, nFlags);
   }

   interaction * interaction::GetNextWindow(UINT nFlag)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetNextWindow(nFlag);
   }

   interaction * interaction::GetTopWindow()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetTopWindow();
   }

   interaction * interaction::GetWindow(UINT nCmd)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetWindow(nCmd);
   }

   id interaction::SetDlgCtrlId(id id)
   {
      if(m_pimpl == NULL)
         return "";
      else
         return m_pimpl->SetDlgCtrlId(id);
   }

   interaction * interaction::GetActiveWindow()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetActiveWindow();
   }

   interaction * interaction::SetFocus()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->SetFocus();
   }


   interaction * interaction::SetActiveWindow()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->SetActiveWindow();
   }

   BOOL interaction::SetForegroundWindow()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->SetForegroundWindow();
   }

   interaction * interaction::GetLastActivePopup()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->GetLastActivePopup();
   }

   void interaction::SetWindowText(const char * lpszString)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->SetWindowText(lpszString);
   }

   int interaction::GetWindowText(__out_ecount_part_z(nMaxCount, return + 1) LPTSTR lpszStringBuf, __in int nMaxCount)
   {
      if(m_pimpl == NULL)
      {
         if(nMaxCount > 0)
            lpszStringBuf[0] = '\0';
         return 0;
      }
      else
         return m_pimpl->GetWindowText(lpszStringBuf, nMaxCount);
   }
   void interaction::GetWindowText(string & rString)
   {
      if(m_pimpl == NULL)
      {
         rString.Empty();
      }
      else
         m_pimpl->GetWindowText(rString);
   }

   int interaction::GetWindowTextLength()
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetWindowTextLength();
   }

   void interaction::SetFont(::ca::font* pFont, BOOL bRedraw)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->SetFont(pFont, bRedraw);
   }
   ::ca::font* interaction::GetFont()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetFont();
   }

   BOOL interaction::SendChildNotifyLastMsg(LRESULT* pResult)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->SendChildNotifyLastMsg(pResult);
   }

   interaction * interaction::EnsureTopLevelParent()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->EnsureTopLevelParent();
   }

   interaction * interaction::GetTopLevelParent()
   {
      ASSERT_VALID(this);

      interaction * hWndParent = this;
      interaction * hWndT;
      while ((hWndT = AfxGetParentOwner(hWndParent)) != NULL)
      {
         if(hWndT->get_wnd() == NULL)
            break;
         hWndParent = hWndT;
      }

      return hWndParent;
   }

   frame_window * interaction::EnsureParentFrame()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->EnsureParentFrame();
   }



   LRESULT interaction::Default()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->Default();
   }

   DWORD interaction::GetStyle()
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetStyle();
   }

   DWORD interaction::GetExStyle()
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetExStyle();
   }

   BOOL interaction::DestroyWindow()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->DestroyWindow();
   }



   // for custom cleanup after WM_NCDESTROY
   void interaction::PostNcDestroy()
   {
   }



   frame_window * interaction::GetParentFrame()
   {
      ASSERT_VALID(this);

      interaction * pParentWnd = GetParent();  // start with one parent up
      while (pParentWnd != NULL)
      {
         if (pParentWnd->IsFrameWnd())
         {
            return dynamic_cast < frame_window * > (pParentWnd);
         }
         pParentWnd = pParentWnd->GetParent();
      }
      return NULL;
   }


   void interaction::CalcWindowRect(LPRECT lprect, UINT nAdjustType)
   {
      if(m_pimpl == NULL)
         return;
      else
         return m_pimpl->CalcWindowRect(lprect, nAdjustType);
   }


   void interaction::RepositionBars(UINT nIDFirst, UINT nIDLast, UINT nIDLeftOver,
         UINT nFlag, LPRECT lpRectParam,
         LPCRECT lpRectClient, BOOL bStretch)
   {
      if(m_pimpl == NULL)
         return;
      else
         return m_pimpl->RepositionBars(nIDFirst, nIDLast, nIDLeftOver, nFlag, lpRectParam, lpRectClient, bStretch);
   }


   interaction * interaction::GetOwner()
   {
      if(m_pguieOwner != NULL)
      {
         return m_pguieOwner;
      }
      else
      {
         return GetParent();
      }
   }

   void interaction::SetOwner(interaction * pguie)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->SetOwner(pguie);
   }

   interaction * interaction::GetDlgItem(id iId)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetDlgItem(iId);
   }

   interaction * interaction::GetDescendantWindow(int iId)
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetDescendantWindow(iId);
   }

   void interaction::ScreenToClient(__rect64 * lprect)
   {
      if(m_pimpl != NULL)
         m_pimpl->ScreenToClient(lprect);
      else
         window_interface::ScreenToClient(lprect);

   }

   void interaction::ScreenToClient(__point64 * lppoint)
   {
      if(m_pimpl != NULL)
         m_pimpl->ScreenToClient(lppoint);
      else
         window_interface::ScreenToClient(lppoint);
   }

   void interaction::ClientToScreen(__rect64 * lprect)
   {
      if(m_pimpl == NULL)
         return window_interface::ClientToScreen(lprect);
      else
         return m_pimpl->ClientToScreen(lprect);
   }

   void interaction::ClientToScreen(__point64 * lppoint)
   {
      if(m_pimpl == NULL)
         return window_interface::ClientToScreen(lppoint);
      else
         return m_pimpl->ClientToScreen(lppoint);
   }

   void interaction::ScreenToClient(RECT * lprect)
   {
      if(m_pimpl != NULL)
         m_pimpl->ScreenToClient(lprect);
      else
         window_interface::ScreenToClient(lprect);
   }

   void interaction::ScreenToClient(POINT * lppoint)
   {
      if(m_pimpl != NULL)
         m_pimpl->ScreenToClient(lppoint);
      else
         window_interface::ScreenToClient(lppoint);
   }

   void interaction::ClientToScreen(RECT * lprect)
   {
      if(m_pimpl == NULL)
         return window_interface::ClientToScreen(lprect);
      else
         return m_pimpl->ClientToScreen(lprect);
   }

   void interaction::ClientToScreen(POINT * lppoint)
   {
      if(m_pimpl == NULL)
         return window_interface::ClientToScreen(lppoint);
      else
         return m_pimpl->ClientToScreen(lppoint);
   }

   int interaction::SetWindowRgn(HRGN hRgn, BOOL bRedraw)
   {
     if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->SetWindowRgn(hRgn, bRedraw);
   }

   int interaction::GetWindowRgn(HRGN hRgn)
   {
     if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetWindowRgn(hRgn);
   }


   bool interaction::IsZoomed()
   {
      if(m_pimpl == NULL)
         return false;
      else
         return m_pimpl->IsZoomed();
   }

   bool interaction::IsFullScreen()
   {
      if(m_pimpl == NULL)
         return false;
      else
         return m_pimpl->IsZoomed();
   }

   bool interaction::ShowWindowFullScreen(bool bShowWindowFullScreen)
   {
      if(m_pimpl == NULL)
         return false;
      else
         return m_pimpl->ShowWindowFullScreen(bShowWindowFullScreen);
   }

   bool interaction::IsIconic()
   {
      if(m_pimpl == NULL)
         return false;
      else
         return m_pimpl->IsIconic();
   }

   void interaction::MoveWindow(int x, int y, int nWidth, int nHeight,
               BOOL bRepaint)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->MoveWindow(x, y, nWidth, nHeight, bRepaint);
   }

   void interaction::MoveWindow(LPCRECT lpRect, BOOL bRepaint)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->MoveWindow(lpRect, bRepaint);
   }



   BOOL interaction::CheckAutoCenter()
   {
      if(m_pimpl == NULL)
         return TRUE;
      else
         return m_pimpl->CheckAutoCenter();
   }

   void interaction::CenterWindow(interaction * pAlternateOwner)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->CenterWindow(pAlternateOwner);
   }

   LRESULT interaction::DefWindowProc(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->DefWindowProc(uiMessage, wparam, lparam);
   }

   void interaction::message_handler(gen::signal_object * pobj)
   {
      if(m_pimpl == NULL || m_pimpl == this)
         return;
      else
         return m_pimpl->message_handler(pobj);
   }

   BOOL interaction::GetWindowPlacement(WINDOWPLACEMENT* lpwndpl)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->GetWindowPlacement(lpwndpl);
   }

   BOOL interaction::SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->SetWindowPlacement(lpwndpl);
   }

   BOOL interaction::PreCreateWindow(CREATESTRUCT& cs)
   {
      if(m_pimpl == NULL)
         return TRUE;
      else
         return m_pimpl->PreCreateWindow(cs);
   }

   BOOL interaction::IsTopParentActive()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->IsTopParentActive();
   }

   void interaction::ActivateTopParent()
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->ActivateTopParent();
   }

   void interaction::UpdateDialogControls(command_target* pTarget, BOOL bDisableIfNoHandler)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->UpdateDialogControls(pTarget, bDisableIfNoHandler);
   }

   void interaction::UpdateWindow()
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->UpdateWindow();
   }

   void interaction::SetRedraw(BOOL bRedraw)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->SetRedraw(bRedraw);
   }

   BOOL interaction::GetUpdateRect(LPRECT lpRect, BOOL bErase)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->GetUpdateRect(lpRect, bErase);
   }

   int interaction::GetUpdateRgn(::ca::rgn* pRgn, BOOL bErase)
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->GetUpdateRgn(pRgn, bErase);

   }

   void interaction::Invalidate(BOOL bErase)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->Invalidate(bErase);
   }

   void interaction::InvalidateRect(LPCRECT lpRect, BOOL bErase)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->InvalidateRect(lpRect, bErase);
   }

   void interaction::InvalidateRgn(::ca::rgn* pRgn, BOOL bErase)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->InvalidateRgn(pRgn, bErase);
   }

   void interaction::ValidateRect(LPCRECT lpRect)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->ValidateRect(lpRect);
   }
   void interaction::ValidateRgn(::ca::rgn* pRgn)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->ValidateRgn(pRgn);
   }


   void interaction::layout()
   {
   }

   void interaction::ShowOwnedPopups(BOOL bShow)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->ShowOwnedPopups(bShow);
   }

   BOOL interaction::Attach(HWND hWndNew)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->Attach(hWndNew);
   }
   HWND interaction::Detach()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->Detach();
   }


   void interaction::pre_subclass_window()
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->pre_subclass_window();
   }

   WNDPROC* interaction::GetSuperWndProcAddr()
   {
      if(m_pimpl == NULL)
         return NULL;
      else
         return m_pimpl->GetSuperWndProcAddr();
   }

   int interaction::RunModalLoop(DWORD dwFlags)
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->RunModalLoop(dwFlags);
   }
   BOOL interaction::ContinueModal()
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->ContinueModal();
   }
   void interaction::EndModalLoop(int nResult)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->EndModalLoop(nResult);
   }
   void interaction::EndAllModalLoops(int nResult)
   {
      if(m_pimpl == NULL)
         return;
      else
         m_pimpl->EndAllModalLoops(nResult);
   }

   bool interaction::BaseOnControlEvent(control_event * pevent)
   {
      if(GetParent() != NULL)
      {
         return GetParent()->BaseOnControlEvent(pevent);
      }
      else
      {
         return false;
      }
   }

   BOOL interaction::PostMessage(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {
      return m_pthread->post_message(this, uiMessage, wparam, lparam);
   }

   // Timer Functions
   UINT_PTR interaction::SetTimer(UINT_PTR nIDEvent, UINT nElapse,
         void (CALLBACK* lpfnTimer)(HWND, UINT, UINT_PTR, DWORD))
   {
      if(m_pimpl == NULL)
         return 0;
      else
         return m_pimpl->SetTimer(nIDEvent, nElapse, lpfnTimer);
   }

   BOOL interaction::KillTimer(UINT_PTR nIDEvent)
   {
      if(m_pimpl == NULL)
         return FALSE;
      else
         return m_pimpl->KillTimer(nIDEvent);
   }


   bool interaction::has_focus()
   {
      return System.get_focus_guie() == this;
   }

   interaction * interaction::set_capture(interaction * pinterface)
   {
      if(pinterface == NULL)
         pinterface = this;
      return GetTopLevelParent()->get_wnd()->set_capture(pinterface);
   }


   interaction * interaction::release_capture()
   {
      return get_wnd()->release_capture();
   }

   void interaction::track_mouse_leave()
   {
      ASSERT(GetTopLevelParent() != NULL);
      if(GetTopLevelParent() == NULL)
         return;
      ASSERT(GetTopLevelParent()->get_wnd() != NULL);
      if(GetTopLevelParent()->get_wnd() == NULL)
         return;
      GetTopLevelParent()->get_wnd()->mouse_hover_remove(this);
   }

   void interaction::track_mouse_hover()
   {
      ASSERT(GetTopLevelParent() != NULL);
      if(GetTopLevelParent() == NULL)
         return;
      ASSERT(GetTopLevelParent()->get_wnd() != NULL);
      if(GetTopLevelParent()->get_wnd() == NULL)
         return;
      GetTopLevelParent()->get_wnd()->mouse_hover_add(this);
   }


   void interaction::_001WindowMaximize()
   {
      m_eappearance = appearance_zoomed;
      rect rectDesktop;
      ::ca::window * pwndDesktop = System.get_desktop_window();
      pwndDesktop->GetWindowRect(rectDesktop);
      SetWindowPos(ZORDER_TOP, 0, 0, rectDesktop.width(),
         rectDesktop.height(), SWP_SHOWWINDOW);
      
   }

   void interaction::_001WindowRestore()
   {
      m_eappearance = appearance_normal;
      if(m_pimpl != NULL)
         m_pimpl->_001WindowRestore();
   }


   void interaction::GuieProc(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void interaction::_001DeferPaintLayeredWindowBackground(::ca::graphics * pdc)
   {
      if(m_pimpl != NULL)
      {
         m_pimpl->_001DeferPaintLayeredWindowBackground(pdc);
      }
   }

   void interaction::_001OnDeferPaintLayeredWindowBackground(::ca::graphics * pdc)
   {
      _001DeferPaintLayeredWindowBackground(pdc);
   }

   bool interaction::set_placement(LPRECT lprect)
   {
      rect rectWindow(*lprect);
      return SetWindowPos(
         NULL, 
         rectWindow.left,
         rectWindow.top,
         rectWindow.width(),
         rectWindow.height(),
         SWP_NOZORDER);
   }

   void interaction::OnLinkClick(const char * psz, const char * pszTarget)
   {
      System.open_link(psz, pszTarget);
   }

   void interaction::on_set_parent(interaction * pguieParent)
   {
      if(pguieParent != NULL)
      {
         pguieParent->m_uiptraChild.add(m_pguie);
      }
   }

   bool interaction::create_message_window(const char * pszName, ::ca::window_callback * pcallback)
   {
      UNREFERENCED_PARAMETER(pcallback);
      if(IsWindow())
      {
         DestroyWindow();
      }
      m_signalptra.remove_all();
      return create(NULL, pszName, 0, rect(0, 0, 0, 0), System.window_from_os_data(HWND_MESSAGE), NULL) != FALSE;
   }

   void interaction::WalkPreTranslateTree(gen::signal_object * pobj)
   {
      ::ca::window * pwnd = dynamic_cast < ::ca::window * > (m_pimpl);
      if(pwnd == NULL)
      {
         pwnd = dynamic_cast < ::ca::window * > (this);
      }
      if(pwnd != NULL && pwnd->IsWindow())
      {
         return pwnd->WalkPreTranslateTree(pobj);
      }
   }

   void interaction::on_select()
   {
   }

   ::visual::e_cursor interaction::get_cursor()
   {
      return m_ecursor;
   }

   void interaction::set_cursor(::visual::e_cursor ecursor)
   {
      m_ecursor = ecursor;
   }

   void interaction::_001OnMouseMove(::gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj);
      pmouse->m_ecursor = get_cursor();
   }


   void interaction::timer_item::check()
   {
      if(::GetTickCount() >= (m_uiLastSent + m_uiElapse))
      {
         try
         {
            m_pguie->SendMessage(WM_TIMER, m_uiId);
         }
         catch(...)
         {
         }
         m_uiLastSent = ::GetTickCount();
      }
   }

   UINT interaction::timer_array::set(interaction * pguie, UINT uiId, UINT uiElapse)
   {
      
      
      CSingleLock sl(&m_mutex, TRUE);


      if(pguie == NULL)
         return 0xffffffff;
      add(pguie);
      index i = find(pguie, uiId);
      if(i >= 0)
      {
         m_timera[i].m_uiElapse = uiElapse;
         m_timera[i].m_uiLastSent = ::GetTickCount();
         return (UINT) i;
      }
      else
      {
         timer_item item;
         
         item.m_pguie = pguie;
         item.m_uiId = uiId;
         item.m_uiElapse = uiElapse;
         item.m_uiLastSent = ::GetTickCount();

         return (UINT) m_timera.add(item);
      }
   }

   void interaction::timer_array::check()
   {


      CSingleLock sl(&m_mutex, TRUE);


      for(int i = 0; i < m_timera.get_count(); i++)
      {
         try
         {
            m_timera[i].check();
         }
         catch(...)
         {
         }
      }
   }

   void interaction::timer_array::on_delete(interaction * pui)
   {
      unset(pui);
   }

   bool interaction::timer_array::unset(interaction * pguie, UINT uiId)
   {


      CSingleLock sl(&m_mutex, TRUE);


      index i = find(pguie, uiId);
      if(i >= 0)
      {
         m_timera.remove_at(i);
         if(find_from(pguie, 0) < 0)
         {
            remove(pguie);
         }
         return true;
      }
      return false;
   }

   void interaction::timer_array::unset(interaction * pguie)
   {


      CSingleLock sl(&m_mutex, TRUE);


      index i = 0;
      while((i = find_from(pguie, i)) >= 0)
      {
         m_timera.remove_at(i);
      }
      if(find_from(pguie, 0) < 0)
      {
         remove(pguie);
      }
   }

   int interaction::timer_array::find(interaction * pguie, UINT uiId)
   {


      CSingleLock sl(&m_mutex, TRUE);


      for(index i = 0; i < m_timera.get_count(); i++)
      {
         if(m_timera[i].m_pguie == pguie && m_timera[i].m_uiId == uiId)
         {
            return i;
         }
      }
      return -1;
   }

   int interaction::timer_array::find_from(interaction * pguie, int iStart)
   {


      CSingleLock sl(&m_mutex, TRUE);


      for(int i = iStart; i < m_timera.get_count(); i++)
      {
         if(m_timera[i].m_pguie == pguie)
         {
            return i;
         }
      }
      return -1;
   }

   void interaction::timer_array::dump(dump_context & dc) const
   {
      UNREFERENCED_PARAMETER(dc);
   }

   void interaction::timer_array::assert_valid() const
   {
   }


   bool interaction::can_merge(::user::interaction * pui)
   {
      return false;
   }

   bool interaction::merge(::user::interaction * pui)
   {
      return false;
   }

   interaction * interaction::get_bottom_child()
   {
      CSingleLock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      if(m_uiptraChild.get_count() <= 0)
         return NULL;
      else
         return m_uiptraChild.last_element();
   }

   interaction * interaction::get_top_child()
   {
      CSingleLock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      if(m_uiptraChild.get_count() <= 0)
         return NULL;
      else
         return m_uiptraChild.first_element();
   }

   interaction * interaction::under_sibling()
   {
      CSingleLock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      interaction * pui = NULL;
      try
      {
         pui = GetParent();
      }
      catch(...)
      {
         return NULL;
      }
      if(pui == NULL)
         return NULL;
      index i = pui->m_uiptraChild.find(this);
      if(i < 0)
         return NULL;
      i++;
      if(i >= pui->m_uiptraChild.get_count())
         return NULL;
      else
         return pui->m_uiptraChild[i];
   }

   interaction * interaction::above_sibling()
   {
      CSingleLock sl(m_pthread == NULL ? NULL : &m_pthread->m_mutex, TRUE);
      interaction * pui = NULL;
      try
      {
         pui = GetParent();
      }
      catch(...)
      {
         return NULL;
      }
      if(pui == NULL)
         return NULL;
      int i = pui->m_uiptraChild.find(this);
      if(i < 0)
         return NULL;
      i--;
      if(i < 0)
         return NULL;
      else
         return pui->m_uiptraChild[i];
   }

   void interaction::_001OnUser184(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::base, pbase, pobj);
      if(pbase->m_wparam == 0 &&
         pbase->m_lparam == 0)
      {
         class rect rect;
         System.get_monitor_rect(0, &rect);
         rect.deflate(rect.width() / 4, rect.height() / 4);
         SetWindowPos(ZORDER_TOP, rect.left, rect.top, rect.width(), rect.height(), 0);
         pbase->m_bRet = true;
      }
   }

   ::user::interaction * interaction::get_os_focus_uie()
   {
      return NULL;
   }


   ::ca::window * interaction::get_wnd()
   {
      if(m_pimpl != NULL)
      {
         ::ca::window * pwnd = dynamic_cast < ::ca::window * > (m_pimpl);
         if(pwnd != NULL)
            return pwnd;
      }
      if(GetParent() == NULL)
         return NULL;
      return GetParent()->get_wnd();
   }


} // namespace user

CLASS_DECL_ca ::user::interaction * WINAPI CreateGuieEx(
   ::ca::application * papp,
    __in DWORD dwExStyle,
    __in_opt const char * lpClassName,
    __in_opt const char * lpWindowName,
    __in DWORD dwStyle,
    __in int X,
    __in int Y,
    __in int nWidth,
    __in int nHeight,
    ::user::interaction * pguieParent,
    id id,
    __in_opt HINSTANCE hInstance,
    __in_opt LPVOID lpParam)
{
   UNREFERENCED_PARAMETER(dwExStyle);
   UNREFERENCED_PARAMETER(lpClassName);
   UNREFERENCED_PARAMETER(lpWindowName);
   UNREFERENCED_PARAMETER(dwStyle);
   UNREFERENCED_PARAMETER(X);
   UNREFERENCED_PARAMETER(Y);
   UNREFERENCED_PARAMETER(nWidth);
   UNREFERENCED_PARAMETER(nHeight);
   UNREFERENCED_PARAMETER(hInstance);
   UNREFERENCED_PARAMETER(lpParam);
   ::user::interaction * pguie = new ::user::interaction(papp);
   if(pguie->create(pguieParent, id))
   {
      return pguie;
   }
   delete pguie;
   return NULL;
}



