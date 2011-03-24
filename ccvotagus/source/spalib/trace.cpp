#include "StdAfx.h"
#include "../../../appseedcore/_/mutex_lock.h"
#include <io.h>
#include <fcntl.h>
#include <share.h>
#include <sys/stat.h>
#include <sys/types.h>

void on_trace(std::string & str, std::string & str2);

HANDLE g_hmutexTrace;
stra g_straTrace;
//int g_iTrace = -1;
FILE * g_ftrace = NULL;
std::string g_strLastStatus;
int g_iLastStatus = 0;


void ensure_trace_file()
{
   try
   {
      dir::mk(dir::ca2().c_str());
      g_ftrace = fopen(dir::ca2("install.log").c_str(), "ab");
   }
   catch(...)
   {
   }
}


void trace(const char * psz)
{
   if(str_begins_ci(psz, "***"))
   {
      g_iLastStatus = 0;
      if(g_strLastStatus != psz)
      {
         g_strLastStatus = psz;
      }
   }
   else
   {
		if(str_begins_ci(g_strLastStatus.c_str(), "***"))
      {
         g_iLastStatus++;
         if(g_iLastStatus >= 23)
         {
            trace(g_strLastStatus.c_str());
         }
      }
   }
   std::string str;
   {
      mutex_lock lockTrace(g_hmutexTrace);
      g_straTrace.push_back(psz);
      str = g_straTrace[g_straTrace.size() - 1];
   }
   std::string str2(str);
   str2 = "\r\n" + str2;
   on_trace(str, str2);
}

void trace_add(const char * psz)
{
   std::string str;
   {
      mutex_lock lockTrace(g_hmutexTrace);
      if(g_straTrace.size() == 0)
         g_straTrace.push_back(psz);
      else
         g_straTrace[g_straTrace.size() - 1] += psz;
      str = g_straTrace[g_straTrace.size() - 1];
   }
   std::string str2(psz);
   on_trace(str, str2);
}

bool isspace_dup(char ch)
{
   if(ch=='\t')
      return true;
   if(ch==' ')
      return true;
   if(ch=='\r')
      return true;
   if(ch=='\n')
      return true;
   return false;
}

void on_trace(std::string & str, std::string & str2)
{
   if(::IsWindowVisible(g_hwnd))
   {
      if(str.length() > 3 && str.substr(0, 3) == "***")
      {
         SetWindowText(g_hwnd, str.substr(3).c_str());
      }
      else if(str.length() > 0 && str.substr(0, 1) != ".")
      {
         SetWindowText(g_hwnd, str.c_str());
      }
   }
   try
   {
      if(g_ftrace != NULL && str2.length() > 0)
      {
         fwrite(str2.c_str(), str2.length(), 1, g_ftrace);
         fflush(g_ftrace);
      }
   }
   catch(...)
   {
   }

}

