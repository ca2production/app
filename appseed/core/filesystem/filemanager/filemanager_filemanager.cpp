//#include "framework.h"
//#include "framework.h"




namespace filemanager
{


   filemanager::filemanager(::aura::application * papp) :
      object(papp),
      ::aura::department(papp)
   {

//      output_debug_string("");

   }

   filemanager::~filemanager()
   {
   }

   bool filemanager::initialize()
   {
      
      

      set_data_server(&Application.dataserver());

      if(!filemanager::file_list_callback::initialize())
         return false;

      InitializeFileManager("filemanager/filemanager");

      m_ptemplateStd->m_strLevelUp.Empty();
      m_ptemplateStd->m_setToolbar[::filemanager::manager::mode_normal] = "filemanager_toolbar.xml";
      m_ptemplateStd->m_setToolbar[::filemanager::manager::mode_saving] = "filemanager_saving_toolbar.xml";
      m_ptemplateStd->m_setToolbar[::filemanager::manager::mode_import] = "filemanager_import_toolbar.xml";
      m_ptemplateStd->m_setToolbar[::filemanager::manager::mode_export] = "filemanager_export_toolbar.xml";
      m_ptemplateStd->m_dataidStatic = "FileManagerFavoritesList";
      //m_ptemplateStd->m_uiDialogBar = 0;
      //m_ptemplateStd->m_uiMenuBar = 0;
      m_ptemplateStd->m_strFilePopup = "filemanager\\file_popup.xml";
      //m_ptemplateStd->m_strFilePopupSubstId = 0;
      m_ptemplateStd->m_strFolderPopup = "filemanager\\folder_popup.xml";
      m_ptemplateStd->m_strPopup = "filemanager\\popup.xml";
      m_ptemplateStd->m_idExpandBox = 0;
      m_ptemplateStd->m_idCollapseBox = 0;
      m_ptemplateStd->m_pfilelistcallback = this;
      //m_ptemplateStd->m_pfilelistcallback->set_app(this);
      m_ptemplateStd->m_strDISection = Application.m_strAppName;



      m_ptemplateFs->m_strLevelUp.Empty();
      m_ptemplateFs->m_setToolbar[::filemanager::manager::mode_normal] = "filemanager_toolbar.xml";
      m_ptemplateFs->m_setToolbar[::filemanager::manager::mode_saving] = "filemanager_saving_toolbar.xml";
      m_ptemplateFs->m_setToolbar[::filemanager::manager::mode_import] = "filemanager_import_toolbar.xml";
      m_ptemplateFs->m_setToolbar[::filemanager::manager::mode_export] = "filemanager_export_toolbar.xml";
      m_ptemplateFs->m_dataidStatic = "FileManagerFavoritesList";
      //m_ptemplateFs->m_uiDialogBar = 0;
      //m_ptemplateFs->m_uiMenuBar = 0;
      m_ptemplateFs->m_strFilePopup = "filemanager\\file_popup.xml";
      //m_ptemplateFs->m_strFilePopupSubstId = 0;
      m_ptemplateFs->m_strFolderPopup = "filemanager\\folder_popup.xml";
      m_ptemplateFs->m_strPopup = "filemanager\\popup.xml";
      m_ptemplateFs->m_idExpandBox = 0;
      m_ptemplateFs->m_idCollapseBox = 0;
      m_ptemplateFs->m_pfilelistcallback = this;
      //m_ptemplateFs->m_pfilelistcallback->set_app(this);
      m_ptemplateFs->m_strDISection = "fs." + Application.m_strAppName;


      m_idFileManager = Application.m_strAppName;

      return true;

   }



   void filemanager::InitializeFileManager(const char * pszMatter)
   {

      System.factory().creatable_small < form >();
      System.factory().creatable_small < manager > ();
      System.factory().creatable_small < child_frame > ();
      System.factory().creatable_small < view > ();
      System.factory().creatable_small < path_view > ();
      System.factory().creatable_small <save_as_view > ();
      System.factory().creatable_small < left_view > ();
      System.factory().creatable_small < main_view > ();
      System.factory().creatable_small < manager > ();
      System.factory().creatable_small < file_list > ();
      System.factory().creatable_small < preview > ();
      System.factory().creatable_small < main_frame > ();
      System.factory().creatable_small < frame >();
      System.factory().creatable_small < tab_view > ();
//      System.factory().creatable_small < ::user::document > ();
      System.factory().creatable_small < form_child_frame > ();
      System.factory().creatable_small < ::simple_form_view > ();
      System.factory().creatable_small < ::filemanager::folder_selection_list_view > ();
      System.factory().creatable_small < folder_list_view > ();
      System.factory().creatable_small < operation_document > ();
      System.factory().creatable_small < operation_child_frame > ();
      System.factory().creatable_small < operation_view > ();
      System.factory().creatable_small < operation_info_view > ();
      System.factory().creatable_small < operation_list_view > ();
      System.factory().creatable_small < save_as_edit_view >();
      System.factory().creatable_small < save_as_button>();


      System.factory().creatable_small < fs::simple::view > ();
      System.factory().creatable_small < fs::simple::list_view > ();


      m_ptemplateStd = canew(manager_template(get_app()));
      Session.userex()->shell().initialize();
      m_ptemplateStd->Initialize(0, pszMatter);

      m_ptemplateStd->m_setToolbar[manager::mode_normal] = "filemanager_toolbar.xml";
      m_ptemplateStd->m_setToolbar[manager::mode_saving] = "filemanager_saving_toolbar.xml";
      m_ptemplateStd->m_setToolbar[manager::mode_import] = "filemanager_import_toolbar.xml";
      m_ptemplateStd->m_setToolbar[manager::mode_export] = "filemanager_export_toolbar.xml";


      m_ptemplateFs = canew(manager_template(get_app()));
      m_ptemplateFs->Initialize(0, string("fs.") + string(pszMatter));

      m_ptemplateForm = canew(::user::multiple_document_template(
         get_app(),
         pszMatter,
         System.type_info < ::html_document > (),
         System.type_info < form_child_frame > (),
         System.type_info < form > ()));

      m_ptemplateOperation = canew(::user::single_document_template(
         get_app(),
         pszMatter,
         System.type_info < operation_document > (),
         System.type_info < operation_child_frame > (),
         System.type_info < operation_view > ()));
   }



   void filemanager::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {

      item_action * pitemaction = dynamic_cast < item_action * > (this);
      if(pitemaction != NULL)
      {
         if(pitemaction->open_file(pdata, itema))
            return;
      }


      sp(::create) cc(allocer());
      cc->m_spCommandLine->m_varFile = itema[0]->m_filepath;
      request_create(cc);

   }



   bool filemanager::do_prompt_file_name(var & varFile, UINT nIDSTitle, uint32_t lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument)
   {

      sp(::userex::pane_tab_view) ppanetabview = NULL;
      if(pdocument->get_view() != NULL && pdocument->get_view()->GetTypedParent < ::userex::pane_tab_view > () != NULL)
      {
         ppanetabview = pdocument->get_view()->GetTypedParent < ::userex::pane_tab_view > ();
         ppanetabview->set_cur_tab_by_id("file_manager");
         ppanetabview->get_pane_by_id("file_manager")->m_bPermanent = false;
         ppanetabview->on_layout();
         ppanetabview->filemanager_manager().FileManagerSaveAs(pdocument);
         if(ppanetabview->GetParentFrame()->RunModalLoop() != "yes")
            return FALSE;
         varFile = ppanetabview->filemanager_manager().get_filemanager_data()->m_pmanager->m_strTopic;
         return TRUE;
      }

      UNREFERENCED_PARAMETER(nIDSTitle);
      UNREFERENCED_PARAMETER(lFlags);
      UNREFERENCED_PARAMETER(ptemplate);
      ASSERT(bOpenFileDialog == FALSE);
      sp(manager) pdoc =  (m_ptemplateStd->open());
      tab_view * pview = pdoc->get_typed_view < tab_view >();

#ifdef WINDOWSEX
      oswindow oswindowDesktop = ::GetDesktopWindow();
      rect rectOpen;
      ::GetWindowRect(oswindowDesktop, rectOpen);
      int32_t iWidth = rectOpen.width();
      int32_t iHeight = rectOpen.width();
      rectOpen.deflate(iWidth / 5, iHeight / 5);
      pview->GetParentFrame()->SetWindowPos(ZORDER_TOP, rectOpen.left,
         rectOpen.top,
         rectOpen.width(), rectOpen.height(), SWP_SHOWWINDOW);

#endif
      pview->set_cur_tab_by_id(1);
      pview->GetParentFrame()->RedrawWindow();
      pview->GetParentFrame()->RunModalLoop();
      varFile = pdoc->m_strTopic;
      pview->GetParentFrame()->DestroyWindow();
      return TRUE;

   }

   string filemanager::get_initial_browse_path(const char * pszDefault)
   {

      string strId;

      strId.Format("manager(%s)", m_ptemplateStd->m_strDISection);

      string strPath;

      if(data_get(strId + ".local://InitialBrowsePath", strPath))
      {

         Sess(get_app()).dir().mk(strPath);

         if(Sess(get_app()).dir().is(strPath))
         {

            return strPath;

         }

      }

      if(pszDefault != NULL && strlen(pszDefault) > 0)
      {

         strPath = pszDefault;

      }
      else
      {

         strPath = System.dir().get_desktop_folder();

      }

//      if(data_set(strId + ".local://InitialBrowsePath", strPath))
//      {
//
//         return strPath;
//
//      }

      return "";

   }


   void filemanager::on_request(::create * pcreate)
   {
      filemanager::callback::on_request(pcreate);
   }



} // namespace filemanager


