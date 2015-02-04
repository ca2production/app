//#include "framework.h"


namespace user
{


   form::form(::aura::application * papp):
      element(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      ::user::form_interface(papp)
   {

      m_bOnEditUpdate         = false;
      m_bOnLanguageChange     = false;
      m_pcallback             = NULL;
      m_bInitialized          = false;

   }


   form::~form()
   {

   }


   index form::_001AddControl(class control::descriptor & descriptorParam)
   {

      //index indexNew = m_controldescriptorset.add(new class control::descriptor(descriptorParam));



      class control::descriptor * pdescriptor = m_controldescriptorset.add(new class control::descriptor(descriptorParam));

      descriptorParam.clear();

      pdescriptor->m_pform = this;

      if(pdescriptor->m_bTransparent)
      {

         switch(pdescriptor->m_etype)
         {
         case control_type_static:
         {
            /*xxx            CTransparentStatic * pstatic = (CTransparentStatic *) window::FromHandlePermanent(pform->get_child_by_id(pcontrol->m_id)->GetSafeoswindow_());
            if(pstatic == NULL || !base_class < CTransparentStatic >::bases(pstatic))
            {
            pstatic = new CTransparentStatic;
            VERIFY(pstatic->subclass_window(pform->get_child_by_id(pcontrol->m_id)->GetSafeoswindow_()));
            }
            pcontrol->m_unionwndptr.m_pstatic = pstatic;*/
         }
         break;
         default:
            break;

         }
      }

      if(pdescriptor->m_typeinfo)
      {

         if(pdescriptor->m_bCreated && pdescriptor->m_pcontrol != NULL)
         {

            pdescriptor->m_bCreated = false;

            pdescriptor->m_pcontrol.release();

            pdescriptor->m_pcontrol.release();

         }

         if((pdescriptor->m_pcontrol.m_p) != NULL)
         {
         }
         else
         {

            if(create_control(pdescriptor))
            {
            }
            else
            {
               // Failed creation
               ASSERT(FALSE);
            }
         }

      }
      else if(create_control(pdescriptor))
      {
      }
      if(pdescriptor->m_pcontrol != NULL)
      {
         //sp(type) ti = typeid(pdescriptor->m_pcontrol);
         /*         if(ti == System.type_info < ::user::list > ())
         {
         if(pdescriptor->m_etype == control_type_simple_list)
         {
         ::user::list * plist = dynamic_cast <::user::list *>(pdescriptor->m_pcontrol);
         plist->m_dataid = pdescriptor->m_idPrivateDataSection;
         plist->_001SetSingleColumnMode(false);
         }
         }*/
         /*else if(ti == System.type_info < simple_static > ())
         {
         simple_static * pstatic = (simple_static *) pcontrol->m_pwnd;
         pstatic->m_bTransparent = pcontrol->m_bTransparent;
         }*/

         _001OnInitializeForm(pdescriptor->m_pcontrol);

      }

      return m_controldescriptorset.get_upper_bound();

   }


   bool form::OnCommand(WPARAM wparam,LPARAM lparam)
   {

      UINT uiNotificationCode = HIWORD(wparam);

      UINT uiId = LOWORD(wparam);

      sp(control) pcontrol = m_controldescriptorset.get_control_by_id(uiId);

      if(pcontrol == NULL)
         return false;

      switch(pcontrol->descriptor().get_type())
      {
      case control_type_button:
         OnCommandButton(pcontrol,uiNotificationCode,lparam);
         break;
      case control_type_check_box:
         OnCommandCheckBox(pcontrol,uiNotificationCode,lparam);
         break;
      case control_type_combo_box:
         OnCommandComboBox(pcontrol,uiNotificationCode,lparam);
         break;
      case control_type_edit:
         OnCommandEdit(pcontrol,uiNotificationCode,lparam);
         break;
      default:
         break;
      }

      return false;

   }


   bool form::OnCommandButton(sp(control) pcontrol,UINT uiNotificationCode,LPARAM lparam)
   {

      UNREFERENCED_PARAMETER(lparam);

      ASSERT(pcontrol != NULL);

      if(pcontrol == NULL)
         return false;

      ASSERT(pcontrol->descriptor().get_type() == control_type_button);

#ifdef WINDOWS

      switch(uiNotificationCode)
      {
      case BN_CLICKED:
      {
         if(pcontrol->descriptor().has_function(control::function_action))
         {
            _001OnButtonAction(pcontrol);
            return true;
         }
      }
      break;
      default:
         break;
      }

#endif

      return false;
   }


   bool form::OnCommandCheckBox(sp(control) pcontrol,UINT uiNotificationCode,LPARAM lparam)
   {

      UNREFERENCED_PARAMETER(lparam);

      ASSERT(pcontrol != NULL);

      if(pcontrol == NULL)
         return false;

      ASSERT(pcontrol->descriptor().get_type() == control_type_check_box);

#ifdef WINDOWS

      switch(uiNotificationCode)
      {
      case BN_CLICKED:
      {
         /*      linux   ::user::button * pbutton = (::user::button *) get_child_by_id(pcontrol->m_id);
         int32_t i = pbutton->get_check() != 0;
         VmsDataSet(pcontrol->descriptor().m_dataid, 0, 0, i);*/
      }
      break;
      default:
         break;
      }

#endif

      return false;

   }


   bool form::OnCommandComboBox(sp(control) pcontrol,UINT uiNotificationCode,LPARAM lparam)
   {

      UNREFERENCED_PARAMETER(lparam);

      ASSERT(pcontrol != NULL);

      if(pcontrol == NULL)
         return false;

      ASSERT(pcontrol->descriptor().get_type() == control_type_combo_box);

#ifdef WINDOWS

      switch(uiNotificationCode)
      {
      case CBN_SELCHANGE:
      {
         /* linux         sp(::user::combo_box) pcombo = (sp(::user::combo_box)) get_child_by_id(pcontrol->m_id);
         int32_t iSel = pcombo->get_cur_sel();
         if(iSel != CB_ERR)
         {
         uint32_t dwData = pcontrol->GetComboBox()->m_dwaData[iSel];
         VmsDataSet(pcontrol->descriptor().m_dataid, 0, 0, (int32_t) dwData);
         }*/
      }
      break;
      case EN_KILLFOCUS:
      {
         //_001SaveEdit(control);
      }
      default:
         break;
      }

#endif

      return false;

   }


   bool form::OnCommandEdit(sp(control) pcontrol,UINT uiNotificationCode,LPARAM lparam)
   {

      UNREFERENCED_PARAMETER(lparam);

      ASSERT(pcontrol != NULL);

      if(pcontrol == NULL)
         return false;

      ASSERT(pcontrol->descriptor().get_type() == control_type_edit);

#ifdef WINDOWS

      switch(uiNotificationCode)
      {
      case EN_CHANGE:
      {
         if(pcontrol->descriptor().has_function(control::function_save_on_change))
         {
            _001SaveEdit(pcontrol);
         }
      }
      break;
      case EN_KILLFOCUS:
      {
         _001SaveEdit(pcontrol);
      }
      default:
         break;
      }

#endif

      return false;

   }


   bool form::_001SaveEdit(sp(control) pcontrol)
   {

      if(pcontrol == NULL)
         return false;

      ASSERT(pcontrol->descriptor().get_type() == control_type_edit || pcontrol->descriptor().get_type() == control_type_edit_plain_text);

      sp(::user::elemental) pedit = get_child_by_id(pcontrol->m_id);

      string str;

      if(pedit == NULL)
      {

         sp(::user::elemental) ptext = pcontrol;

         if(ptext == NULL)
            return false;

         ptext->_001GetText(str);

      }
      else
      {

         pedit->_001GetText(str);

      }

      if(!pcontrol->Validate(str))
      {
         // que tal um bal�o para indicar o erro
         return false;
      }

      var var;
      if(!pcontrol->get_data(pedit,var))
      {
         return false;
      }

      if(!_001Validate(pcontrol,var))
      {
         return false;
      }

      if(pcontrol->descriptor().has_function(control::function_vms_data_edit))
      {
         ::database::selection selection;
         _001GetSelection(pcontrol->descriptor().m_dataid,selection);

         ::database::update_hint uh;
         uh.add_self(this);

         data_set(selection,var,&uh);
      }
      return true;
   }


   void form::_001OnUpdate(sp(::aura::impact) pviewSender,LPARAM lhint,object* phint)
   {
      UNREFERENCED_PARAMETER(pviewSender);
      UNREFERENCED_PARAMETER(lhint);
      UNREFERENCED_PARAMETER(phint);
      for(int32_t i = 0; i < m_controldescriptorset.get_size(); i++)
      {
         sp(control) pcontrol = m_controldescriptorset[i]->m_pcontrol;
         if(pcontrol == NULL)
            continue;
         _001Update(pcontrol);
      }
   }

   void form::_001Update(sp(control) pcontrol)
   {
      ASSERT(pcontrol != NULL);
      if(pcontrol == NULL)
         return;
      switch(pcontrol->descriptor().get_type())
      {
      case control_type_check_box:
         _001UpdateCheckBox(pcontrol);
         break;
      case control_type_combo_box:
         _001UpdateComboBox(pcontrol);
         break;
      case control_type_edit:
      case control_type_edit_plain_text:
         _001UpdateEdit(pcontrol);
         break;
      case control_type_simple_list:
         _001UpdateSimpleList(pcontrol);
         break;
      default:
         break;
      }
   }

   void form::_001UpdateDbFlags(sp(control) pcontrol)
   {
      ASSERT(pcontrol != NULL);
      if(pcontrol == NULL)
         return;
      switch(pcontrol->descriptor().get_type())
      {
      case control_type_check_box:
         _001UpdateDbFlagsCheckBox(pcontrol);
         break;
         /*   case control_type_combo_box:
         _001UpdateComboBox(control);
         break;
         case control_type_edit:
         case control_type_edit_plain_text:
         _001UpdateEdit(control);
         break;
         case control_type_simple_list:
         _001UpdateSimpleList(control);
         break;*/
      default:
         break;
      }
   }

   void form::_001UpdateDbFlagsCheckBox(sp(control) pcontrol)
   {
      ASSERT(pcontrol != NULL);
      if(pcontrol == NULL)
         return;
      ASSERT(pcontrol->descriptor().get_type() == control_type_check_box);
      ASSERT(pcontrol->descriptor().m_eddx == control::ddx_dbflags);
      int_ptr_array ia;
      try
      {
         pcontrol->descriptor().m_ddx.m_pdbflags->m_key.m_pclient->data_load(pcontrol->descriptor().m_ddx.m_pdbflags->m_key.m_id,ia);
      }
      catch(...)
      {
         return;
      }
      {
         /*         check_box * pcheck = dynamic_cast < check_box * > (pcontrol);
         if(pcheck != NULL)
         {
         index i = 0;
         if(ia.BaseSortFind(pcontrol->descriptor().m_ddx.m_pdbflags->m_value, i))
         {
         pcheck->_001SetCheck(check::checked, false);
         }
         else
         {
         pcheck->_001SetCheck(check::unchecked, false);
         }
         }*/
      }
   }


   void form::_001UpdateCheckBox(sp(control) pcontrol)
   {
      ASSERT(pcontrol != NULL);
      if(pcontrol == NULL)
         return;
      ASSERT(pcontrol->descriptor().get_type() == control_type_check_box);
      int32_t i;
      if(data_get(pcontrol->descriptor().m_dataid,i))
      {
         /* linux      ::user::button * pbutton = (::user::button *) get_child_by_id(pcontrol->m_id);
         pbutton->SetCheck((i != 0) ? 1 : 0); */
      }
   }

   void form::_001UpdateComboBox(sp(control) pcontrol)
   {
      ASSERT(pcontrol != NULL);
      if(pcontrol == NULL)
         return;
      /* linux   ASSERT(pcontrol->descriptor().get_type() == control_type_combo_box);
      int32_t i;
      if(VmsDataGet(pcontrol->descriptor().m_dataid, 0, 0, i))
      {
      int_ptr iSel = pcontrol->GetComboBox()->m_dwaData.find_first((uint32_t) i);
      if(iSel >= 0)
      {
      sp(::user::combo_box) pcombo = (sp(::user::combo_box)) get_child_by_id(pcontrol->m_id);
      pcombo->set_cur_sel(iSel);
      }
      }*/
   }

   void form::_001UpdateEdit(sp(control) pcontrol)
   {
      ASSERT(pcontrol != NULL);
      if(pcontrol == NULL)
         return;

      if(m_bOnEditUpdate)
         return;
      keep<bool> keepUpdateLock(&m_bOnEditUpdate,true,false,true);

      ASSERT(pcontrol->descriptor().get_type() == control_type_edit
         || pcontrol->descriptor().get_type() == control_type_edit_plain_text);

      if(pcontrol->descriptor().has_function(control::function_vms_data_edit))
      {
         var var;
         ::database::selection selection;
         _001GetSelection(pcontrol->descriptor().m_dataid,selection);
         if(selection.get_item_count() > 0)
         {
            ::database::selection_item & item = selection.get_item(0);
            sp(::user::elemental) ptext = NULL;
            if(get_child_by_id(pcontrol->m_id) != NULL)
            {
               ptext = get_child_by_id(pcontrol->m_id);
            }
            if(ptext == NULL && pcontrol != NULL)
            {
               ptext = pcontrol;
            }
            if(ptext == NULL)
               return;
            if(data_get(pcontrol->descriptor().m_dataid.m_id + "." + item.m_id.m_id,var))
            {
               switch(var.get_type())
               {
               case var::type_string:
               {
                  string str;
                  str = var.m_str;
                  ptext->_001SetText(str,::action::source_database);
               }
               break;
               case var::type_int32:
               {
                  string str;
                  str.Format("%d",var.int32());
                  ptext->_001SetText(str,::action::source_database);
               }
               break;
               default:
                  ASSERT(FALSE);
                  break;
               }
            }
         }
      }
   }

   void form::_001UpdateSimpleList(sp(control) pcontrol)
   {
      ASSERT(pcontrol != NULL);
      if(pcontrol == NULL)
         return;

      ASSERT(pcontrol->descriptor().get_type() == control_type_simple_list);

      /*      ::user::list * plist = dynamic_cast<::user::list *>(get_child_by_id(pcontrol->m_id));

      if(typeid(plist->GetDataInterface()) == System.type_info < ::user::simple_list_data > ())
      {
      ::user::simple_list_data * pdata = dynamic_cast < ::user::simple_list_data * > (plist->GetDataInterface());
      stringa stra;
      data_get(pcontrol->descriptor().m_dataid, stra);
      ASSERT(plist != NULL);
      pdata->set_data(plist, stra);
      }*/
   }

   void form::_000OnPosCreate(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //      SCAST_PTR(::message::base, pbase, pobj)
   }

   void form::_001InitializeFormPreData()
   {
      if(m_pcallback != NULL)
      {
         m_pcallback->_001InitializeFormPreData(this);
      }

      /*
      if(GetOwner() != NULL)
      {
      GetOwner()->SendMessage(
      WM_USER + 723,
      GetDlgCtrlId(),
      (LPARAM) this);
      }
      */

   }


   bool form::_001GetData(id uiId,bool &bData)
   {
      sp(control) pcontrol = m_controldescriptorset.get_control_by_id(uiId);
      if(pcontrol == NULL)
         return false;

      int32_t i;
      if(!data_get(pcontrol->descriptor().m_dataid,i))
         return false;

      bData = (i != 0) ? 1 : 0;

      return true;

   }

   bool form::_001SetData(id uiId,bool bData)
   {
      sp(control) pcontrol = m_controldescriptorset.get_control_by_id(uiId);
      if(pcontrol == NULL)
         return false;

      int32_t i = bData ? 1 : 0;
      data_set(pcontrol->descriptor().m_dataid,i);
      return true;

   }

   void form::Update(bool bSave)
   {
      if(bSave)
      {

      }
      else
      {
         for(int32_t i = 0; i < m_controldescriptorset.get_size(); i++)
         {
            sp(control) pcontrol = m_controldescriptorset[i]->m_pcontrol;
            if(pcontrol == NULL)
               continue;
            _001Update(pcontrol);
         }
      }
   }

   void form::install_message_handling(::message::dispatch *pinterface)
   {
      ::user::scroll_view::install_message_handling(pinterface);
      /*   InstallOnDrawInterface(pinterface);
      VMSGEN_WINDOW_ON_SIZE_CONDITIONAL(pinterface, this, _001OnSize);
      VMSGEN_WINDOW_ON_VSCROLL_CONDITIONAL(pinterface, this, _001OnVScroll);
      VMSGEN_WINDOW_ON_HSCROLL_CONDITIONAL(pinterface, this, _001OnHScroll);
      //   VMSGEN_WINDOW_ON_PAINT_CONDITIONAL(pinterface, this, _001OnPaint);
      VMSGEN_WINDOW_ON_LBUTTONDOWN_CONDITIONAL(pinterface, this, _001OnLButtonDown);
      VMSGEN_WINDOW_ON_LBUTTONUP_CONDITIONAL(pinterface, this, _001OnLButtonUp);
      VMSGEN_WINDOW_ON_LBUTTONDBLCLK_CONDITIONAL(pinterface, this, _001OnLButtonDblClk);
      VMSGEN_WINDOW_ON_TIMER_CONDITIONAL(pinterface, this, _001OnTimer);*/
      IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&form::_001OnCreate);
      IGUI_MSG_LINK(::message::message_pos_create,pinterface,this,&form::_000OnPosCreate);
      //      IGUI_WIN_MSG_LINK(WM_COMMAND, pinterface, this, &form::_001OnCommand);
      //    IGUI_WIN_MSG_LINK(WM_NOTIFY, pinterface, this, &form::_001OnNotify);
      // revamp IGUI_WIN_MSG_LINK(user::MessageNotify, pinterface, this, &form::_001OnMessageNotify);
      IGUI_WIN_MSG_LINK(::axis::application::APPM_LANGUAGE,pinterface,this,&form::_001OnAppLanguage);

      //   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
      //   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN,pinterface,this,&::user::interaction::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP,pinterface,this,&::user::interaction::_001OnKeyUp);


      /*   InstallOnDrawInterface(pinterface);
      VMSGEN_WINDOW_ON_SIZE_CONDITIONAL(pinterface, this, _001OnSize);
      VMSGEN_WINDOW_ON_VSCROLL_CONDITIONAL(pinterface, this, _001OnVScroll);
      VMSGEN_WINDOW_ON_HSCROLL_CONDITIONAL(pinterface, this, _001OnHScroll);
      //   VMSGEN_WINDOW_ON_PAINT_CONDITIONAL(pinterface, this, _001OnPaint);
      VMSGEN_WINDOW_ON_LBUTTONDOWN_CONDITIONAL(pinterface, this, _001OnLButtonDown);
      VMSGEN_WINDOW_ON_LBUTTONUP_CONDITIONAL(pinterface, this, _001OnLButtonUp);
      VMSGEN_WINDOW_ON_LBUTTONDBLCLK_CONDITIONAL(pinterface, this, _001OnLButtonDblClk);
      VMSGEN_WINDOW_ON_TIMER_CONDITIONAL(pinterface, this, _001OnTimer);*/
      //IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &form::_001OnCreate);
      //IGUI_MSG_LINK(::message::message_pos_create, pinterface, this, &form::_000OnPosCreate);
      //      IGUI_WIN_MSG_LINK(WM_COMMAND, pinterface, this, &form::_001OnCommand);
      //    IGUI_WIN_MSG_LINK(WM_NOTIFY, pinterface, this, &form::_001OnNotify);
      // revamp IGUI_WIN_MSG_LINK(user::MessageNotify, pinterface, this, &form::_001OnMessageNotify);
      //IGUI_WIN_MSG_LINK(application::APPM_LANGUAGE, pinterface, this, &form::_001OnAppLanguage);

      //   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
      //   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
      //      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
      //    IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);

      //      IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&form::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER,pinterface,this,&form::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_USER + 123,pinterface,this,&form::_001OnUser123);

   }

   void form::_001GetSelection(::database::id & id,::database::selection &selection)
   {
      selection.add_item(id);
   }

   bool form::on_simple_action(id id)
   {
      return control::on_simple_action(id);
   }


   void form::_001OnNotify(signal_details * pobj)
   {

#ifdef WINDOWSEX

      SCAST_PTR(::message::notify,pnotify,pobj)

         pnotify->m_bRet = false;

#else

      throw todo(get_app());

#endif

   }


   void form::_001OnMessageNotify(signal_details * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj)

         // revamp pbase->set_lresult(user::NotifyRetContinue);

         pbase->m_bRet = false;

   }


   bool form::_001Validate(sp(control) pcontrol,var & var)
   {

      UNREFERENCED_PARAMETER(pcontrol);
      UNREFERENCED_PARAMETER(var);

      return true;

   }


   void form::_001RemoveControls()
   {

      m_controldescriptorset.remove_all();

   }


   bool form::_001OnBeforeSave(sp(control) pcontrol)
   {

      UNREFERENCED_PARAMETER(pcontrol);

      return true;

   }

   void form::data_on_after_change(signal_details * pobj)
   {

      SCAST_PTR(::database::change_event,pchange,pobj);

      if(pchange->m_puh != NULL)
      {

         if(pchange->m_puh->has_self(this))
         {

            return;

         }

      }

      for(int32_t iControl = 0; iControl < m_controldescriptorset.get_size(); iControl++)
      {

         sp(control) pcontrol = m_controldescriptorset[iControl]->m_pcontrol;

         if(pcontrol == NULL)
            continue;

         if(m_controldescriptorset[iControl]->m_eddx == control::ddx_dbflags)
         {

            _001UpdateDbFlags(pcontrol);

         }
         else if(m_controldescriptorset[iControl]->m_dataid == pchange->m_key.m_id)
         {

            _001Update(pcontrol);

         }

      }

   }


   void form::_001UpdateFunctionStatic()
   {

      for(int32_t i = 0; i < m_controldescriptorset.get_size(); i++)
      {

         class control::descriptor & descriptor = m_controldescriptorset(i);

         if(descriptor.has_function(control::function_static))
         {

            string str;

            str.load_string(get_app(),descriptor.m_id);

            descriptor.m_pcontrol->SetWindowText(str);

         }
         else if(descriptor.has_function(control::function_static2))
         {

            string str;

            str.load_string(get_app(),descriptor.m_uiText);

            descriptor.m_pcontrol->SetWindowText(str);

         }

      }

   }


   void form::WfiOnClose()
   {

      post_message(WM_CLOSE);

   }


   void form::_001OnInitializeForm(sp(control) pcontrol)
   {

      ::user::control_event ev;

      ev.m_puie         = pcontrol;
      ev.m_actioncontext        = ::action::source_database;
      ev.m_eevent       = ::user::event_initialize_control;
      ev.m_uiEvent      = 0;

      BaseOnControlEvent(&ev);

   }


   void form::_001OnButtonAction(sp(control) pcontrol)
   {

      UNREFERENCED_PARAMETER(pcontrol);

   }


   void form::_001OnAppLanguage(signal_details * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj)

         keep < bool > keepOnLanguageChange(&m_bOnLanguageChange,true,false,true);

      _017OnAppLanguage();

      pbase->m_bRet = false;

   }


   void form::_001OnCreate(signal_details * pobj)
   {

      //      SCAST_PTR(::message::create, pcreate, pobj)
      if(pobj->previous())
         return;

      //PostMessage(::message::message_pos_create);

   }


   void form::_001FillCombo(sp(control) pcontrol)
   {

      ASSERT(pcontrol != NULL);
      if(pcontrol == NULL)
         return;
      /* linux  if(pcontrol->GetComboBox() != NULL)
      {
      if(!pcontrol->GetComboBox()->m_datakeyFill.IsNull())
      {
      pcontrol->GetComboBox()->m_wstra.remove_all();
      pcontrol->GetComboBox()->m_dwaData.remove_all();
      var var;
      var.m_etype = var::type_element;
      var.m_pca2 = pcontrol->GetComboBox();
      VmsDataGet(
      pcontrol->GetComboBox()->m_datakeyFill,
      0, 0,
      var);
      sp(::user::combo_box) pcombo = (sp(::user::combo_box)) pcontrol->m_pwnd;
      pcombo->ResetContent();
      string str;
      for(int32_t i = 0; i < pcontrol->GetComboBox()->m_wstra.get_size(); i++)
      {
      str = pcontrol->GetComboBox()->m_wstra[i];
      pcombo->AddString(str);
      }

      }
      } */
   }


   void form::_017OnAppLanguage()
   {

      for(int32_t i = 0; i < m_controldescriptorset.get_size() ; i++)
      {
         class control::descriptor & descriptor = m_controldescriptorset(i);
         if(descriptor.m_typeinfo)
         {
            if(descriptor.m_bCreated && descriptor.m_pcontrol != NULL)
            {
            }
            else if(descriptor.m_bSubclassed && descriptor.m_pcontrol != NULL)
            {
               //            if(::IsWindow(pcontrol->m_pwnd->GetSafeoswindow_()))
               {
                  //xxx pcontrol->m_pwnd->unsubclass_window();
               }
               //            ASSERT(pcontrol->m_typeinfo->IsDerivedFrom(System.type_info < window > ()));
               if(descriptor.m_pcontrol.is_set())
               {
                  //window_id wndidTemp = get_child_by_id(pcontrol->m_id)->GetSafeoswindow_();
                  //if(wndidTemp != NULL)
                  {
                     //xxx        VERIFY(pcontrol->m_pwnd->subclass_window(wndidTemp));
                  }
               }
            }
            if(descriptor.m_pcontrol != NULL)
            {
               //               sp(type) ti = typeid(descriptor.m_pcontrol);
               /*               if(ti == System.type_info < ::user::list > ())
               {
               if(descriptor.m_etype == control_type_simple_list)
               {
               ::user::list * plist = dynamic_cast <::user::list *>(descriptor.m_pcontrol);
               plist->m_dataid = descriptor.m_idPrivateDataSection;
               plist->_001SetSingleColumnMode(false);
               }
               }*/
               /*            else if(pcontrol->m_typeinfo->IsDerivedFrom(System.type_info < simple_static > ()))
               {
               simple_static * pstatic = (simple_static *) pcontrol->m_pwnd;
               pstatic->m_bTransparent = pcontrol->m_bTransparent;
               }*/
               _001OnInitializeForm(descriptor.m_pcontrol);
            }
         }
      }

   }


   bool form::create_control(class control::descriptor * pdescriptor)
   {

      if(!normalize_control_descriptor_typeinfo(pdescriptor))
      {
         TRACE("form::create_control: failed to create control, could not find proper type for allocation");
         return false;
      }
      sp(element) pca = Application.alloc(pdescriptor->m_typeinfo);
      if(pca == NULL)
      {
         TRACE("form::create_control: failed to create control, allocation error");
         return false;
      }
      sp(class control) pcontrol = pca;
      if(pcontrol == NULL)
      {
         pca.release();
         TRACE("form::create_control: failed to create control, object is not derived from user::control::descriptor");
         return false;
      }
      if(!pcontrol->create_control(pdescriptor))
      {
         pcontrol.release();
         return false;
      }
      return true;
   }


   void form::_001SetControlFactory()
   {

   }


   string form::get_path()
   {
      return "";
   }


   bool form::open_document(var varFile)
   {

      if(!::user::form_interface::open_document(varFile))
         return false;

      return true;

   }


   bool form::BaseOnControlEvent(::user::control_event * pevent)
   {

      if(m_pcallback != NULL)
      {
         if(m_pcallback->BaseOnControlEvent(
            this,
            pevent))
            return true;
      }
      //else if(get_html_data()->m_pform != NULL
      //   && get_html_data()->m_pform->m_pcallback != NULL)
      //{
      //   if(get_html_data()->m_pform->m_pcallback->BaseOnControlEvent(
      //      this,
      //      pevent))
      //      return true;
      //}
      //if(form::BaseOnControlEvent(pevent))
      //   return true;
      //return false;

      if(pevent->m_eevent == ::user::event_tab_key)
      {

         sp(::user::elemental) pfocus = pevent->m_puie->keyboard_get_next_focusable();

         if(pfocus != NULL)
         {

            Session.user()->set_keyboard_focus(pfocus);

         }

      }
      else if(pevent->m_eevent == ::user::event_button_clicked)
      {
         class control::descriptor * pdescriptor = m_controldescriptorset.get(pevent->m_puie);
         if(pdescriptor == NULL)
            return false;
         if(pdescriptor->has_function(control::function_action))
         {
            if(pdescriptor->m_pcontrol != NULL)
            {
               _001OnButtonAction(pdescriptor->m_pcontrol);
               return true;
            }
            else
            {
               return false;
            }
         }
      }
      else if(pevent->m_eevent == ::user::event_set_check && pevent->m_actioncontext.is_user_source())
      {
         class control::descriptor * pdescriptor = m_controldescriptorset.get(pevent->m_puie);
         if(pdescriptor == NULL)
            return false;
         if(pdescriptor->m_eddx == control::ddx_dbflags)
         {
            int_ptr_array ia;
            pdescriptor->m_ddx.m_pdbflags->m_key.m_pclient->data_load(
               pdescriptor->m_ddx.m_pdbflags->m_key.m_id,
               ia);
            sp(elemental) pcheck = pevent->m_puie;
            if(pcheck->_001GetCheck() == check::checked)
            {
               ia.add_unique(pdescriptor->m_ddx.m_pdbflags->m_value);
            }
            else
            {
               ia.remove(pdescriptor->m_ddx.m_pdbflags->m_value);
            }
            pdescriptor->m_ddx.m_pdbflags->m_key.m_pclient->data_load(
               pdescriptor->m_ddx.m_pdbflags->m_key.m_id,
               ia);
         }
      }
      return false;
   }


   bool form::_001Initialize()
   {
      if(m_bInitialized)
         return true;
      _001InitializeFormPreData();
      _001UpdateFunctionStatic();
      //   CVmsGuiApp * papp = (CVmsGuiApp *) &System;
      //   papp->m_pcoreapp->TwfInitializeDescendants(pview->GetSafeoswindow_(), true);
      for(int32_t i = 0; i < m_controldescriptorset.get_size(); i++)
      {
         sp(control) pcontrol = m_controldescriptorset[i]->m_pcontrol;
         if(pcontrol == NULL)
            continue;
         _001Update(pcontrol);
      }

      m_bInitialized = true;

      return true;

   }


   bool form::_001IsPointInside(sp(control) pcontrol,point64 point)
   {

      if(pcontrol == NULL)
         return false;

      return pcontrol->_001IsPointInside(point);

   }



   bool form::normalize_control_descriptor_typeinfo(class ::user::control::descriptor * pdescriptor)
   {

      if(pdescriptor->m_typeinfo)
      {

         return true;

      }

      pdescriptor->m_typeinfo = controltype_to_typeinfo(pdescriptor->get_type());

      if(pdescriptor->m_typeinfo)
      {

         return true;

      }

      return false;

   }


   void form::OnBeforeNavigate2(var & varFile,uint32_t nFlags,const char * lpszTargetFrameName,byte_array& baPostedData,const char * lpszHeaders,bool* pbCancel)
   {

      UNREFERENCED_PARAMETER(varFile);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(lpszTargetFrameName);
      UNREFERENCED_PARAMETER(baPostedData);
      UNREFERENCED_PARAMETER(lpszHeaders);
      UNREFERENCED_PARAMETER(pbCancel);

   }


   void form::control_get_window_rect(sp(control) pcontrol,LPRECT lprect)
   {

      pcontrol->GetWindowRect(lprect);

   }

   void form::control_get_client_rect(sp(control) pcontrol,LPRECT lprect)
   {

      pcontrol->GetClientRect(lprect);

   }




   void form::on_update(::aura::impact * pSender,LPARAM lHint,object* phint)
   {

      ::aura::impact::on_update(pSender,lHint,phint);
      if(phint != NULL)
      {
         form_update_hint * puh = dynamic_cast < form_update_hint * > (phint);
         if(puh != NULL)
         {
            if(puh->m_etype == form_update_hint::type_browse)
            {
               if(!puh->m_strForm.is_empty())
               {
                  string str;
                  str = Application.dir().matter(puh->m_strForm);
                  if(get_document()->on_open_document(str))
                  {
                     m_strPath = puh->m_strForm;
                  }
               }
            }
            else if(puh->m_etype == form_update_hint::type_get_form_view)
            {
               puh->m_pformview = this;
            }
         }
         else
         {
            //html_view_update_hint * puh = dynamic_cast < html_view_update_hint * > (phint);
            //if(puh != NULL)
            //{
            //   if(puh->m_etype == html_view_update_hint::type_document_complete)
            //   {
            //      for(int32_t i = 0; i < get_html_data()->m_propertyset.m_propertya.get_count(); i++)
            //      {
            //         html::elemental * pelemental = get_html_data()->get_element_by_id(get_html_data()->m_propertyset.m_propertya[i]->name());
            //         if(pelemental != NULL)
            //         {
            //            pelemental->set_string(get_html_data()->m_propertyset.m_propertya[i]->get_string(), ::action::source_data);
            //         }
            //      }
            //   }

            //   {

            //      sp(::draw2d::graphics) dc(allocer());

            //      dc->CreateCompatibleDC(NULL);

            //      get_html_data()->implement(dc);

            //   }
            //   
            //}

         }

      }

      if(m_pcallback != NULL)
      {

         m_pcallback->on_update(this,pSender,lHint,phint);

      }

   }



   //void form::install_message_handling(::message::dispatch * pinterface)
   //{
   //   form::install_message_handling(pinterface);

   //}


   //void form::_001OnCreate(signal_details * pobj)
   //{
   //   pobj->previous();
   //}


   void form::_001OnTimer(signal_details * pobj)
   {
      SCAST_PTR(::message::timer,ptimer,pobj);
      if(m_pcallback != NULL)
      {
         ::user::control_event ev;
         ev.m_eevent = ::user::event_timer;
         ev.m_uiEvent = ptimer->m_nIDEvent;
         m_pcallback->BaseOnControlEvent(this,&ev);
      }
      if(ptimer->m_nIDEvent == 24)
      {
         KillTimer(24);
         GetTopLevelFrame()->EndModalLoop(IDOK);
      }
   }

   void form::_001OnUser123(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);
      if(pbase->m_wparam == 0x80000001)
      {
         if(GetTopLevel() != NULL)
         {
            GetTopLevel()->EndModalLoop(IDOK);
         }
         return;
      }
      if(m_pcallback != NULL)
      {
         m_pcallback->OnUser123(pbase->m_wparam,pbase->m_lparam);
      }
   }

   sp(type) form::controltype_to_typeinfo(::user::e_control_type e_type)
   {

      return Application.user_default_controltype_to_typeinfo(e_type);

   }


} // namespace user

