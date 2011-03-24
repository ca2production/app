#include "StdAfx.h"
#include "frame.h"

namespace flag
{

   application::application()
   {
      m_strAppName            = "flag";
      m_strLicense            = "";
      m_strBaseSupportId      = "votagus_ca2_flag";
   }

   application::~application(void)
   {
   }



   bool application::initialize_instance()
   {
      factory().creatable_small < ::flag::pane_view >();
      factory().creatable_small < ::flag::document >();
      factory().creatable_small < ::flag::frame >();
      factory().creatable_small < ::flag::view >();

      if(!ca84::application::initialize_instance())
         return false;

	   ::userbase::single_document_template* pDocTemplate;
	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "html/frame",
		   &typeid(::flag::document),
		   &typeid(::flag::frame),       // main SDI frame ::ca::window
		   &typeid(pane_view));
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;
	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "html/frame",
         &typeid(::flag::document),
		   &typeid(::flag::frame),       // main SDI frame ::ca::window
		   &typeid(::flag::view));
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplateVideo = pDocTemplate;

      return true;
   }

   int application::exit_instance()
   {
      
      for(int i = 0; i < m_hwndaHidden.get_count(); i++)
      {
         ShowWindow(m_hwndaHidden[i], SW_RESTORE);
      }

      Sleep((1984 + 1977) * 2);

      return TRUE;
   }

   bool application::bergedge_start()
   {


      if(!_001ProcessShellCommand(command_line()))
         return false;

      return true;
   }

   void application::_001OnFileNew()
   {
      if(command_line().m_varQuery.has_property("client_only"))
      {
         if(command_line().m_varQuery.has_property("file"))
         {
            m_ptemplateVideo->open_document_file(command_line().m_varQuery["file"], TRUE, Application.m_puiInitialPlaceHolderContainer);
         }
         else
         {
            m_ptemplateVideo->open_document_file(NULL, TRUE, Application.m_puiInitialPlaceHolderContainer);
         }
      }
      else
      {
         if(command_line().m_varQuery.has_property("file"))
         {
            m_ptemplateVideo->open_document_file(command_line().m_varQuery["file"], TRUE, Application.m_puiInitialPlaceHolderContainer);
         }
         else
         {
            m_ptemplate_html->open_document_file(NULL, TRUE, Application.m_puiInitialPlaceHolderContainer);
         }
      }
   }


   ::document * application::_001OpenDocumentFile(var varFile)
   {
      if(!command_line().m_varQuery.has_property("client_only"))
      {
         m_ptemplate_html->open_document_file(NULL, TRUE, Application.m_puiInitialPlaceHolderContainer);
      }
      return m_ptemplateVideo->open_document_file(varFile, TRUE);
   }

   
   ::ca::application * application::get_app() const
   {
      return m_papp;
   }


   bool application::on_assert_failed_line(const char * lpszFileName, int iLine)
   {
      if(m_pwndMain != NULL)
      {
         m_pwndMain->PostMessage(12578);
      }
      return true;
   }


   bool application::final_handle_exception(::ca::exception & e)
   {
      for(int i = 0; i < m_hwndaHidden.get_count(); i++)
      {
         ShowWindow(m_hwndaHidden[i], SW_RESTORE);
      }
      return ca84::application::final_handle_exception(e);
   }

   application::helper_thread::helper_thread(::ca::application * papp) :
      ca(papp),
      thread(papp)
   {
   }

   int application::helper_thread::run()
   {
      application * papp = dynamic_cast < application * > (get_app());
      string strDir = Application.dir().userappdata("flag\\menu");
      papp->menu_view_check_menu_dir(strDir);
      HANDLE hDirectory =
         ::CreateFile((const char *) strDir,    // folder path 
                      FILE_LIST_DIRECTORY,
                      FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
                      NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
   
      if(INVALID_HANDLE_VALUE == hDirectory)
      {
         DWORD dwError = ::GetLastError();
         // handle error (see this FAQ)
         return dwError;
      }

      DWORD dwBytesReturned = 0;
      const DWORD dwBuffLength = 4096;
      BYTE buffer[dwBuffLength];
      WCHAR wchFileName[_MAX_PATH + 1];
      
      while(::ReadDirectoryChangesW(hDirectory, buffer, dwBuffLength, TRUE,
                                    FILE_NOTIFY_CHANGE_FILE_NAME |
                                    FILE_NOTIFY_CHANGE_LAST_WRITE |
                                    FILE_NOTIFY_CHANGE_CREATION, &dwBytesReturned, 
                                    NULL, NULL))
      {
         DWORD dwNextEntryOffset = 0;
         PFILE_NOTIFY_INFORMATION pfni = NULL;
         do
         {
            pfni = (PFILE_NOTIFY_INFORMATION)(buffer + dwNextEntryOffset);
            
            memcpy(wchFileName, pfni->FileName, pfni->FileNameLength);
            wchFileName[pfni->FileNameLength / sizeof(WCHAR)] = L'\0';
            string str;
            str = gen::international::unicode_to_utf8(wchFileName);
            papp->menu_view_check_menu_dir(strDir);
            dwNextEntryOffset += pfni->NextEntryOffset; // next please!
         }while(pfni->NextEntryOffset != 0);
      } 
      ::CloseHandle(hDirectory);
      return 0;
   }

   void application::menu_view_check_menu_dir(const char * psz)
   {
      stringa straPath;
      System.dir().ls(psz, &straPath);
      //if(straPath.get_size() == 0)
      {
         stringa straRelative;
         straPath.remove_all();
         string strSource;
         strSource = System.dir().commonprograms();
         if(strSource.has_char())
         {
            System.dir().rls(strSource, &straPath, NULL, &straRelative);
            for(int i = 0; i < straPath.get_size(); i++)
            {
               string str = System.dir().path(psz, straRelative[i]);
               System.dir().mk(System.dir().name(str));
               ::CopyFile(straPath[i], str , TRUE);
            }
         }
         straRelative.remove_all();
         straPath.remove_all();
         strSource = Application.dir().userprograms();
         if(strSource.has_char())
         {
            System.dir().rls(strSource, &straPath, NULL, &straRelative);
            for(int i = 0; i < straPath.get_size(); i++)
            {
               string str = System.dir().path(psz, straRelative[i]);
               System.dir().mk(System.dir().name(str));
               ::CopyFile(straPath[i], str, TRUE);
            }
         }
      }
   }

   void application::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      m_ptemplateVideo->open_document_file(itema[0].m_strPath);
   }


} // namespace flag





CLASS_DECL_CA2_FLAG ::ca::application * get_new_app()
{
   return new ::flag::application;
}

