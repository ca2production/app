#pragma once


class form_document;
class form_view;


class keyboard;
class front_end_schema;
class document_manager;
class document_template;
class document;


class CLASS_DECL_CORE base_user :
   virtual public ::base_departament,
   virtual public ::user::document_request_interface,
   virtual public BaseMenuCentralContainer,
   virtual public ::database::client
{
public:



   sp(::user::keyboard_focus)             m_pkeyboardfocus;
   ::user::mouse_focus *                  m_pmousefocusLButtonDown;
   ::user::mouse_focus *                  m_pmousefocusRButtonDown;
   sp(::user::window_map)                 m_pwindowmap;
   ::user::keyboard *                     m_pkeyboard;
   stringa                                m_straEscape;



   user(base_application * papp);
   virtual ~user();

   virtual bool set_keyboard_layout(const char * pszPath, bool bUser);

   virtual bool initialize1();
   virtual bool initialize2();
   virtual bool initialize();


   class window_map & window_map();


   virtual sp(::user::keyboard_focus) get_keyboard_focus();
   virtual void set_keyboard_focus(sp(::user::keyboard_focus) pkeyboardfocus);
   virtual ::user::mouse_focus * get_mouse_focus_LButtonDown();
   virtual void set_mouse_focus_LButtonDown(::user::mouse_focus * pmousefocus);
   virtual ::user::mouse_focus * get_mouse_focus_RButtonDown();
   virtual void set_mouse_focus_RButtonDown(::user::mouse_focus * pmousefocus);



   class keyboard & keyboard();


   virtual sp(type) controltype_to_typeinfo(::user::control::e_type type);


   virtual int32_t GetVisibleTopLevelFrameCountExcept(sp(::user::interaction) pwndExcept);


   virtual void SendMessageToWindows(UINT message, WPARAM wParam, LPARAM lParam);

   virtual void AddToRecentFileList(const char * lpszPathName);

   virtual bool finalize();

   virtual bool _001OnCmdMsg(base_cmd_msg * pcmdmsg);

   virtual void _001OnFileNew();

   virtual int32_t exit_instance();

   void LoadStdProfileSettings(UINT nMaxMRU = ___MRU_COUNT);



};






