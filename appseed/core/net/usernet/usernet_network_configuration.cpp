//#include "framework.h"
//#include "core/user/user/user.h"
//#include "core/filesystem/filemanager/filemanager.h"
//#include "usernet_network_configuration.h"

// Included in _user.cpp

namespace usernet // ca8 + cube
{


   network_configuration::network_configuration(::aura::application * papp) :
      object(papp)
   {
      m_pdoc   = NULL;
      m_pview  = NULL;
   }

   network_configuration::~network_configuration()
   {
   }

   bool network_configuration::initialize(sp(::user::interaction) puiParent)
   {
      m_pdoc = Platform.userex()->create_form(this, puiParent);
      if(m_pdoc != NULL)
      {
         m_pview = m_pdoc->get_typed_view < ::user::form > ();
         m_pview->m_pcallback = this;
         return true;
      }
      return false;
   }

   bool network_configuration::initialize_child(sp(::user::interaction) puiParent)
   {
      m_pdoc = Platform.userex()->create_child_form(this, puiParent);
      if(m_pdoc != NULL)
      {
         m_pview = m_pdoc->get_typed_view < ::user::form > ();
         m_pview->m_pcallback = this;
         return true;
      }
      return false;
   }

   void network_configuration::on_show()
   {
      if(!m_pdoc->on_open_document(Application.dir().matter("system/network/configuration/proxy.xhtml")))
      {
         return;
      }

      xml::document doc;

      if(doc.load(Session.file_as_string(System.dir().appdata("proxy.xml"))))
      {
         string strProxy = doc.root().attr("server");
         int32_t iProxyPort = doc.root().attr("port");
         sp(::user::interaction) pui = m_pview->get_child_by_name("server");
         sp(::user::elemental) ptext =  (pui.m_p);
         ptext->_001SetText(strProxy, ::action::source::add(::action::source_data, ::action::source_load));
         pui = m_pview->get_child_by_name("port");
         ptext =  (pui.m_p);
         ptext->_001SetText(::str::from(iProxyPort), ::action::source::add(::action::source_data, ::action::source_load));
      }

   }

  bool network_configuration::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
  {
      UNREFERENCED_PARAMETER(pview);
      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie->m_id == "submit")
         {
            sp(::user::interaction) pui = m_pview->get_child_by_name("server");
            sp(::user::elemental) ptext =  (pui.m_p);
            //m_loginthread.m_puser = dynamic_cast < ::fontopus::user * > (System.allocate_user());
            string strServer;
            ptext->_001GetText(strServer);
            if(strServer.get_length() == 0)
            {
               System.file().del(System.dir().appdata("proxy.xml"));
            }
            else
            {
               xml::document doc;
               doc.root().set_name("proxy");
               doc.root().add_attr("server", strServer);
               pui = m_pview->get_child_by_name("port");
               ptext =  (pui.m_p);
               string strPort;
               ptext->_001GetText(strPort);
               doc.root().add_attr("port", strPort);
               Application.file().put_contents(System.dir().appdata("proxy.xml"), doc.get_xml());
            }
         }
      }

      return false;

   }


} // namespace usernet // ca8 + cube


