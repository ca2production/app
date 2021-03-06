#include "framework.h"


namespace html_lite
{


   application::application()
   {

      m_pauraapp->m_psignal->connect(this,&application::on_application_signal);

   }


   application::~application()
   {


   }


   void application::on_application_signal(signal_details * pobj)
   {

      SCAST_PTR(::aura::application_signal_details,psignal,pobj);

      if(psignal->m_esignal == ::aura::application_signal_process_initialize)
      {

         if (m_pauraapp->m_paurasystem->m_phtml == NULL)
         {

            m_pauraapp->m_paurasystem->m_phtml = create_html();

            if (m_pauraapp->m_paurasystem->m_phtml == NULL)
            {

               psignal->m_bOk = false;

               psignal->m_bRet = true;

               return;

            }

            m_pauraapp->m_paurasystem->m_phtml->construct(m_pauraapp);

         }

      }
      else if (psignal->m_esignal == ::aura::application_signal_process_initialize)
      {


      }
      else if(psignal->m_esignal == ::aura::application_signal_initialize1)
      {


         if(!m_pauraapp->m_paurasystem->m_phtml->initialize())
         {

            psignal->m_bOk    = false;

            psignal->m_bRet   = true;

            return;

         }

      }
      else  if(psignal->m_esignal == ::aura::application_signal_exit_instance)
      {
         
         if (m_pauraapp->m_paurasystem->m_phtml != NULL)
         {

            delete m_pauraapp->m_paurasystem->m_phtml;

            m_pauraapp->m_paurasystem->m_phtml = NULL;

         }

      }

   }


   ::html::html * application::create_html()
   {

      return new ::html::html(m_pauraapp);

   }


} // namespace html_lite














