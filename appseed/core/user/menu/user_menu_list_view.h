#pragma once


namespace user
{


   class CLASS_DECL_CORE menu_list_view : 
      virtual public ::user::show < ::user::menu_list_window >
   {
   public:


      typedef ::user::show <  ::user::menu_list_window  > BASE;


      menu_list_view(::aura::application * papp);
      virtual ~menu_list_view();

      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual bool pre_create_window(::user::create_struct & cs);

      virtual void GuieProc(signal_details * pobj);

      virtual bool _001OnCmdMsg(::aura::cmd_msg * pcmdmsg);

      bool LoadMenu(sp(::xml::node) pnode, sp(::user::interaction) puiNotify, UINT uiCallbackMessage);
         
   #ifdef DEBUG
      virtual void assert_valid() const;
   #ifndef _WIN32_WCE
      virtual void dump(dump_context & dumpcontext) const;
   #endif
   #endif

      virtual void PostNcDestroy();

   };

} // namespace user
