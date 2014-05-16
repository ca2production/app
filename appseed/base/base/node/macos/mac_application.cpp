#include "framework.h"
#include <mach-o/dyld.h>



namespace mac
{


   application::application(::base::application * papp) :
      element(papp)
   {
      ::thread::m_p.create(allocer());
      ::thread::m_p->m_p = this;

      MAC_THREAD(::thread::m_p.m_p)->m_pAppThread = this;

//      m_psystem = papp->m_pplaneapp->m_psystem;

  //    m_pfilemanager = NULL;
      // in non-running state until WinMain
      // xxx      m_hInstance = NULL;
      //      m_hLangResourceDLL = NULL;
    //  m_pszHelpFilePath = NULL;
     // m_pszProfileName = NULL;
      //m_pszRegistryKey = NULL;
      //      m_pRecentFileList = NULL;
      //m_pdocmanager = NULL;
      // xxx       m_atomApp = m_atomSystemTopic = NULL;
      //m_lpCmdLine = NULL;
      //      m_pCmdInfo = NULL;

      // initialize wait cursor state
      //      m_nWaitCursorCount = 0;
      m_hcurWaitCursorRestore = NULL;

      // initialize current printer state
      // xxx       m_hDevMode = NULL;
      // xxx       m_hDevNames = NULL;
//      m_nNumPreviewPages = 0;     // not specified (defaults to 1)

      // other initialization
  //    m_bHelpMode = FALSE;
      //      m_eHelpType = afxWinHelp;
      m_nSafetyPoolSize = 512;        // default size

      shell::theLinuxShell.Initialize();
   }

   application::~application()
   {

   }


   void application::_001OnFileNew()
   {
      //      ::ca2::smart_pointer < ::application_base > ::m_p->_001OnFileNew(NULL);
   }

   sp(::user::object) application::_001OpenDocumentFile(var varFile)
   {
      //    return ::ca2::smart_pointer < ::application_base > ::m_p->_001OpenDocumentFile(varFile);
      return NULL;
   }

   void application::_001EnableShellOpen()
   {
      // xxx       ASSERT(m_atomApp == NULL && m_atomSystemTopic == NULL); // do once

      // xxx       m_atomApp            = ::GlobalAddAtomW(::str::international::utf8_to_unicode(m_strAppName));
      // xxx       m_atomSystemTopic    = ::GlobalAddAtomW(L"system");
   }

   bool application::_001OnDDECommand(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      return FALSE;
   }

   
   HINSTANCE application::GetHinstance()
   {
      
      return NULL;
      
   }

   
   string application::get_version()
   {
      
      return "";

//      throw todo(get_app());

      /*      char lpszModuleFilePath[MAX_PATH + 1];
      GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);

      DWORD dw;

      DWORD dwResSize = GetFileVersionInfoSize(
      lpszModuleFilePath,
      &dw);


      if(dwResSize > 0)
      {
      LPVOID lpdata = new BYTE[dwResSize];
      if(GetFileVersionInfo(
      lpszModuleFilePath,
      0,
      dwResSize,
      lpdata))
      {
      UINT cbTranslate;
      struct LANGANDCODEPAGE {
      WORD wLanguage;
      WORD wCodePage;
      } *lpTranslate;

      // read the list of languages and code pages.

      VerQueryValue(lpdata,
      TEXT("\\VarFileInfo\\Translation"),
      (LPVOID*)&lpTranslate,
      &cbTranslate);

      string strKey;
      //for( i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
      for(int32_t i=0; i < 1; i++ )
      {
      LPTSTR lpsz;
      UINT uiSize;

      strKey.Format(
      TEXT("\\StringFileInfo\\%04x%04x\\FileDescription"),
      lpTranslate[i].wLanguage,
      lpTranslate[i].wCodePage);




      strKey.Format(
      TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
      lpTranslate[i].wLanguage,
      lpTranslate[i].wCodePage);

      // Retrieve file description for language and code page "i".
      VerQueryValue(lpdata,
      (LPTSTR) (const char *) strKey,
      (LPVOID *)&lpsz,
      &uiSize);


      string strVersion(lpsz, uiSize);

      return strVersion;
      }
      }
      delete [] (LPBYTE) lpdata;
      }
      */

      return "";

   }


   bool application::Ex2OnAppInstall()
   {
#ifdef IMPLEMENT_VISTA_TOOLS
      if(VistaTools::IsVista())
      {
         if(VistaTools::IsElevated() != S_OK)
         {
            TRACE0("Error! Installing application ( : (un)install run parameter ) without Elevation (required since Vista Windows version)");
            return false;
         }
      }
#endif
      return true;
   }


   bool application::Ex2OnAppUninstall()
   {

      throw todo(get_app());

      // xxx       if(VistaTools::IsVista())
      // xxx       {
      // xxx          if(VistaTools::IsElevated() != S_OK)
      // xxx          {
      // xxx             TRACE0("Error! Installing application ( : (un)install run parameter ) without Elevation (required since Vista Windows version)");
      // xxx             return false;
      // xxx          }
      // xxx       }
      return true;
   }

   bool application::DeferRegisterClass(LONG fToRegister, const char ** ppszClass)
   {

      throw todo(get_app());
      // xxx       return __end_defer_register_class(fToRegister, ppszClass);
      return false;
   }


   void application::LockTempMaps()
   {
      MAC_THREAD(::thread::m_p.m_p)->LockTempMaps();
   }

   bool application::UnlockTempMaps(bool bDeleteTemp)
   {
      return MAC_THREAD(::thread::m_p.m_p)->UnlockTempMaps(bDeleteTemp);
   }


   void application::TermThread(HINSTANCE hInstTerm)
   {
      /*      try
      {
      #ifdef DEBUG
      // check for missing ::ca2::LockTempMap calls
      if (__get_module_thread_state()->m_pCurrentWinThread->m_nTempMapLock != 0)
      {
      TRACE(::ca2::trace::category_AppMsg, 0, "Warning: Temp ::collection::map lock count non-zero (%ld).\n",
      __get_module_thread_state()->m_pCurrentWinThread->m_nTempMapLock);
      }
      #endif
      ::ca2::LockTempMaps(::ca2::smart_pointer < ::application_base >::m_p);
      ::ca2::UnlockTempMaps(::ca2::smart_pointer < ::application_base >::m_p, -1);
      }
      catch( ::exception::base* e )
      {
      e->Delete();
      }*/


   }





   // application
   HCURSOR application::LoadCursor(const char * lpszResourceName) const
   {
      return NULL;
   }

   HCURSOR application::LoadCursor(UINT nIDResource) const
   {
      return NULL;
   }

   HCURSOR application::LoadStandardCursor(const char * lpszCursorName) const
   {
      // xxx       return ::LoadCursor(NULL, lpszCursorName);
      return NULL;
   }

   HCURSOR application::LoadOEMCursor(UINT nIDCursor) const
   {

      // xxx       return ::LoadCursor(NULL, MAKEINTRESOURCE(nIDCursor));
      return NULL;

   }


   bool application::process_initialize()
   {

      return true;
      
   }


   bool application::initialize1()
   {

      MAC_THREAD(::thread::m_p.m_p)->set_run();

      return true;

   }


   bool application::initialize2()
   {
      return true;
   }

   bool application::initialize3()
   {
      return true;
   }

   // thread termination
   int32_t application::exit_instance() // default will 'delete this'
   {

      // avoid calling CloseHandle() on our own thread handle
      // during the thread destructor
      ::thread::m_p->set_os_data(NULL);

      MAC_THREAD(::thread::m_p.m_p)->m_bRun = false;
//      MAC_THREAD(::application_base::m_p.m_p->::thread::m_p.m_p)->m_bRun = false;

      int32_t iRet = ::base::application::exit_instance();

      //::ca2::smart_pointer<::application>::destroy();



      return iRet;
   }
   /*
   // Advanced: exception handling
   LRESULT application::ProcessWndProcException(::exception::base* e, const MESSAGE* pMsg)
   {
   return   ::win::thread::ProcessWndProcException(e, pMsg);
   }


   // Advanced: handling messages sent to message filter hook
   bool application::ProcessMessageFilter(int32_t code, LPMESSAGE lpMsg)
   {
   return  ::win::thread::ProcessMessageFilter(code, lpMsg);
   }


   // Advanced: access to GetMainWnd()
   ::user::interaction* application::GetMainWnd()
   {
   return ::win::thread::GetMainWnd();
   }



   void application::assert_valid() const
   {
   ::win::thread::assert_valid();
   }

   void application::dump(dump_context & dumpcontext) const
   {
   ::win::thread::dump(dumpcontext);
   }


   void application::CommonConstruct()
   {
   ::win::thread::CommonConstruct();
   }
   void application::Delete()
   {
   ::win::thread::Delete();
   }
   // 'delete this' only if m_bAutoDelete == TRUE

   bool application::DispatchThreadMessageEx(MESSAGE* msg)  // helper
   {
   return ::win::thread::DispatchThreadMessageEx(msg);
   }*/

   /*   ::draw2d::graphics * application::graphics_from_os_data(void * pdata)
   {
   return ::win::graphics::from_handle((HDC) pdata);
   }*/

   sp(::window) application::window_from_os_data(void * pdata)
   {
      return ::mac::window::from_handle((oswindow) pdata);
   }

   sp(::window) application::window_from_os_data_permanent(void * pdata)
   {
      ::window * pwnd = ::mac::window::FromHandlePermanent((oswindow) pdata);
      if(pwnd != NULL)
         return pwnd;
      user::interaction_ptr_array wndptra = System.frames();
      for(int32_t i = 0; i < wndptra.get_count(); i++)
      {
         if(wndptra[i].get_safe_handle() == (oswindow) pdata)
         {
            return wndptra[i].get_wnd();
         }
      }
      return NULL;
   }
   

   ::thread * application::GetThread()
   {

      return ::get_thread();
      
   }
   

   void application::set_thread(::thread * pthread)
   {
      
      ::set_thread(pthread);
      
   }
   

   ///////////////////////////////////////////////////////////////////////////
   // application Initialization

   void application::SetCurrentHandles()
   {
      //ASSERT(this == afxCurrentWinApp);
      //if(afxCurrentAppName != NULL)
      // return;
      //ASSERT(afxCurrentAppName == NULL);


      // Note: there are a number of _tcsdup (aka _strdup) calls that are
      // made here for the exe path, help file path, etc.  In previous
      // versions of ca2 API, this primitive::memory was never freed.  In this and future
      // versions this primitive::memory is automatically freed during application's
      // destructor.  If you are freeing the primitive::memory yourself, you should
      // either remove the code or set the pointers to NULL after freeing
      // the primitive::memory.

      // get path of executable
      /*   char szBuff[_MAX_PATH];
      DWORD dwRet = ::GetModuleFileName(m_hInstance, szBuff, _MAX_PATH);
      ASSERT( dwRet != 0 && dwRet != _MAX_PATH );
      if( dwRet == 0 || dwRet == _MAX_PATH )
      throw user_exception();*/

      /*
      LPTSTR lpszExt = ::PathFindExtension(szBuff);
      ASSERT(lpszExt != NULL);
      if( lpszExt == NULL )
      throw user_exception();

      ASSERT(*lpszExt == '.');
      *lpszExt = 0;       // no suffix
      */

      string strExeName;
      //string strTitle = System.load_string("System.title");
      // get the exe title from the full path name [no extension]
      strExeName = System.get_module_title();



      //      dynamic_cast < ::mac::thread * > ((smart_pointer < ::application >::m_p->::ca2::thread_sp::m_p))->m_hThread = __get_thread()->m_hThread;
      //    dynamic_cast < ::mac::thread * > ((smart_pointer < ::application >::m_p->::ca2::thread_sp::m_p))->m_nThreadID = __get_thread()->m_nThreadID;
      dynamic_cast < class ::mac::thread * > (::thread::m_p.m_p)->m_hThread      =  ::GetCurrentThread();


   }

   sp(::window) application::FindWindow(const char * lpszClassName, const char * lpszWindowName)
   {
      return window::FindWindow(lpszClassName, lpszWindowName);
   }

   sp(::window) application::FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow)
   {
      return window::FindWindowEx(hwndParent, hwndChildAfter, lpszClass, lpszWindow);
   }


   void application::get_time(struct timeval *p)
   {
#ifdef _WIN32
      FILETIME ft; // Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).
      GetSystemTimeAsFileTime(&ft);
      uint64_t tt;
      memcpy(&tt, &ft, sizeof(tt));
      tt /= 10; // make it usecs
      p->tv_sec = (long)tt / 1000000;
      p->tv_usec = (long)tt % 1000000;
#else
      gettimeofday(p, NULL);
#endif
   }

   void application::set_env_var(const string & var,const string & value)
   {
#if (defined(SOLARIS8) || defined(SOLARIS))
      {
         static std::collection::map<string, char *> vmap;
         if (vmap.find(var) != vmap.end())
         {
            delete[] vmap[var];
         }
         vmap[var] = new char[var.get_length() + 1 + value.get_length() + 1];
         sprintf(vmap[var], "%s=%s", var, value);
         putenv( vmap[var] );
      }
#elif defined _WIN32
      {
         string slask = var + "=" + value;
         _putenv( (const char *)slask);
      }
#else
      setenv(var, value, 1);
#endif
   }

   uint32_t application::get_thread_id()
   {
      return ::GetCurrentThreadId();
   }



   bool application::set_main_init_data(::core::main_init_data * pdata)
   {

      m_pmaininitdata = (::mac::main_init_data *) pdata;

      if(m_pmaininitdata != NULL && m_pimpl->is_system())
      {
         if(!win_init(m_pmaininitdata))
            return false;
      }

      return true;

   }

   bool application::win_init(main_init_data * pdata)
   {
      ASSERT(pdata->m_hPrevInstance == NULL);

      string strCmdLine          = pdata->m_strCommandLine;
      UINT nCmdShow              = pdata->m_nCmdShow;

      // handle critical errors and avoid Windows message boxes
      // xxx         SetErrorMode(SetErrorMode(0) | SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX);

      m_strCmdLine = strCmdLine;
      m_nCmdShow = nCmdShow;
      //pApp->SetCurrentHandles();
      SetCurrentHandles();

      __init_thread();

      return true;

   }

   bool application::update_module_paths()
   {
      string str;

      char * lpsz = str.GetBufferSetLength(1024);

      uint32_t size = 1024;

      if(_NSGetExecutablePath(lpsz, &size) == 0)
      {

         str.ReleaseBuffer();

      }
      else
      {

         lpsz = str.GetBufferSetLength(size);

         if(_NSGetExecutablePath(lpsz, &size) == 0)
         {

            str.ReleaseBuffer();

         }
         else
         {

            return false;

         }

      }

      m_strModuleFolder = ::dir::name(str);


      {

         char * pszCurDir = getcwd(NULL, 0);

         string strCurDir = pszCurDir;

         free(pszCurDir);

         if(file_exists_dup(::dir::path(strCurDir, "libcore.dylib")))
         {
            
            m_strCa2ModuleFolder = strCurDir;
            
         }
         else if(file_exists_dup(::dir::path(m_strModuleFolder, "libcore.dylib")))
         {
            
            m_strCa2ModuleFolder = m_strModuleFolder;
            
         }
         else
         {

            m_strCa2ModuleFolder = ::dir::name(::dir::pathfind(getenv("DYLD_LIBRARY_PATH"), "libcore.dylib", "rfs")); // readable - normal file - non zero sized
            
         }

      }


      return true;

   }


   sp(::user::printer) application::get_printer(const char * pszDeviceName)
   {

      sp(::mac2::printer) pprinter = Application.alloc (System.type_info < ::user::printer > ());

      if(!pprinter->open(pszDeviceName))
      {

         return NULL;

      }

      return pprinter;

   }
   
   
   void application::ShowWaitCursor(bool bShow)
   {
      
      UNREFERENCED_PARAMETER(bShow);
      
   }
   
    
    
    string application::draw2d_get_default_library_name()
    {
        
        return "draw2d_quartz2d";
        
    }
   string application::multimedia_audio_get_default_library_name()
   {
      
      return "audio_core_audio";
      
   }

   string application::multimedia_audio_mixer_get_default_library_name()
   {
      
      return "audio_mixer_core_audio";
   
   }
   string application::veriwell_multimedia_music_midi_get_default_library_name()
   {
      
      return "music_midi_core_audio";
      
   }
   
   
} // namespace mac





