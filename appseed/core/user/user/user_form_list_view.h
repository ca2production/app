#pragma once


namespace user
{


   class CLASS_DECL_CORE form_list_view:
      virtual public ::user::form_list,
      virtual public ::user::list_view,
      virtual public ::user::form_view
   {
   public:


      form_list_view();
      virtual ~form_list_view();


      virtual void install_message_handling(::message::dispatch *pinterface);

   };


} // namespace user




