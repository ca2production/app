#include "StdAfx.h"
#include "resource.h"

#include "frame.h"
#include "view.h"

#include "window_frame/FrameSchemaHardCoded005.h"


namespace platform
{
 
   frame::frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp),
      form_frame(papp)
   {
      m_pimagelist         = NULL;
      m_iFrameData         = 10;
      m_dataid             = "ca2_fontopus_votagus::platform::frame";

      m_bCustomFrame       = true;
      m_bFrameMoveEnable   = false;
      m_bHover             = false;
      m_bMouseLeaveTimer   = false;
      m_bOnDraw            = false;

      WfiEnableFullScreen();
   }

   frame::~frame()
   {
   }

   BOOL frame::PreCreateWindow(CREATESTRUCT& cs)
   {
      if( !simple_frame_window::PreCreateWindow(cs) )
         return FALSE;
      cs.dwExStyle &= ~WS_EX_WINDOWEDGE;
      ::DestroyMenu(cs.hMenu);
      cs.hMenu = NULL;
      return TRUE;
   }

   #ifdef _DEBUG
   void frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }


   #endif //_DEBUG

   void frame::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      simple_frame_window::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &frame::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &frame::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &frame::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &frame::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_MOUSELEAVE, pinterface, this, &frame::_001OnMouseLeave);
   }
   
   
   void frame::_001OnTimer(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj);
      UINT nIDEvent = ptimer->m_nIDEvent;
      
      static float theta;
      if(nIDEvent == 4321875)
      {
         KillTimer(nIDEvent);
         m_bMouseLeaveTimer = false;
         m_bHover = false;
         ShowWindow(SW_HIDE);
      }
      else if(nIDEvent == 3)
      {
         //AnimateStatusBar();
      }
      else if(nIDEvent == 1000)
      {
         ShowWindow(SW_RESTORE);
         KillTimer(nIDEvent);
         m_bTimerOn = false;
      }
      else if(nIDEvent == 8913)
      {
      }
      else if(nIDEvent == 1001)
      {
         m_bHideTimer = false;
         ShowWindow(SW_HIDE);
         KillTimer(1001);
      }
      else if(nIDEvent == 4033)
      {
         point pt;
         if(m_bHoverMouse && GetTickCount() > m_dwLastHover + 300)
         {
            OnHoverAction();
         }
         System.get_cursor_pos(&pt);
         if(!m_bHoverMouse && pt.x == 0 && pt.y == 0)
         {
            m_dwLastHover = ::GetTickCount();
            m_bHoverMouse = true;
               
         }
         else if(m_bHoverMouse && (pt.x > 10 || pt.y > 0))
         {
            m_bHoverMouse = false;
         }
         if(IsWindowVisible())
         {
            rect rectWindow;
            GetWindowRect(rectWindow);
            if(rectWindow.contains(pt))
            {
               m_bHideTimer = false;
               KillTimer(1001);
            }
            else if(!m_bHideTimer)
            {
               m_bHideTimer = true;
               SetTimer(1001, 500, NULL);
            }
         }
   // OpenGL animation code goes here
            
            //glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
            //glClear( GL_COLOR_BUFFER_BIT );
            
            /*glPushMatrix();
            glRotatef( theta, 0.0f, 1.0f, 1.0f );
            glBegin( GL_TRIANGLES );
            glColor3f( 1.0f, 0.0f, 0.0f ); glVertex2f( 0.0f, 1.0f );
            glColor3f( 0.0f, 1.0f, 0.0f ); glVertex2f( 0.87f, -0.5f );
            glColor3f( 0.0f, 0.0f, 1.0f ); glVertex2f( -0.87f, -0.5f );
            glEnd();
            glPopMatrix();*/
            
            //SwapBuffers( m_hdcOpenGL );
            
            theta += 2.0f;
         
      }
      //simple_frame_window::OnTimer(nIDEvent);
   }



   void frame::ShowControlBars(bool bShow)
   {
      UINT nShow;
      if(bShow)
      {
         nShow = SW_SHOW;
      }
      else
      {
         nShow = SW_HIDE;
      }

   /*   m_toolbar.ShowWindow(nShow);
      m_toolbarView.ShowWindow(nShow);
   //   m_statusbar.ShowWindow(nShow);
      m_menubar.ShowWindow(nShow);
      m_dialogbar.ShowWindow(nShow);*/

   }



   void frame::OnHoverAction()
   {
      ShowWindow(SW_RESTORE);
   }

   void frame::_001OnSize(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void frame::_001OnMouseMove(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      if(!m_bHover)
      {
         m_bHover = true;
         track_mouse_hover();
      }
      if(m_bMouseLeaveTimer)
      {  
         m_bMouseLeaveTimer = false;
         KillTimer(4321875);
      }
   }

   void frame::_001OnMouseLeave(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      m_bMouseLeaveTimer = true;
      m_bHover = false;
      SetTimer(4321875, 884, NULL);
   }

   void frame::_001OnCreate(gen::signal_object * pobj)
   {
//      SCAST_PTR(::user::win::message::create, pcreate, pobj);
      pobj->previous();

      m_bTimerOn = false;

      SetTimer(8913, 5000, 0);
      SetTimer(4033, 100, 0);
      ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);



      m_pimagelist = new image_list(get_app());

      m_pimagelist->create(16, 16, 0, 10, 10);
      m_pimagelist->add_matter_icon("system/language_icon.ico");


      if(!data_get("DockPosition", (int &) m_eposition))
      {
         m_eposition = position_left;
      }
      ShowWindow(SW_HIDE);
      //super_dock_on_bergedge();
   }  

   void frame::super_dock_on_bergedge()
   {
      if(System.command_line().m_varQuery.propset().has_property("show_platform") == 0)
      {
         return;
      }
      rect rectDesktop;
      bergedge::view * pview = GetTypedParent < bergedge::view >();
      pview->GetWindowRect(rectDesktop);
      ShowWindow(SW_RESTORE);
      switch(m_eposition)
      {
      case position_left:
         SetWindowPos(ZORDER_TOPMOST, 0, 0, 400, rectDesktop.height(), SWP_SHOWWINDOW);
         break;
      case position_top:
         SetWindowPos(ZORDER_TOPMOST, 0, 0, rectDesktop.width(), 400, SWP_SHOWWINDOW);
         break;
      case position_bottom:
         SetWindowPos(ZORDER_TOPMOST, 0, rectDesktop.height() - 400, rectDesktop.width(), 400, SWP_SHOWWINDOW);
         break;
      case position_right:
         SetWindowPos(ZORDER_TOPMOST, rectDesktop.width() - 400, 0, rectDesktop.width(), 400, SWP_SHOWWINDOW);
         break;
      }
   }


   window_frame::FrameSchema * frame::create_frame_schema()
   {
      window_frame::FrameSchemaHardCoded005 * pschema = new window_frame::FrameSchemaHardCoded005(get_app());
      pschema->m_pruntimeclassControlBoxButton = &typeid(MetaButton);
      pschema->SetStyle(window_frame::FrameSchemaHardCoded005::StyleTranslucidWarmGray);
      return pschema;
   }

   void frame::_000OnDraw(::ca::graphics * pgraphics)
   {
      if(m_bOnDraw)
         return;
      form_frame::_000OnDraw(pgraphics);
   }

} // namespace platform