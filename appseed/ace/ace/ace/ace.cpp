//#include "framework.h"

BEGIN_EXTERN_C
CLASS_DECL_ACE int g_bAura = 0;
END_EXTERN_C


BEGIN_EXTERN_C

CLASS_DECL_ACE uint32_t g_dwStartTime = 0;


END_EXTERN_C

extern "C"
CLASS_DECL_ACE void debug_print(const char * pszFormat,...)
{
   
   //if (strstr(pszFormat, "%") == NULL)
   //{
   //   
   //   ::OutputDebugStringW(wstring(pszFormat));
   //   
   //   return;

   //}

   va_list argList;

   va_start(argList,pszFormat);

   char sz[4096];

   vsnprintf(sz,sizeof(sz),pszFormat,argList);

   ::OutputDebugStringW(wstring(sz));

   va_end(argList);

}


//namespace std
//{
//
//   const nothrow_t nothrow;
//
//} // namespace std

int32_t ___()
{

   simple_message_box(NULL,"___ library of ca","___ library of ca",MB_ICONINFORMATION | MB_OK);

   return 0;

}


void __post_quit_message(int32_t nExitCode)
{

#ifdef WINDOWSEX

   ::PostQuitMessage(nExitCode);

#else

   ::get_thread_app()->post_quit();

#endif

}

string_map < INT_PTR,INT_PTR > * g_pmapLibrary = NULL;

string_map < INT_PTR, INT_PTR > & __library()
{
   return *g_pmapLibrary;
}





int g_iAuraRefCount = 0;


CLASS_DECL_ACE int get_ace_init()
{

   return g_iAuraRefCount;

}


::ace::system * ace_create_ace_system()
{

   return new ::ace::system(NULL, NULL);

}


CLASS_DECL_ACE int_bool defer_ace_init()
{

   g_iAuraRefCount++;

   if(g_iAuraRefCount > 1)
      return TRUE;

   if(!ace_init())
      return FALSE;

   g_pfn_create_system = ace_create_ace_system;

   s_pacestrpool = new ace_str_pool();

   g_bAura = 1;


   return TRUE;

}


CLASS_DECL_ACE int_bool defer_ace_term()
{

   g_iAuraRefCount--;

   if(g_iAuraRefCount >= 1)
      return TRUE;

   g_bAura = 0;

   ::ace::del(s_pacestrpool);

   ace_term();

   return TRUE;

}

#ifdef WINDOWS

void set_simple_output_debug_string();

void set_extended_output_debug_string();

#endif

bool ace_init()
{

   ::ace::static_start::init();

   if(!__node_ace_pre_init())
      return false;

   //::ace::static_start::init();

   __init_threading_count();

   ::multithreading::init_multithreading();

//   ::hthread::s_pmutex = new mutex();

  // ::hthread::s_pptra = new ref_array <  hthread >();


   if(!__node_ace_pos_init())
      return false;


#ifdef WINDOWS

   set_extended_output_debug_string();

#endif

   return true;

}


bool ace_term()
{

   __wait_threading_count(::millis((5000) * 8));

   __node_ace_pre_term();

   ::multithreading::term_multithreading();

   __term_threading_count();

#ifdef WINDOWS

   set_simple_output_debug_string();

#endif

   processor_cache_oriented_destroy_all_memory_pools();

   __node_ace_pos_term();

   ::ace::static_start::term();

   return true;

}




void dappy(const char * psz)
{

   //debug_print("app._ : %s : %s\n",_argv[2],psz);
   //debug_print("hello!!    : %s\n",psz);
   //::OutputDebugString("hello!!    : " + string(psz) + "\n");

}




::map < void *,void *,::ace::application *,::ace::application * > * g_pmapAura = NULL;

void set_ace(void * p,::ace::application * papp)
{

   g_pmapAura->set_at(p,papp);

}

::ace::application * get_ace(void * p)
{

   return g_pmapAura->operator [](p);

}




// note (casey) : according to cmuratori (Casey Muratori) "non initialized" (for "static" variables) is zero initialized
CLASS_DECL_ACE LPFN_CREATE_SYSTEM g_pfn_create_system;

CLASS_DECL_ACE const char * g_pszCooperativeLevel;

::ace::system * create_ace_system()
{
   
   return g_pfn_create_system();

}



int __cdecl debug_report(int,char const *,int,char const *,char const *,...)
{
   
   return 1;

}

CLASS_DECL_ACE void writeln(const char * psz)
{

   output_debug_string(string(psz) + "\n");

}