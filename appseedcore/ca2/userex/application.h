#pragma once

namespace userex
{

   class CLASS_DECL_ca application :
      public ::html::application
   {
   public:


      ::userbase::multiple_document_template * m_ptemplateForm;
      ::userbase::multiple_document_template * m_ptemplateChildForm;
      ::userbase::multiple_document_template * m_ptemplatePlaceHolder;


      application();
      virtual ~application();

      form_document *   create_form(::user::form_callback * pcallback, ::user::interaction * pwndParent);
      form_document *   create_form(form_view * pview, ::user::form_callback * pcallback, ::user::interaction * pwndParent);
      simple_document * hold(::user::interaction * pui);

      virtual bool initialize();

   };

   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace ca


