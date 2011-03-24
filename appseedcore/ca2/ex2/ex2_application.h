#pragma once

class file_system;
typedef ca::smart_pointer < file_system > file_system_sp;
class Ex1FactoryImpl;

namespace gen
{
   class command_line;
}

namespace ex2
{

   class CLASS_DECL_ca application :
      public gen::application,
      virtual public ca::smart_pointer < ex2::application >
   {
   protected:
      ex1::file_system_sp m_spfilesystem;
   public:

      application();
      virtual ~application();

      virtual void SetCurrentHandles();

      virtual bool set_main_init_data(void * pdata);

      virtual bool process_initialize();

      virtual bool initialize1(); // cgcl // first initialization
      virtual bool initialize2(); // cst  // second initialization
      virtual bool initialize3(); // third initialization and so on...

      virtual bool initialize(); // last initialization

      virtual bool finalize();

      virtual int exit_instance();
      
      virtual ::ex1::file_system & file_system();
      virtual BOOL _001OnDDECommand(const char * lpcsz);
      virtual void _001EnableShellOpen();
      virtual ::document * _001OpenDocumentFile(var varFile);
      virtual void _001OnFileNew();

      virtual void _001ParseCommandLine(gen::command_line& rCmdInfo);
      virtual bool _001ProcessShellCommand(gen::command_line& rCmdInfo);

      virtual void Ex1SetCommandLineInfo(gen::command_line & rCmdInfo);
      virtual void Ex1GetCommandLineInfo(gen::command_line & rCmdInfo);

      virtual ::ca::application * get_app() const;

      virtual string get_version();

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual bool Ex2OnAppInstall();
      virtual bool Ex2OnAppUninstall();

      virtual BOOL DeferRegisterClass(LONG fToRegister, const char ** ppszClass);

      // Temporary ::collection::map management (locks temp ::collection::map on current thread)
      virtual void LockTempMaps();
      virtual BOOL UnlockTempMaps(BOOL bDeleteTemps = TRUE);
      virtual const char * RegisterWndClass(UINT nClassStyle, HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);

      virtual ::radix::thread * GetThread();
      virtual void set_thread(::radix::thread * pthread);
      virtual ::user::interaction * GetMainWnd();

      virtual ::ca::graphics * graphics_from_os_data(void * pdata);

      virtual ::ca::window * window_from_os_data(void * pdata);
      virtual ::ca::window * window_from_os_data_permanent(void * pdata);


      virtual ::ca::window * get_desktop_window();

      virtual ::ca::window * FindWindow(const char * lpszClassName, const char * lpszWindowName);
      virtual ::ca::window * FindWindowEx(HWND hwndParent, HWND hwndChildAfter, const char * lpszClass, const char * lpszWindow);

      virtual void get_time(timeval *p);
      virtual void set_env_var(const string & var,const string & value);
      virtual unsigned long get_thread_id();

   };

} // namespace ex2


