#pragma once

namespace mail
{

   class CLASS_DECL_ca configuration :
      public ::user::form_callback,
      public ::user::create_view
   {
   public:
      form_document *               m_pdoc;
      form_view *                   m_pview;
      string                        m_strEmail;

      configuration(::ca::application * papp);
      virtual ~configuration();

      bool initialize(::user::interaction * puiParent);

      void on_show(const char * pszEmail);

      bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);
   };


} // namespace ca8