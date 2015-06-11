#include "framework.h"
//#include "base/user/user.h"
//#include "metrowin.h"

class keep_event_reset
{
public:


   event * m_pevent;


   keep_event_reset(event * pevent)
   {
      m_pevent = pevent;
      pevent->ResetEvent();
   }
   ~keep_event_reset()
   {
      m_pevent->SetEvent();
   }


};

namespace metrowin
{

   window_draw::window_draw(::aura::application * papp) :
      ::object(papp),
      ::thread(papp),
      ::user::window_draw(papp),
      //message_queue(papp),
      m_mutexRender(papp),
      m_mutexRendering(papp),
      m_mutexRgnUpdate(papp),
      m_semaphoreBuffer(papp)//,
      //m_wndpaOut(papp)
   {
   }

   extern void _001DeferPaintLayeredWindowBackground(oswindow hwnd, ::draw2d::graphics * pdc);
   window_draw::~window_draw()
   {
   }


   void window_draw::message_queue_message_handler(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      if(pbase->m_uiMessage == (WM_USER + 1984 + 1977))
      {
         _synch_redraw();
      }
   }

   void window_draw::asynch_redraw()
   {
      DWORD dwTick = ::get_tick_count();
      if(m_iFramesPerSecond == 0)
      {
         if(dwTick - m_dwLastUpdate < 1000)
            return;
      }
      else
      {
         if(dwTick - m_dwLastUpdate < 1000 / m_iFramesPerSecond)
            return;
      }
      _asynch_redraw();
   }

   void window_draw::_asynch_redraw()
   {
      if(!m_bProDevianMode)
      {
         m_pthreadimpl->m_spqueue->message_queue_post_message(WM_USER + 1984 + 1977);
      }
   }

   void window_draw::synch_redraw()
   {
      throw todo(get_app());
   }

   void window_draw::_synch_redraw()
   {


      keep_event_reset keepeventreset(&m_eventFree);

      static DWORD s_dwLastAnalysisFrame = 0;
      static DWORD s_dwLastFrameFrame = 0;
      static DWORD s_iAnalysisFrameFailureCount = 0;
      static DWORD s_iFrameFailureCount = 0;
      DWORD iFailureTime;
      if(m_iFramesPerSecond == 0)
      {
         iFailureTime = 1000 / 12;
      }
      else
      {
         iFailureTime = 1000 / m_iFramesPerSecond;
      }
      m_dwLastUpdate = ::get_tick_count();
      UpdateBuffer();
      return;
      //if(m_pbuffer->GetBuffer()->get_os_data() != NULL)
      //{
      //   //m_pbuffer->m_spdib->fill_channel(255, visual::rgba::channel_alpha);
      //   //ScreenOutput();
      //}
      DWORD dwTakeTime = ::get_tick_count() - m_dwLastUpdate;
      m_dwLastDelay = dwTakeTime;
      if(dwTakeTime > iFailureTime)
      {
         s_dwLastAnalysisFrame += dwTakeTime;
         s_dwLastFrameFrame += dwTakeTime;
         TRACE("window_draw::_synch_redraw :: System has exceeded prodevian performance failure time - %d milliseconds", iFailureTime);
         TRACE("window_draw::_synch_redraw :: took - %d milliseconds", dwTakeTime);
         s_iAnalysisFrameFailureCount++;
         DWORD iTimeFrame = 2000;
         DWORD iMaxFailureCount = 3;
         if(s_dwLastAnalysisFrame > iTimeFrame ||
            dwTakeTime > (iFailureTime * iMaxFailureCount))
         {
            s_dwLastAnalysisFrame = 0;
            if(s_iAnalysisFrameFailureCount > iMaxFailureCount
            || (dwTakeTime > (iFailureTime * iMaxFailureCount)))
            {
               s_iFrameFailureCount++;
            }
            s_iAnalysisFrameFailureCount = 0;
         }
         DWORD iMaxFrameFailureCount = 3;
         DWORD iFrameTimeFrame = iTimeFrame * iMaxFrameFailureCount;
         if(s_dwLastFrameFrame > iFrameTimeFrame)
         {
            s_dwLastFrameFrame = 0;
            if(s_iFrameFailureCount > iMaxFailureCount)
            {
               TRACE("window_draw::_synch_redraw :: during prodevian Performance Analysis Time Frame - %d milliseconds -,", iTimeFrame);
               TRACE("window_draw::_synch_redraw :: failure count has exceeded the maximum count - %d", iMaxFailureCount);
               TRACE("window_draw::_synch_redraw :: Going to try to save some resource that may favor drawing perfomance");
               if(!Session.savings().is_trying_to_save(::aura::resource_blur_background))
               {
                  TRACE("window_draw::_synch_redraw :: System is not trying to save \"blur background\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to try to save \"blur background\" resource");
                  Session.savings().try_to_save(::aura::resource_blur_background);
               }
               else if(!Session.savings().is_trying_to_save(::aura::resource_blurred_text_embossing))
               {
                  TRACE("window_draw::_synch_redraw :: System is not trying to save \"blurred text embossing\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to try to save \"blurred text embossing\" resource");
                  Session.savings().try_to_save(::aura::resource_blurred_text_embossing);
               }
               else if(!Session.savings().is_warning(::aura::resource_processing))
               {
                  TRACE("window_draw::_synch_redraw :: System is not warning to save \"processing\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to warn to save \"processing\" resource");
                  Session.savings().warn(::aura::resource_processing);
               }
               else if(!Session.savings().is_trying_to_save(::aura::resource_processing))
               {
                  TRACE("window_draw::_synch_redraw :: System is not trying to save \"processing\" resource");
                  TRACE("window_draw::_synch_redraw :: Going to try to save \"processing\" resource");
                  Session.savings().try_to_save(::aura::resource_blur_background);
               }
            }
            s_iFrameFailureCount = 0;
         }

      }
   }

//   bool window_draw::to(
//      ::draw2d::graphics *          pdc,
//      LPCRECT        lpcrectUpdate,
//      user::oswindow_tree::Array & hwndtreea,
//      bool           bGdiLocked,
//      bool           bExcludeParamWnd)
//   {
//      UNREFERENCED_PARAMETER(bGdiLocked);
//      UNREFERENCED_PARAMETER(bExcludeParamWnd);
//      single_lock sl(&m_mutexRender, TRUE);
//      rect rectUpdate(*lpcrectUpdate);
//
//      rect rectChild;
//
//      rect rectNewUpdate;
//
//      throw todo(get_app());
//       return true;
//   }
//
//   bool window_draw::to(
//      ::draw2d::graphics *          pdc,
//      LPCRECT        lpcrectUpdate,
//      user::oswindow_tree & hwndtree,
//      bool           bGdiLocked,
//      bool           bExcludeParamWnd)
//   {
//      UNREFERENCED_PARAMETER(bGdiLocked);
//      single_lock sl(&m_mutexRender, TRUE);
//      rect rectUpdate(*lpcrectUpdate);
//
////      DWORD dwTimeIn = get_tick_count();
//
//      oswindow hwndParam = hwndtree.m_oswindow;
//
//      if(hwndParam == NULL)
//      {
//         return false;
//      }
//
//      return to(
//         pdc,
//         rectUpdate,
//         hwndtree.m_oswindowtreea,
//         true,
//         false);
//
//   }


   UINT window_draw::RedrawProc()
   {
      m_bRun = true;
      while(m_bRun)
      {
         try
         {
            if(m_bProDevianMode)
            {
               _synch_redraw();
            }
         }
         catch(...)
         {
         }
  /*       while(::PeekMessageA(&msg, NULL, NULL, NULL, PM_NOREMOVE))
         {
            __get_thread()->pump_message();
         }*/
         int iUiDataWriteWindowTimeForTheApplicationInThisMachine = 8;
         if(m_iFramesPerSecond == 0)
         {
            Sleep(1000);
         }
         else if((1000 / m_iFramesPerSecond) > m_dwLastDelay)
         {
            Sleep(MAX((DWORD) MAX(0, iUiDataWriteWindowTimeForTheApplicationInThisMachine), (1000 / m_iFramesPerSecond) - m_dwLastDelay));
         }
         else
         {
            Sleep(iUiDataWriteWindowTimeForTheApplicationInThisMachine);
         }
      }
      //delete this;
      return 0;
   }

   int32_t window_draw::run()
   {

      m_dwLastRedrawRequest = ::get_tick_count();
      m_bRender = false;
      m_dwLastUpdate = false;

      return RedrawProc();
   }


   bool window_draw::UpdateBuffer()
   {
      synch_lock ml(&user_mutex());
      if(m_bRender)
         return false;
      single_lock sl(&m_mutexRender, FALSE);
      if(!sl.lock(duration::zero()))
         return false;
      keep<bool> keepRender(&m_bRender, true, false, true);
      static bool bTest = false;
   //   semaphore * psemaphore = TwfGetBufferSemaphore();
   //   single_lock slSemaphoreBuffer(psemaphore, FALSE);
   //   if(!slSemaphoreBuffer.lock(duration::zero()))
   //   {
   ////xxx      AddUpdateRect(rectClip, true);
   ////      return false;
   //   }







      user::interaction_ptra wndpa;

      wndpa = System.m_uiptraFrame;

      user::oswindow_tree::Array hwndtreea;

      m_xapp->m_directx->Render(wndpa);

      ml.unlock();

      m_xapp->m_directx->Present();

      return true;


   }

   //bool window_draw::ScreenOutput()
   //{
   //
   //   if(m_bRender)
   //      return false;
   //
   //   single_lock sl(&m_mutexRender, FALSE);
   //
   //   if(!sl.lock(duration::zero()))
   //      return false;
   //
   //   keep<bool> keepRender(&m_bRender, true, false, true);
   //
   //   static bool bTest = false;

   //   for(int i = 0; i < m_wndpaOut.get_count(); i++)
   //   {
   //      sp(::user::interaction) pwnd = m_wndpaOut[i];

   //   //   ScreenOutput(m_pbuffer, pwnd);
   //
   //   }

   //   return true;

   //}


   //semaphore * window_draw::TwfGetBufferSemaphore()
   //{
   //   return &m_semaphoreBuffer;
   //}

   // The first ::user::interaction_impl handle in the array must belong
   // to the higher z order ::user::interaction_impl.
   // The rectangle must contain all update region.
   // It must be in screen coordinates.



   // Remark: this optimization eliminates top level windows
   // that are lower z order siblings of a higher z order
   // top level ::user::interaction_impl that contains all
   // the update region in a opaque area.
   // It doesn�t eliminates from the update parent windows
   // obscured by opaque children.

//   window_draw::EOptimize window_draw::TwfOptimizeRender(
//      user::oswindow_tree::Array & hwndtreea,
//      LPCRECT lpcrect)
//   {
//      const rect rectUpdate(*lpcrect);
//
//      rect rectClient;
//      for(int i = 0; i < hwndtreea.get_size();)
//      {
//         user::oswindow_tree & hwndtree = hwndtreea[i];
//         switch(TwfOptimizeRender(
//            hwndtree,
//            lpcrect))
//         {
//         case OptimizeNone:
//            i++;
//            break;
//         case OptimizeThis:
//            hwndtreea.remove_at(i);
//            break;
//         case OptimizeAllNext:
//            {
//               while(hwndtreea.get_size() > i + 1)
//               {
//                  hwndtreea.remove_at(i + 1);
//               }
//               /*hwndtreea.remove_at(i + 1);
//               oswindow hwnd = hwndtreea[i].m_hwnd;
//               rect rect;
//               ::GetClientRect(hwnd, rect);
//               ::ClientToScreen(hwnd, &rect.top_left());
//               ::ClientToScreen(hwnd, &rect.bottom_right());
//               rect.union(rect, lpcrect);
//               TwfOptimizeRenderRemoveNextProper(
//                  hwndtreea,
//                  i + 1,
//                  rect);*/
//            }
//            return OptimizeAllNext;
//         }
//      }
//      return OptimizeNone;
//
//   }
//
//   window_draw::EOptimize window_draw::TwfOptimizeRenderRemoveNextProper(
//      user::oswindow_tree::Array & hwndtreea,
//      int iIndex,
//      LPCRECT lpcrect)
//   {
//
//      return OptimizeNone;
//
//   }
//
//
//   window_draw::EOptimize window_draw::TwfOptimizeRender(user::oswindow_tree & hwndtree, LPCRECT lpcrect)
//   {
//
//      hwndtree.m_dwUser = 0;
//
//      oswindow hwnd = hwndtree.m_oswindow;
//
//      ::user::interaction_base * ptwi = System.user()->window_map().get((int_ptr) (void *) hwnd);
//
//#ifdef WINDOWSEX
//      if(!::IsWindowVisible(hwnd))
//      {
//         return OptimizeThis;
//      }
//#else
//      throw todo(get_app());
//#endif
//
//      const rect rectUpdate(*lpcrect);
//
//      rect rectClient;
//
//      ::user::interaction * pguie = dynamic_cast < ::user::interaction * > (ptwi);
//
//      pguie->GetClientRect(rectClient);
//      pguie->ClientToScreen(rectClient);
//
//
//
//
//      rect rectIntersect;
//
//      if(!rectIntersect.intersect(rectClient, rectUpdate))
//      {
//         return OptimizeThis;
//      }
//
//      if(!rectClient.contains(rectUpdate))
//      {
//
//         return OptimizeNone;
//      }
//
//   //    ::user::interaction_impl * pwnd = window::FromHandlePermanent(hwnd);
//
//
//      if(ptwi == NULL)
//      {
//
//   //      ::user::interaction_base::GetProperty getp;
//   //      getp.m_eproperty = CTransparentWndInterface::PropertyInterface;
//   //      ::SendMessage(hwnd, CTransparentWndInterface::MessageGetProperty, 0, (LPARAM) &getp);
//   //      ptwi = getp.m_pinterface;
//   //      if(ptwi != NULL)
//   //      {
//   //         pwnd = ptwi->TwiGetWnd();
//   //      }
//      }
//
//      EOptimize eoptimize = OptimizeNone;
//      if(ptwi != NULL)
//      {
//         if(!ptwi->_001HasTranslucency())
//            eoptimize = OptimizeAllNext;
//      }
//
//      EOptimize eoptimizeChildren = TwfOptimizeRender(
//            hwndtree.m_oswindowtreea,
//            lpcrect);
//
//      if(eoptimizeChildren == OptimizeAllNext)
//      {
//         hwndtree.m_dwUser |= 1; // exclude from drawing;
//         return OptimizeAllNext;
//      }
//      else if(eoptimize == OptimizeAllNext)
//      {
//         return OptimizeAllNext;
//      }
//      else
//      {
//         return OptimizeNone;
//      }
//
//
//   }
//
//
//   bool window_draw::TwfGetTopWindow(
//      oswindow hwnd,
//      user::oswindow_array & hwnda,
//      array < HRGN, HRGN > & hrgna,
//      user::oswindow_tree::Array & hwndtreea,
//      HRGN hrgn)
//   {
//      rect rectClient;
//      for(int i = 0; i < hwndtreea.get_size(); i++)
//      {
//         user::oswindow_tree & hwndtree = hwndtreea[i];
//         if(!TwfGetTopWindow(
//            hwnd,
//            hwnda,
//            hrgna,
//            hwndtree,
//            hrgn))
//            return false;
//
//      }
//      return true;
//
//   }
//
//   bool window_draw::TwfGetTopWindow(
//      oswindow hwndParam,
//      user::oswindow_array & hwnda,
//      array < HRGN, HRGN > & hrgna,
//      user::oswindow_tree & hwndtree,
//      HRGN hrgn)
//   {
//      oswindow hwnd = hwndtree.m_oswindow;
//#ifdef WINDOWSEX
//
//      if(!::IsWindowVisible(hwnd))
//      {
//         return true;
//      }
//
//
//
//      rect rectWindow;
//
//      ::GetWindowRect(hwnd, rectWindow);
//
//
//   //   ::user::interaction_impl * pwnd = ::metrowin::window::from_handle(hwnd);
//
//      if(!TwfGetTopWindow(
//            hwndParam,
//            hwnda,
//            hrgna,
//            hwndtree.m_oswindowtreea,
//            hrgn))
//      {
//         return false;
//      }
//
//      HRGN hrgnIntersect;
//
//      hrgnIntersect = ::CreateRectRgnIndirect(rectWindow);
//
//      int iCombine = ::CombineRgn(hrgnIntersect, hrgn, hrgnIntersect, RGN_AND);
//
//      if(iCombine == NULLREGION)
//      {
//         ::DeleteObject(hrgnIntersect);
//         return true;
//      }
//
//      ::user::interaction_base * pwndi = System.window_map().get((int_ptr)(void *) hwnd);
//
//      if(pwndi == NULL)
//      {
//         ::SendMessage(
//            hwnd,
//            ::user::interaction_base::MessageBaseWndGetProperty,
//            ::user::interaction_base::PropertyDrawBaseWndInterface,
//            (LPARAM) &pwndi);
//      }
//
//      if(hwndParam == hwnd ||
//         (pwndi != NULL &&
//            pwndi->_001HasTranslucency()))
//      {
//
//
//         iCombine = ::CombineRgn(hrgn, hrgn, hrgnIntersect, RGN_DIFF);
//
//         point ptOffset(0, 0);
//
//         ::ScreenToClient(hwnd, &ptOffset);
//
//         hwnda.add(hwnd);
//         ::OffsetRgn(hrgnIntersect, ptOffset.x, ptOffset.y);
//         hrgna.add(hrgnIntersect);
//
//         if(iCombine == NULLREGION)
//         {
//            return false;
//         }
//
//      }
//      else
//      {
//         ::DeleteObject(hrgnIntersect);
//         TwfGetTopWindowOptimizeOpaque(
//            hwnd,
//            hwnda,
//            hrgna);
//
//      }
//      if(hwndParam == hwnd)
//      {
//         return false;
//      }
//      else
//      {
//         return true;
//      }
//
//#else
//
//      throw todo(get_app());
//
//#endif
//
//   }
//
//   // lpcrect must be in screen coordinates
//   void window_draw::TwfGetTopWindow(
//      oswindow hwnd,
//      user::oswindow_array & hwnda,
//      array < HRGN, HRGN > & hrgna,
//      user::oswindow_tree::Array & hwndtreea,
//      LPCRECT lpcrect)
//   {
//#ifdef WINDOWSEX
//      HRGN hrgn = ::CreateRectRgnIndirect(lpcrect);
//      TwfGetTopWindow(
//         hwnd,
//         hwnda,
//         hrgna,
//         hwndtreea,
//         hrgn);
//      ::DeleteObject(hrgn);
//#else
//      throw todo(get_app());
//#endif
//   }
//
//   void window_draw::TwfGetTopWindowOptimizeOpaque(
//      oswindow hwndOpaque,
//      user::oswindow_array & hwnda,
//      array < HRGN, HRGN > & hrgna)
//   {
//#ifdef WINDOWSEX
//      rect rectWindow;
//
//   //   ::user::interaction_impl * pwndOpaque = window::FromHandlePermanent(hwndOpaque);
//
//      ::GetWindowRect(hwndOpaque, rectWindow);
//
//      HRGN hrgnOpaque = ::CreateRectRgnIndirect(rectWindow);
//
//      point ptOffset;
//      for(int i = 0; i < hrgna.get_size(); )
//      {
//         oswindow hwnd = hwnda[i];
//         HRGN hrgn = hrgna[i];
//         ptOffset.x = 0;
//         ptOffset.y = 0;
//         ::ClientToScreen(hwnd, &ptOffset);
//         ::OffsetRgn(hrgn, ptOffset.x, ptOffset.y);
//         if(::CombineRgn(hrgn, hrgn, hrgnOpaque, RGN_DIFF) == NULLREGION)
//         {
//            ::DeleteObject(hrgn);
//            hrgna.remove_at(i);
//            hwnda.remove_at(i);
//         }
//         else
//         {
//            ::OffsetRgn(hrgn, -ptOffset.x, -ptOffset.y);
//            i++;
//         }
//      }
//
//      ::DeleteObject(hrgnOpaque);
//#else
//      throw todo(get_app());
//#endif
//   }
//
//
//   void window_draw::get_wnda(user::interaction_ptra & wndpa)
//   {
//      wndpa = System.frames();
//   }
//
//   void window_draw::get_wnda(user::oswindow_array & hwnda)
//   {
//      System.frames().get_wnda(hwnda);
//   }
//
   // Both the device context and clip region
   // should be in screen coordinates

//   bool window_draw::ScreenOutput(
//      user::buffer * pbuffer,
//      ::draw2d::region & rgnUpdate)
//   {
//      UNREFERENCED_PARAMETER(pbuffer);
//      UNREFERENCED_PARAMETER(rgnUpdate);
//   //   TRACE("//\n");
//   //   TRACE("window_draw::TwfScreenOutput\n");
//   //   TRACE("//\n");
//
////      DWORD dwTimeIn = get_tick_count();
//
//      user::oswindow_array hwnda;
//
//      get_wnda(hwnda);
//
//      user::window_util::SortByZOrder(hwnda);
//
//      ASSERT(FALSE);
//      /*for(int i = 0; i  < hwnda.get_size(); i++)
//      {
//         oswindow hwnd = hwnda[i];
//         ScreenOutput(
//            pbuffer,
//            hwnd,
//            rgnUpdate);
//      }*/
////      DWORD dwTimeOut = get_tick_count();
//   //   TRACE("//\n");
//   //   TRACE("// window_draw::TwfRender\n");
//   //   TRACE("// TickCount = %d \n", dwTimeOut - dwTimeIn);
//   //   TRACE("//\n");
//
//      return true;
//   }
//
//
//
//   bool window_draw::ScreenOutput(
//      // pdc is the source primitive::memory device context
//      // from which bitmap the screen is updated.
//      user::buffer * pbuffer,
//      // hwndParam ::user::interaction_impl device context
//      // is used from screen output
//      ::user::interaction* pwnd)
//   {
//      if(pwnd != NULL)
//      {
//         if(pwnd->m_bVoidPaint)
//         {
//            return true;
//         }
//         if(!pwnd->m_bVisible)
//         {
//            return true;
//         }
//         if(pwnd->IsIconic())
//         {
//            return true;
//         }
//         if(pwnd->m_pguie != NULL && pwnd->m_pguie != pwnd && !pwnd->m_pguie->m_bVisible)
//         {
//            return true;
//         }
//         if(pwnd->m_pimpl != NULL && pwnd->m_pimpl != pwnd && !pwnd->m_pimpl->m_bVisible)
//         {
//            return true;
//         }
//      }
//
//      oswindow hwndParam = (oswindow) pwnd->get_handle();
//#ifdef WINDOWSEX
//
//      HDC hdcScreen = ::GetDCEx(hwndParam, NULL,  DCX_CLIPSIBLINGS | DCX_WINDOW);
//
//      if(hdcScreen == NULL)
//      {
//         // If it has failed to get ::user::interaction_impl
//         // owned device context, try to get
//         // a device context from the cache.
//         hdcScreen = ::GetDCEx(hwndParam, NULL, DCX_CACHE | DCX_CLIPSIBLINGS | DCX_WINDOW);
//
//         // If no device context could be retrieved,
//         // nothing can be drawn at the screen.
//         // The function failed.
//         if(hdcScreen == NULL)
//            return false;
//      }
//
//      ::SelectClipRgn(hdcScreen, NULL);
//
//
//
//      ////////////////////////////////////////
//      //
//      // Routine:
//      // Preparation for the
//      // bit blitting screen output.
//      //
//      ////////////////////////////////////////
//
//      // get the update region bound box.
//      // rect rectUpdate;
//      // rgnUpdate.GetRgnBox(rectUpdate);
//
//      // get the ::user::interaction_impl client area box
//      // in screen coordinates.
//      rect64 rectWindow;
//      rectWindow = pwnd->m_rectParentClient;
//
//      // Output rectangle receive the intersection
//      // of ::user::interaction_impl box and update box.
//      //rect rectOutput;
//      //rectOutput.intersect(rectWnd, rectUpdate);
//
//      // OutputClient rectangle receive the Output
//      // rectangle in client coordinates.
//      //rect rectOutputClient(rectOutput);
//      //rectOutputClient -= rectWnd.top_left();
//   //   ::ScreenToClient(hwndParam, &rectOutputClient.top_left());
//   //   ::ScreenToClient(hwndParam, &rectOutputClient.bottom_right());
//
//      rect64 rectOutputClient(rectWindow);
//      rectOutputClient -= rectWindow.top_left();
//
//      // The ::user::interaction_impl owned device context is clipped
//      // with the update region in screen coordinates
//      // translated to ::user::interaction_impl client coordinates.
//      //::draw2d::region_sp rgnClip(get_app());
//      //rgnClip->CreateRectRgn(0, 0, 0, 0);
//      //rgnClip->CopyRgn(&rgnUpdate);
//      //rgnClip->OffsetRgn( - rectWnd.top_left());
//
//   //   ::SelectClipRgn(hdcScreen, rgnClip);
//
//      // Debug
//   #ifdef DEBUG
//      //rect rectClip;
//      //rgnClip->GetRgnBox(rectClip);
//   #endif
//
//      pbuffer->GetBuffer()->SetViewportOrg(0, 0);
//
//      point pt(0, 0);
//
//      ::SetViewportOrgEx(hdcScreen, 0, 0, &pt);
//
//      /////////////////////////////
//      //
//      // Routine:
//      // Bit blitting screen output.
//      //
//      /////////////////////////////
//
//   /*   if(!::DrawDibDraw ( pbuffer->m_drawdib.m_hdrawdib,
//         hdcScreen,
//         rectOutputClient.left,
//         rectOutputClient.top,
//         rectOutputClient.width(),
//         rectOutputClient.height(),
//         &(pbuffer->m_spdib.m_Info.bmiHeader), pbuffer->m_spdib.m_pcolorref,
//         rectOutput.left,
//         rectOutput.top,
//         rectOutput.width(),
//         rectOutput.height(),
//         0))
//      {
//         TRACE0("Bitmap not painted.\n");
//      }*/
//
//      if(::GetWindowLong(hwndParam, GWL_EXSTYLE) & WS_EX_LAYERED)
//      {
//         BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
//
//         rect64 rectWindow;
//         rectWindow = pwnd->m_rectParentClient;
//
//         point pt;
//         size sz;
//
//         pt = point(rectWindow.top_left());
//         sz = size(rectWindow.size());
//
//         if(pt.x < 0)
//         {
//            pt.x = 0;
//            sz.cx += pt.x;
//         }
//
//         if(pt.y < 0)
//         {
//            pt.y = 0;
//            sz.cy += pt.y;
//         }
//
//         class rect rcMonitor;
//
//         System.get_monitor_rect(0, &rcMonitor);
//
//         sz.cx = (LONG) min(rectWindow.right - pt.x, rcMonitor.right - pt.x);
//         sz.cy = (LONG) min(rectWindow.bottom - pt.y, rcMonitor.bottom - pt.y);
//
////         m_pbuffer->m_spdib->fill_channel(0xc0, visual::rgba::channel_alpha);
//
//         ::UpdateLayeredWindow(hwndParam, hdcScreen, &pt, &sz,
//            (HDC)(dynamic_cast<::metrowin::graphics * >(m_pbuffer->GetBuffer()))->get_os_data(),
//            &pt, 0, &blendPixelFunction, ULW_ALPHA);
//
//         class rect rectWin;
//         ::GetWindowRect(hwndParam, rectWin);
//         if(rect(rectWindow) != rectWin || (pwnd->m_pguie != NULL && (bool) pwnd->m_pguie->oprop("pending_layout")))
//         {
//
//
//            if(pwnd->m_pguie != NULL && (bool) pwnd->m_pguie->oprop("pending_layout"))
//            {
//               oswindow hwndZOrder = (oswindow) pwnd->m_pguie->oprop("pending_zorder").get_integer();
//               ::SetWindowPos(hwndParam, HWND_TOPMOST,
//                  (int) rectWindow.left, (int) rectWindow.top, (int) rectWindow.width(), (int) rectWindow.height(), SWP_SHOWWINDOW);
//               ::SetWindowPos(hwndParam, HWND_NOTOPMOST,
//                  (int) rectWindow.left, (int) rectWindow.top, (int) rectWindow.width(), (int) rectWindow.height(), SWP_SHOWWINDOW);
//               ::SetWindowPos(hwndParam, hwndZOrder,
//                  (int) rectWindow.left, (int) rectWindow.top, (int) rectWindow.width(), (int) rectWindow.height(), SWP_SHOWWINDOW | SWP_FRAMECHANGED);
//               /*simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pwnd->m_pguie);
//               if(pframe != NULL)
//               {
//                  pframe->ActivateFrame();
//               }*/
//               pwnd->m_pguie->oprop("pending_layout") = false;
//            }
//            else
//            {
//               ::SetWindowPos(hwndParam, NULL, (int) rectWindow.left, (int) rectWindow.top, (int) rectWindow.width(), (int) rectWindow.height(), SWP_SHOWWINDOW);
//            }
//         }
//
//      }
//      else
//      {
//         ::BitBlt(
//         hdcScreen,
//         (int) rectOutputClient.left,
//         (int) rectOutputClient.top,
//         (int) rectOutputClient.width(),
//         (int) rectOutputClient.height(),
//         (HDC)(dynamic_cast<::metrowin::graphics * >(m_pbuffer->GetBuffer()))->get_os_data(),
//         (int) rectWindow.left,
//         (int) rectWindow.top,
//         SRCCOPY);
//      }
//
//
//      /*::Rectangle(hdcScreen,
//         rectOutputClient.left,
//         rectOutputClient.top,
//         rectOutputClient.width(),
//         rectOutputClient.height());*/
//
//      ::ReleaseDC(hwndParam, hdcScreen);
//
////      DWORD dwTimeOut = get_tick_count();
//   //   TRACE("//\n");
//   //   TRACE("// window_draw::TwfOuputScreen\n");
//   //   TRACE("// TickCount = %d \n", dwTimeOut - dwTimeIn);
//   //   TRACE("//\n");
//
//      return true;
//#else
//
//throw todo(get_app());
//#endif
//   }
//
//
//
//
//   // The first ::user::interaction_impl handle in the array must belong
//   // to the higher z order ::user::interaction_impl.
   // The rectangle must contain all update region.
   // It must be in screen coordinates.



   // Remark: this optimization eliminates top level windows
   // that are lower z order siblings of a higher z order
   // top level ::user::interaction_impl that contains all
   // the update region in a opaque area.
   // It doesn�t eliminates from the update parent windows
   // obscured by opaque children.



} // namespace metrowin