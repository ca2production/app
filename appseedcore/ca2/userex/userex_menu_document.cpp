#include "StdAfx.h"


menu_document::menu_document(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   ::document(papp),
   ::userbase::document(papp),
   html_document(papp),
   form_document(papp)
{
}

void menu_document::OnBeforeNavigate2(html::data * pdata, const char * lpszUrl, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel)
{
   form_document::OnBeforeNavigate2(pdata, lpszUrl, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
}
