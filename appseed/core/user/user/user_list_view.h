#pragma once


namespace user
{


   class CLASS_DECL_CORE list_view:
      virtual public scroll_view,
      virtual public list
   {
   public:


      list_view(::aura::application * papp);
      virtual ~list_view();


      virtual void install_message_handling(::message::dispatch * pdispatch);

      //virtual void _001OnInitialUpdate(signal_details * pobj);


   };



} // namespace user



