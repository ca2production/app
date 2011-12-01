#pragma once


class CLASS_DECL_ca Ex1FormInterfaceComboBox :
   virtual public ::radix::object
{
public:


   ::database::id       m_datakeyFill;
   stringa              m_wstra;
   dword_array          m_dwaData;


};


namespace user
{

   class form;
   class form_list;
   class form_callback;

   class CLASS_DECL_ca control :
      virtual public view
   {
   public:

      enum e_element
      {
         element_none,
         element_tab,
         element_close_tab_button,
         element_status_image,
         element_text,
         element_icon,
         element_border,
         element_client,
         element_area,
      };


      enum EMessageParam
      {
         MessageParamGetBaseControlExPtr = 1
      };


      enum e_type
      {
         type_none,
         type_static,
         type_check_box,
         type_edit,
         type_simple_list,
         type_button,
         type_combo_box,
         type_edit_plain_text,
      };
      enum efunction
      {
         // Text got from control m_uiId member
         function_static,
         // Text got from control m_uiText member
         function_static2,
         function_data_selection,
         function_save_on_change,
         function_vms_data_edit,
         function_action,
         function_edit_multi_line,
      };
      enum edatatype
      {
         DataTypeString,
         DataTypeNatural,
      };
      enum eddx
      {
         ddx_none,
         ddx_flags,
         ddx_dbflags,
      };

   // sort_array < INT_PR, INT_PTR >
      class ddx_dbflags
      {
      public:
         ddx_dbflags(::database::key key, INT_PTR value);
         ::database::key                               m_key;
         INT_PTR                                m_value;
      };

      class CLASS_DECL_ca descriptor
      {
      public:
         descriptor();
         descriptor(const descriptor & descriptor);
         virtual ~descriptor();
         form *                  m_pform;
         control *               m_pcontrol;
         id                      m_id;
           ::ca::type_info         m_typeinfo;
         int                     m_iSubItem;
         id                      m_idPrivateDataSection;
         bool                     m_bTransparent;
         e_type                     m_etype;
         bool                    m_bCreated;
         bool                    m_bSubclassed;
         eddx                    m_eddx;
         ::database::id                 m_dataid;
         flags < efunction >     m_flagsfunction;
         edatatype               m_edatatype;
         union
         {
            void *                     m_pvoid;
            class ddx_dbflags *        m_pdbflags;
         } m_ddx;
         union
         {
            void                       * m_pvoid;
            Ex1FormInterfaceComboBox   * m_pcombobox;
         } m_data;
         void clear();
         bool operator == (const descriptor & descriptor) const;
         descriptor & operator = (const descriptor & descriptor);
         e_type get_type();
         void set_type(e_type e_type);
         void add_function(efunction efunction);
         void remove_function(efunction efunction);
         bool has_function(efunction efunction);
         edatatype get_data_type();
         void set_data_type(edatatype edatatype);
         void set_ddx_dbflags(::database::id idSection, ::database::id idKey, ::database::id idIndex, INT_PTR value);
      };

      class CLASS_DECL_ca descriptor_set :
         public array_ptr_alloc < descriptor >
      {
      public:
         control * get_control_by_id(id id);
         descriptor * get(::user::interaction * puie);
         descriptor * get_by_sub_item(int iSubItem);

         descriptor_set();
         virtual ~descriptor_set();
      };


      static const unsigned int  g_uiMessage;
      int                        m_iHover;
      e_element                  m_eelementHover;
      descriptor *               m_pdescriptor;
      ::user::window_interface * m_pwndiCustomWindowProc;
      bool                       m_bCustomWindowProc;
      int                        m_iEditItem;
      form *                     m_pform;
      form_callback *            m_pformcallback;
      bool                       m_bControlExCommandEnabled;


      control();
      virtual ~control();


      virtual void install_message_handling(::gen::message::dispatch * pdispatch);

      virtual bool create_control(class control::descriptor * pdescriptor);


      bool _003IsCustomMessage();
      ::user::window_interface * _003GetCustomMessageWnd();
      


      virtual int get_hover();

      class descriptor & descriptor();

      virtual void _003CallCustomDraw(::ca::graphics * pdc, ::user::draw_context * pitem);
      virtual bool _003CallCustomWindowProc(::user::window_interface * pwndi, UINT message, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
      virtual void _003OnCustomDraw(::ca::graphics * pdc, ::user::draw_context * pitem);
      virtual void _003CustomWindowProc(gen::signal_object * pobj);

      virtual form * get_form();
      virtual form_list * get_form_list();
      virtual bool _001IsPointInside(point64 pt);

      Ex1FormInterfaceComboBox * GetComboBox();
      static control Null();
      bool Validate(string & str);
      bool get_data(::user::interaction * pwnd, var & var);
      void SetEditItem(int iItem);
      void SetEditSubItem(int iItem);
      int GetEditSubItem();
      int GetEditItem();

      virtual ::user::interaction * ControlExGetWnd();
      
      using ::user::interaction::GetClientRect;
      using ::user::interaction::GetWindowRect;
      virtual void GetClientRect(LPRECT lprect);
      virtual void GetWindowRect(LPRECT lprect);


      bool operator == (const class user::control::descriptor & descriptor) const;
      bool operator == (const class control & control) const;


      virtual bool IsControlCommandEnabled();
      virtual void EnableControlCommand(bool bEnable);


      virtual void BaseControlExWndProcBefore(gen::signal_object * pobj);
      virtual void BaseControlExWndProcAfter(gen::signal_object * pobj);

      virtual void BaseControlExOnMouseMove(UINT nFlags, point point);

      virtual int hit_test(point point, e_element & eelement);

      DECL_GEN_SIGNAL(_001OnMouseMove)
      DECL_GEN_SIGNAL(_001OnMouseLeave)

   };


   class control_cmd_ui : public base_cmd_ui
   {
   public:

      control_cmd_ui(gen::signal * psignal);


      ::collection::map < id, id, id, id > m_mapControlCommand;
      virtual void Enable(BOOL bOn);
      virtual void SetCheck(int nCheck);
      virtual void SetText(const char * lpszText);
      id GetControlCommand(id id);
   };

   class control_view_impl
   {
   public:

      control_view_impl();

      virtual LRESULT BaseControlExOnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
      virtual void BaseControlExOnUpdateCmdUI(::frame_window * pTarget, BOOL bDisableIfNoHndler);
      virtual BOOL BaseControlExOnCommand(WPARAM wParam, LPARAM lParam) ;
      virtual ::user::interaction * GetWnd();

      control_cmd_ui  m_cmdui; // cmd_ui derived class used to update
                                    // base_controlex derived controls
      ::collection::list<HWND, HWND> m_listwndptrBlackList;
   };



} // namespace user