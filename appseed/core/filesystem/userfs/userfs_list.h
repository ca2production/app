#pragma once


namespace userfs
{

   class main_view;

   class CLASS_DECL_CORE list :
      virtual public list_interface
   {
   public:


      simple_list_header_control    m_headerctrl;


      list(sp(base_application) papp);
      virtual ~list();


      void _001OnClick(UINT uiFlags, point point);

      virtual void install_message_handling(::message::dispatch * pdispatch);
      
      virtual void on_update(sp(::user::view) pSender, LPARAM lHint, object* pHint);
      virtual bool pre_create_window(CREATESTRUCT& cs);

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnLButtonDblClk)
      DECL_GEN_SIGNAL(_001OnCancelMode)

#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

   };


} // namespace userfs

