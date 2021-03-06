//#include "framework.h"

/*
namespace visual
{


   visual::visual(::draw2d::dib * pdib)
   {
      m_pdc = pgraphics;
   }


   visual::~visual()
   {
   }


   void visual::Polygon(const point_array & pointa)
   {
      m_pdc->Polygon(pointa.get_data(), (int32_t) pointa.get_size());
   }


} // visual


//#include "framework.h"

*/


namespace visual
{


   visual::visual(::aura::application * papp) :
      ::object(papp),
      ::aura::department(papp)
   {

      m_pimaging = NULL;
      m_pfontdepartment = NULL;
      m_pvisualapi = new ::visual::api(papp);
      defer_create_mutex();

   }


   visual::~visual()
   {

      ::aura::del(m_pimaging);
      ::aura::del(m_pvisualapi);
      ::aura::del(m_pfontdepartment);

   }


   void visual::construct(::aura::application * papp)
   {

      ::aura::department::construct(papp);



   }

   api & visual::api()
   {

      return *m_pvisualapi;

   }

   imaging & visual::imaging()
   {

      return *m_pimaging;

   }


   bool visual::initialize1()
   {

      if (!::aura::department::initialize1())
         return false;

      synch_lock sl(m_pmutex);

      if (m_pfontdepartment == NULL)
      {

         m_pfontdepartment = new class font_department(get_app());

         if (m_pfontdepartment == NULL)
            return false;

         if (!m_pfontdepartment->Initialize())
            return false;

      }

      if (m_pimaging == NULL)
      {

         m_pimaging = new class imaging(get_app());

         if (m_pimaging == NULL)
            throw memory_exception(get_app());

      }

      return true;

   }


   bool visual::process_initialize()
   {

      if (!::aura::department::process_initialize())
         return false;

      synch_lock sl(m_pmutex);

      if (!m_pvisualapi->open())
         return false;

      return true;

   }


   bool visual::initialize()
   {

      if (!::aura::department::initialize())
         return false;

      ////if(Application.dir().is(System.dir().commonappdata("")))
      //{

      //   __begin_thread(get_app(), &visual::thread_proc_parallel_initialize, this, ::multithreading::priority_highest);

      //}

      return true;

   }

   //uint32_t c_cdecl visual::thread_proc_parallel_initialize(void * pparamThis)
   //{

   //   visual * pvisual = (visual *)pparamThis;

   //   pvisual->set_cursor_set_from_matter("cursor/antialiased-classic");

   //   return 0;

   //}


   bool visual::finalize()
   {

      bool bOk = true;

      synch_lock sl(m_pmutex);

      try
      {

         if (m_pvisualapi != NULL)
         {

            bOk = m_pvisualapi->close();

         }

      }
      catch (...)
      {

         bOk = false;

      }

      try
      {

         if (m_pfontdepartment != NULL)
         {

            m_pfontdepartment->Finalize();

         }

      }
      catch (...)
      {


      }

      ::aura::del(m_pvisualapi);

      ::aura::del(m_pfontdepartment);

      ::aura::del(m_pimaging);

      for (auto & p : m_cursormap)
      {

         delete p.m_element2;

      }

      m_cursormap.remove_all();

      return bOk;

   }


   class font_department & visual::fonts()
   {
      return *m_pfontdepartment;
   }

   cursor * visual::set_cursor_file(e_cursor ecursor, const ::file::path & psz, bool bFromCache)
   {

      synch_lock sl(m_pmutex);

      cursor * pcursor = get_cursor(ecursor);

      if (System.visual().imaging().load_from_file(pcursor, psz, bFromCache))
      {

         return pcursor;

      }
      else
      {

         if (pcursor->initialize_system_default())
         {

            return pcursor;

         }

         return NULL;

      }

   }

   
   cursor * visual::set_system_default_cursor(e_cursor ecursor)
   {

      synch_lock sl(m_pmutex);

      cursor * pcursor = get_cursor(ecursor);

      if (pcursor->initialize_system_default())
      {

         return pcursor;

      }

      return NULL;

   }



   cursor * visual::get_cursor(e_cursor ecursor)
   {

      synch_lock sl(m_pmutex);

      cursor * pcursor = NULL;

      if (m_cursormap.Lookup(ecursor, pcursor))
      {

         return pcursor;

      }
      else
      {

         pcursor = new cursor(get_app());

         pcursor->m_ecursor = ecursor;

         m_cursormap.set_at(ecursor, pcursor);

         return pcursor;

      }

   }



   ::count visual::set_cursor_set_from_matter(const ::file::path & pszMatter)
   {

      // "arrow.png" is a troll/bait for getting the right path of the cursor file, then the directory where found

      return set_cursor_set_from_dir(Application.dir().matter(pszMatter / "arrow.png").folder(), true);

   }


   ::count visual::set_cursor_set_from_dir(const ::file::path & pszDir, bool bFromCache)
   {
      ::count count = 0;
      if (set_cursor_file(::visual::cursor_arrow, pszDir / "arrow.png", bFromCache))
      {
         count++;
      }
      else
      {
         return 0;
      }
      if (set_cursor_file(::visual::cursor_hand, pszDir / "hand.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_hand, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_text_select, pszDir / "text_select.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_text_select, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_top_left, pszDir / "size_top_left.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_top_left, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_top, pszDir / "size_top.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_top, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_top_right, pszDir / "size_top_right.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_top_right, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_right, pszDir / "size_right.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_right, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_bottom_right, pszDir / "size_bottom_right.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_bottom_right, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_bottom, pszDir / "size_bottom.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_bottom, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_bottom_left, pszDir / "size_bottom_left.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_bottom_left, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_left, pszDir / "size_left.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_left, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_vertical, pszDir / "size_vertical.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_vertical, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_horizontal, pszDir / "size_horizontal.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_horizontal, pszDir / "arrow.png", bFromCache);
      }

      return count;
   }


   ::count visual::set_cursor_set_system_default()
   {

      ::count count = 0;

      if (set_system_default_cursor(::visual::cursor_arrow))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_hand))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_text_select))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_top_left))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_top))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_top_right))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_right))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_bottom_right))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_bottom))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_bottom_left))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_left))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_vertical))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_horizontal))
      {
         count++;
      }

      return count;

   }


   // should not call axis class implementation because visual::visual is inside a n-furcation of user::visual
   int32_t visual::exit_application()
   {

      int32_t iExitCode = 0;

      try
      {

         iExitCode = ::aura::department::exit_application();

      }
      catch (...)
      {

         ::simple_message_box(NULL, "except", "except", MB_OK);

         iExitCode = -1;

      }

      return iExitCode;

   }


   bool visual::embossed_text_out(
      ::draw2d::graphics * pgraphics,
      LPCRECT lpcrect,
      string strText,
      ::visual::fastblur & dib2,
      ::draw2d::font * pfont,
      int iDrawTextFlags,
      COLORREF crText,
      COLORREF crGlow,
      int iSpreadRadius,
      int iBlurRadius,
      int iBlur,
      bool bUpdate,
      double dAlpha)
   {

      if (strText.is_empty())
      {

         return false;

      }

      auto pred = [&](::draw2d::graphics * pgraphics)
      {

         pgraphics->SelectObject(pfont);
         pgraphics->_DrawText(strText, *lpcrect, iDrawTextFlags);

      };

      bool bRet = emboss_pred(
         pgraphics,
         lpcrect,
         pred,
         dib2,
         crGlow,
         iSpreadRadius,
         iBlurRadius,
         iBlur,
         bUpdate,
         dAlpha);

      byte bA = (byte)(dAlpha * 255.0);
      ::draw2d::brush_sp brushText(allocer());
      brushText->create_solid((crText & 0x00ffffffu) | (bA << 24));
      pgraphics->SelectObject(brushText);
      pgraphics->SelectObject(pfont);
      pgraphics->_DrawText(strText, *lpcrect, iDrawTextFlags);

      return true;

   }


} // namespace visual
