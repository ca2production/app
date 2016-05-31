#pragma once


#include <shellapi.h>
#include <wincrypt.h>



#include "windows_base_file.h"
#include "windows_multithreading.h"
#include "windows_utils.h"


char get_drive_letter(const char * lpDevicePath);

CLASS_DECL_ACE void set_main_thread(HANDLE hThread);
CLASS_DECL_ACE void set_main_thread_id(UINT uiThread);


CLASS_DECL_ACE HANDLE get_main_thread();
CLASS_DECL_ACE UINT   get_main_thread_id();

#ifdef __cplusplus

CLASS_DECL_ACE void attach_thread_input_to_main_thread(bool bAttach = true);

#endif


#ifdef __cplusplus

CLASS_DECL_ACE string key_to_char(WPARAM wparam, LPARAM lparam);
CLASS_DECL_ACE string read_resource_as_string_dup(HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);

#endif

#define MESSAGE MSG
#define LPMESSAGE LPMSG


CLASS_DECL_ACE int WinRegGetValueW(HKEY hkey, LPCWSTR lpSubKey, LPCWSTR lpValue, DWORD dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData);

#ifdef __cplusplus

#include "windows_comptr.h"

#endif

#include "windows.inl"







