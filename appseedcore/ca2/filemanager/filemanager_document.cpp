#include "StdAfx.h"
#include "FileManagerViewUpdateHint.h"
#include "SimpleFileListInterface.h"


namespace filemanager
{

   document::document(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::document(papp),
      ::userbase::document(papp),
      ::fs::document(papp)
   {
      set_data(new filemanager::data(papp));
      command_signalid id;
      connect_update_cmd_ui("levelup", &document::_001OnUpdateLevelUp);
      connect_command("levelup", &document::_001OnLevelUp);
      connect_update_cmd_ui("add_location", &document::_001OnUpdateAddLocation);
      connect_command("add_location", &document::_001OnAddLocation);
      connect_update_cmd_ui("replace_text_in_file_system", &document::_001OnUpdateReplaceText);
      connect_command("replace_text_in_file_system", &document::_001OnReplaceText);
      connect_update_cmd_ui("edit_paste", &document::_001OnUpdateEditPaste);
      connect_command("edit_paste", &document::_001OnEditPaste);
      connect_update_cmd_ui("file_save", &document::_001OnUpdateFileSaveAs);
      connect_command("file_save", &document::_001OnFileSaveAs);
      connect_update_cmd_ui("cancel", &document::_001OnUpdateEditPaste);
      connect_command("cancel", &document::_001OnEditPaste);
   }

   document::~document()
   {
   }

   BOOL document::on_new_document()
   {
      if (!::userbase::document::on_new_document())
         return FALSE;




      return TRUE;
   }

   #ifdef _DEBUG
   void document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::userbase::document::dump(dumpcontext);
   }
   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // document serialization
   /*
   void document::Serialize(CArchive& ar)
   {
   if (ar.IsStoring())
   {
   // TODO: add storing code here
   }
   else
   {
   // TODO: add loading code here
   }
   }
   */
   /////////////////////////////////////////////////////////////////////////////
   // document commands

   void document::OnFileManagerBrowse()
   {
      {
         FileManagerViewUpdateHint uh;
         uh.set_type(FileManagerViewUpdateHint::TypePreSynchronize);
         update_all_views(NULL, 0, &uh);
      }
      {
         FileManagerViewUpdateHint uh;
         uh.set_type(FileManagerViewUpdateHint::TypeSynchronize);
         update_all_views(NULL, 0, &uh);
      }
      FileManagerInterface::OnFileManagerBrowse();
   }

   void document::OpenSelectionProperties()
   {
      {
         FileManagerViewUpdateHint uh;
         uh.set_type(FileManagerViewUpdateHint::TypeOpenSelectionProperties);
         update_all_views(NULL, 0, &uh);
      }

   }


   bool document::_001OnCommand(id id)
   {
      if(id == get_filemanager_data()->m_ptemplate->m_strLevelUp)
      {
         FileManagerOneLevelUp();
         return true;
      }
      return ::userbase::document::_001OnCommand(id);
   }

   bool document::_001OnUpdateCmdUi(cmd_ui * pcmdui)
   {
      /*if(pcmdui->m_id == get_filemanager_data()->m_ptemplate->m_strLevelUp)
      {
      FileManagerOnUpdateLevelUp(pcmdui);
      return true;
      }*/
      return ::userbase::document::_001OnUpdateCmdUi(pcmdui);
   }


   /*bool document::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
   {
   /*if (nCode == CN_UPDATE_COMMAND_UI)
   {
   cmd_ui * pcmdui = (cmd_ui *) pExtra;
   if(nID == get_filemanager_data()->m_ptemplate->m_uiLevelUp)
   {
   FileManagerOnUpdateLevelUp(pcmdui);
   return TRUE;
   }
   }
   else
   {
   int nMsg = HIWORD(nCode);
   nCode = LOWORD(nCode);

   // for backward compatibility HIWORD(nCode)==0 is WM_COMMAND
   if (nMsg == 0)
   nMsg = WM_COMMAND;

   if(nMsg == WM_COMMAND)
   {
   if(nID == get_filemanager_data()->m_ptemplate->m_uiLevelUp)
   {
   FileManagerOnLevelUp();
   return TRUE;
   }
   }
   }*/
   /*   return ::userbase::document::_001OnCmdMsg(pcmdmsg);
   }
   */

   void document::_001OnUpdateLevelUp(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
         if(m_item.m_strPath.is_empty())
         {
            pcmdui->m_pcmdui->Enable(FALSE);
         }
         else
         {
            pcmdui->m_pcmdui->Enable(TRUE);
         }
         pobj->m_bRet = true;
   }

   void document::_001OnLevelUp(gen::signal_object * pobj)
   {
      FileManagerOneLevelUp();
      pobj->m_bRet = true;
   }

   void document::_001OnUpdateAddLocation(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
         pcmdui->m_pcmdui->Enable(TRUE);
      pobj->m_bRet = true;
   }

   void document::_001OnAddLocation(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      update_all_views(NULL, 89124592, NULL);
   }

   void document::_001OnUpdateReplaceText(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
         pcmdui->m_pcmdui->Enable(TRUE);
      pobj->m_bRet = true;
   }

   void document::_001OnReplaceText(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      update_all_views(NULL, 89124593, NULL);
   }

   void document::_001OnUpdateEditPaste(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)

         pcmdui->m_pcmdui->Enable(System.m_strCopy.is_empty());
      pobj->m_bRet = true;
   }

   void document::_001OnEditPaste(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);   
      //System.file().paste(get_filemanager_data()->GetFileManager()->get_item().m_strPath, System.m_strCopy);
      //update_all_views(NULL, 123, NULL);
      //pobj->m_bRet = true;
   }

   void document::_001OnUpdateFileSaveAs(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
         pcmdui->m_pcmdui->Enable(TRUE);
   }

   void document::_001OnFileSaveAs(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);

      if(get_filemanager_data()->is_saving())
      {
         FileManagerViewUpdateHint uh;
         uh.m_pmanager = this;
         uh.set_type(FileManagerViewUpdateHint::TypeSaveAsOK);
         update_all_views(NULL, 0, &uh);
      }

   }

   void document::Initialize(bool bMakeVisible)
   {
      string str;
      str.Format("document(%s)", get_filemanager_data()->m_ptemplate->m_strDISection);
      m_dataid = str;




      CreateViews();

      FileManagerViewUpdateHint uh;


      uh.m_pmanager = this;

      if(data_get("InitialBrowsePath", ::ca::system::idEmpty, str))
      {
         FileManagerBrowse(str);
      }
      else
      {
         FileManagerBrowse("");
      }

      uh.set_type(FileManagerViewUpdateHint::TypeCreateBars);
      update_all_views(NULL, 0, &uh);

      if(bMakeVisible)
      {
         uh.set_type(FileManagerViewUpdateHint::TypePop);
         update_all_views(NULL, 0, &uh);
      }

   }

   void document::OpenFolder(::fs::item &item)
   {
      data_set("InitialBrowsePath", ::ca::system::idEmpty, item.m_strPath);
      get_filemanager_data()->OnFileManagerOpenFolder(item);
      FileManagerBrowse(item.m_strPath);
   }

   void document::CreateViews()
   {

      FileManagerViewUpdateHint uh;
      uh.m_pmanager = this;
      uh.set_type(FileManagerViewUpdateHint::TypeCreateViews);
      update_all_views(NULL, 0, &uh);

      uh.set_type(FileManagerViewUpdateHint::TypeInitialize);
      uh.m_uiId = get_filemanager_data()->m_iDocument;
      uh.m_pmanager = this;
      update_all_views(NULL, 0, &uh);


   }

   void document::PopViews()
   {
      FileManagerViewUpdateHint uh;
      uh.m_uiId = get_filemanager_data()->m_iDocument;
      uh.m_pmanager = this;
      uh.set_type(FileManagerViewUpdateHint::TypeCreateBars);
      update_all_views(NULL, 0, &uh);

      uh.set_type(FileManagerViewUpdateHint::TypePop);

      update_all_views(NULL, 0, &uh);
   }

   bool document::HandleDefaultFileManagerItemCmdMsg(BaseCmdMsg * pcmdmsg, ::fs::item_array & itema) 
   {
      if(pcmdmsg->m_etype == BaseCmdMsg::type_cmdui)
      {
         if(get_filemanager_data()->m_pcallback->GetFileManagerItemCallback(
            get_filemanager_data(), pcmdmsg->m_pcmdui->m_id, itema))
         {
            get_filemanager_data()->m_pcallback->OnFileManagerItemUpdate(
               get_filemanager_data(), pcmdmsg->m_pcmdui, itema);
            return TRUE;
         }
      }
      else
      {
         if(get_filemanager_data()->m_pcallback->GetFileManagerItemCallback(
            get_filemanager_data(), pcmdmsg->m_id, itema))
         {
            get_filemanager_data()->m_pcallback->OnFileManagerItemCommand(
               get_filemanager_data(), pcmdmsg->m_id, itema);
            return true;
         }
      }
      return false;
   }


   file_manager_operation_document * document::get_operation_doc(bool bSwitch)
   {
      FileManagerTabView * ptabview = get_typed_view < FileManagerTabView > ();
      if(ptabview == NULL)
         return NULL;

      ASSERT(ptabview != NULL);
      if(ptabview != NULL)
      {
         if(bSwitch)
         {
            ptabview->set_cur_tab_by_id(200000);
         }
         else
         {
            ptabview->ensure(200000);
         }
         return dynamic_cast < file_manager_operation_document * >
            (ptabview->get(200000)->m_pdoc);
      }
      return NULL;
   }

   void document::GetActiveViewSelection(::fs::item_array & itema)
   {
      FileManagerViewUpdateHint uh;
      uh.set_type(FileManagerViewUpdateHint::TypeGetActiveViewSelection);
      update_all_views(NULL, 0, &uh);
      itema = uh.m_itemaSelected;
   }


   void document::FileManagerSaveAs(::document * pdocument)
   {
      FileManagerInterface::FileManagerSaveAs(pdocument);
      FileManagerViewUpdateHint uh;
      uh.m_pmanager = this;
      uh.set_type(FileManagerViewUpdateHint::TypeSaveAsStart);
      update_all_views(NULL, 0, &uh);
      uh.set_type(FileManagerViewUpdateHint::TypeCreateBars);
      update_all_views(NULL, 0, &uh);
   }




   data * document::get_filemanager_data()
   {
      return dynamic_cast < data * > (::ca::data_container::get_data());
   }

} // namespace filemanager