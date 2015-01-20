#include "framework.h"

struct send_thread_message : public MESSAGE
{

   bool     m_bOk;


};



bool thread::s_bAllocReady = false;


thread::thread()
{

   CommonConstruct();

   m_puiptra = NULL;

}




thread::thread(::aura::application * papp) :
element(papp)
{

   CommonConstruct();

   if (papp == NULL)
      return;
   set_app(papp);
   if (!s_bAllocReady)
      return;
   m_pthreadimpl.alloc(allocer());
   m_pthreadimpl->m_pthread = this;
   m_pthreadimpl->construct();

   if(m_pauraapp != NULL && m_pauraapp->m_paurasession != NULL)
   {

      m_bZipIsDir = m_pauraapp->m_paurasession->m_bZipIsDir;

   }

}


thread::thread(::aura::application * papp, __THREADPROC pfnThreadProc, LPVOID pParam) :
element(papp)
{

   CommonConstruct();

   m_pthreadimpl.alloc(allocer());
   m_pthreadimpl->m_pthread = this;
   m_pthreadimpl->construct(pfnThreadProc, pParam);

   if(m_pauraapp != NULL && m_pauraapp->m_paurasession != NULL)
   {

      m_bZipIsDir = m_pauraapp->m_paurasession->m_bZipIsDir;

   }

}


void thread::CommonConstruct()
{

   m_durationRunLock = ::duration::infinite();

   m_dwAlive = ::get_tick_count();

   m_pmutex = new mutex();

   m_peventEvent = NULL;

   m_bReady = false;
   m_bRun = true;
   m_pbReady = NULL;

   m_puiActive = NULL;
   m_puiMain = NULL;

   m_iReturnCode = 0;

   m_bZipIsDir = true;

   m_pslUser = NULL;

   m_preplacethread = NULL;

   m_bAutoDelete = true;


}



thread::~thread()
{

   if(m_pmutex != NULL)
      delete m_pmutex;

   if(m_peventEvent == NULL)
      delete m_peventEvent;

}








void * thread::get_os_data() const
{
   return m_pthreadimpl == NULL ? NULL : m_pthreadimpl->get_os_data();
}


int_ptr thread::get_os_int() const
{

   return m_pthreadimpl == NULL ? -1 : m_pthreadimpl->get_os_int();

}


HTHREAD thread::get_os_handle() const
{

   return (HTHREAD)get_os_data();

}



void thread::_001OnSendThreadMessage(signal_details * pobj)
{

   SCAST_PTR(::message::base,pbase,pobj);

   ::send_thread_message * pmessage = (::send_thread_message *) pbase->m_lparam;

   process_message(pmessage);

   pmessage->m_bOk = true;

}


void thread::start()
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->start();

}


bool thread::verb()
{

   return true;

}


bool thread::begin(int32_t epriority, uint_ptr nStackSize, uint32_t dwCreateFlags, LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   if (m_pthreadimpl.is_null())
      return false;

   m_pthreadimpl->m_pthread = this;

   return m_pthreadimpl->begin(epriority,nStackSize,dwCreateFlags,lpSecurityAttrs);

}


bool thread::create_thread(int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   if (m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->create_thread(epriority,nStackSize,dwCreateFlags,lpSecurityAttrs);

}


bool thread::begin_synch(int32_t * piStartupError, int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   if(m_pthreadimpl.is_null())
      return false;

   m_pthreadimpl->m_pthread = this;

   return m_pthreadimpl->begin_synch(piStartupError, epriority,nStackSize,dwCreateFlags,lpSecurityAttrs);

}


bool thread::create_thread_synch(int32_t * piStartupError,int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->create_thread_synch(piStartupError,epriority,nStackSize,dwCreateFlags,lpSecurityAttrs);

}


bool thread::finalize()
{

   signal_close_dependent_threads();

   unregister_from_required_threads();

   wait_close_dependent_threads(minutes(1));

   if(m_pthreadimpl == NULL)
      return true;

   m_pthreadimpl->finalize();

   return true;

}


int32_t thread::exit()
{

   try
   {

      if (!finalize())
      {

         TRACE("There occurred errors durring application::finalize virtual member function");

      }

   }
   catch (...)
   {

   }

   return exit_instance();

}



int32_t thread::get_thread_priority()
{

   if(m_pthreadimpl.is_null())
      return -1;

   return m_pthreadimpl->get_thread_priority();

}


bool thread::set_thread_priority(int32_t epriority)
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->set_thread_priority(epriority);

}


uint32_t thread::ResumeThread()
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->ResumeThread();

}


bool thread::post_thread_message(UINT message, WPARAM wParam, lparam lParam)
{

   if (m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->post_thread_message(message, wParam, lParam);

}

bool thread::send_thread_message(UINT message,WPARAM wParam,lparam lParam, ::duration durWaitStep)
{

   ::send_thread_message * pmessage =  new ::send_thread_message;

   ZEROP(pmessage);

   pmessage->message = message;
   pmessage->wParam = wParam;
   pmessage->lParam = lParam;
   pmessage->m_bOk = false;

   post_thread_message(WM_APP + 3241,0, pmessage);

   while(defer_pump_message())
   {

      if(pmessage->m_bOk)
      {

         break;

      }

      Sleep(durWaitStep.get_total_milliseconds());

      if(pmessage->m_bOk)
      {

         break;

      }

   }

   delete pmessage;

   return true;

}


void thread::set_os_data(void * pvoidOsData)
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->set_os_data(pvoidOsData);

}


void thread::set_os_int(int_ptr iData)
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->set_os_int(iData);

}


void thread::on_keep_alive()
{

   m_dwAlive = ::get_tick_count();

}


bool thread::is_alive()
{

   if(m_pthreadimpl.is_null())
      return false;

   if (!m_bRun)
      return false;

   //if ((::get_tick_count() - m_dwAlive) > ((5000) * 91))
     // return false;

   return true;

}

bool thread::has_message()
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->has_message();


}


bool thread::is_auto_delete()
{

   return m_bAutoDelete;

}


wait_result thread::wait(const duration & duration)
{

   if(m_pthreadimpl.is_null())
      return wait_result();

   return m_pthreadimpl->wait(duration);

}


void thread::set_priority(int32_t priority)
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->set_priority(priority);

}

int32_t thread::priority()
{

   if(m_pthreadimpl.is_null())
      return 0x80000000;

   return m_pthreadimpl->priority();

}



CLASS_DECL_AURA void thread_alloc_ready(bool bReady)
{

   thread::s_bAllocReady = bReady;

}


void thread::process_message_filter(int32_t code, signal_details * pobj)
{

   if(m_pthreadimpl.is_null())
      return;

   return  m_pthreadimpl->process_message_filter(code, pobj);

}


bool thread::post_message(::aura::interaction * pui, UINT message, WPARAM wParam, lparam lParam)
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->post_message(pui, message, wParam, lParam);

}

bool thread::pre_init_instance()
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->pre_init_instance();

}

bool thread::on_run_exception(::exception::exception & e)
{

   try
   {

      if (m_pthreadimpl.is_null())
         return false;

      return m_pthreadimpl->on_run_exception(e);

   }
   catch (::exception::standard_access_violation &)
   {

      return false;

   }
   catch (::exception::exception & e)
   {

      throw e;

   }
   catch (...)
   {

      return false;

   }

}

bool thread::initialize_instance()
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->initialize_instance();

}


message::e_prototype thread::GetMessagePrototype(UINT uiMessage, UINT uiCode)
{

   if(m_pthreadimpl.is_null())
      return ::message::PrototypeNone;

   return m_pthreadimpl->GetMessagePrototype(uiMessage, uiCode);

}

bool thread::pre_run()
{

   register_at_required_threads();

   return true;

}

int32_t thread::run()
{

   if(m_pthreadimpl.is_null())
      return -1;

   return m_pthreadimpl->run();

}


void thread::pre_translate_message(signal_details * pobj)
{

   if (m_pthreadimpl.is_null())
      return;

   return m_pthreadimpl->pre_translate_message(pobj);

}


bool thread::pump_message()
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->pump_message();

}

bool thread::defer_pump_message()
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->defer_pump_message();

}

bool thread::process_message(LPMESSAGE lpmsg)
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->process_message(lpmsg);

}

bool thread::on_idle(LONG lCount)
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->on_idle(lCount);

}


bool thread::is_idle_message(signal_details * pobj)
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->is_idle_message(pobj);

}


bool thread::is_idle_message(LPMESSAGE lpmsg)
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->is_idle_message(lpmsg);

}


int32_t thread::exit_instance()
{

   if (m_pthreadimpl.is_null())
      return 0;

   return m_pthreadimpl->exit_instance();

}


void thread::process_window_procedure_exception(::exception::base* e, signal_details * pobj)
{

   if(m_pthreadimpl.is_null())
      return;

   return m_pthreadimpl->process_window_procedure_exception(e,pobj);

}



void thread::add(::aura::interaction * pui)
{

   if (m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->add(pui);

}


void thread::remove(::aura::interaction * pui)
{

   if (m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->remove(pui);

}


::count thread::get_ui_count()
{

   if (m_pthreadimpl.is_null())
      return 0;

   return m_pthreadimpl->get_ui_count();

}


::aura::interaction * thread::get_ui(index iIndex)
{

   if (m_pthreadimpl.is_null())
      return NULL;

   return m_pthreadimpl->get_ui(iIndex);

}


void thread::set_timer(::aura::interaction * pui, uint_ptr nIDEvent, UINT nEllapse)
{

   if (m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->set_timer(pui, nIDEvent, nEllapse);

}


void thread::unset_timer(::aura::interaction * pui, uint_ptr nIDEvent)
{

   if (m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->unset_timer(pui, nIDEvent);

}


void thread::set_auto_delete(bool bAutoDelete)
{

   m_bAutoDelete = bAutoDelete;

}


void thread::set_run(bool bRun)
{

   m_bRun = bRun;

}


event & thread::get_finish_event()
{

   if (m_pthreadimpl.is_null())
      return *((event *)NULL);

   return m_pthreadimpl->get_finish_event();

}


bool thread::get_run()
{

   return m_bRun;

}




::aura::interaction * thread::get_active_ui()
{

   return m_puiActive;

}


::aura::interaction * thread::set_active_ui(::aura::interaction * pui)
{

   return m_puiActive = pui;

}


void thread::step_timer()
{

   if (m_pthreadimpl.is_null())
      return;

   return m_pthreadimpl->step_timer();

}


bool thread::on_run_step()
{

   if (m_pthreadimpl.is_null())
      return false;


   step_timer();

   sp(::aura::application) papp = (this);

   m_dwAlive = ::get_tick_count();

   if (papp != NULL)
   {

      papp->m_dwAlive = m_dwAlive;

   }

   sp(::aura::application) pappP = (this);

   if (pappP != NULL)
   {

      pappP->m_dwAlive = m_dwAlive;

   }

   try
   {

      if (!verb())
         return false;

   }
   catch (::exit_exception & e)
   {

      throw e;

   }
   catch (::exception::exception & e)
   {

      if (!Application.on_run_exception(e))
         throw exit_exception(get_app());

   }
   catch (...)
   {

   }

   return true;

}


int32_t thread::main()
{

   return m_pthreadimpl->main();

}



void thread::assert_valid() const
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->assert_valid();

}


void thread::dump(dump_context & dumpcontext) const
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->dump(dumpcontext);

}


void thread::Delete()
{


   release();

}


void thread::dispatch_thread_message(signal_details * pobj)  // helper
{
   m_pthreadimpl->dispatch_thread_message(pobj);

}

void thread::wait()
{

   if(m_pthreadimpl.is_null())
      return;

   return m_pthreadimpl->wait();

}


int_ptr thread::item() const
{

   if(m_pthreadimpl.is_null())
      return -1;

   return m_pthreadimpl->item();

}


int thread::get_x_window_count() const
{

   if (m_pthreadimpl.is_null())
      return 0;

   return m_pthreadimpl->get_x_window_count();

}




void thread::post_to_all_threads(UINT message,WPARAM wparam,LPARAM lparam)
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->post_to_all_threads(message,wparam,lparam);

}


void thread::register_dependent_thread(::thread * pthreadDependent)
{

   if(pthreadDependent == this)
      return;

   {

      synch_lock sl(m_pmutex);

      m_threadptraDependent.add_unique(pthreadDependent);

   }

   {

      synch_lock slThread(pthreadDependent->m_pmutex);

      pthreadDependent->m_threadptraRequired.add_unique(this);

   }

}


void thread::unregister_dependent_thread(::thread * pthreadDependent)
{

   {

      synch_lock sl(m_pmutex);

      m_threadptraDependent.remove(pthreadDependent);

   }

   {

      synch_lock slThread(pthreadDependent->m_pmutex);

      pthreadDependent->m_threadptraRequired.remove(this);

   }

}


void thread::signal_close_dependent_threads()
{

   synch_lock sl(m_pmutex);

   for(index i = m_threadptraDependent.get_upper_bound(); i >= 0;)
   {

      try
      {

         synch_lock slThread(m_threadptraDependent[i]->m_pmutex);

         m_threadptraDependent[i]->set_end_thread();

         i--;

      }
      catch(...)
      {

         m_threadptraDependent.remove_at(i);

      }

      sl.unlock();

      sl.lock();


   }

}


void thread::wait_close_dependent_threads(const duration & duration)
{

   DWORD dwStart = ::get_tick_count();

   while(::get_tick_count() - dwStart < duration.get_total_milliseconds())
   {

      {

         synch_lock sl(m_pmutex);

         if(m_threadptraDependent.get_count() <= 0)
            break;

         for(index i = 0; i < m_threadptraDependent.get_count(); i++)
         {
            TRACE(string("---"));
            TRACE(string("supporter : ") + typeid(*this).name() + string(" (") + ::str::from(this) + ")");
            TRACE(string("dependent : ") + typeid(*m_threadptraDependent[i]).name() + string(" (") + ::str::from(m_threadptraDependent[i]) + ")");

         }

      }

      Sleep(11);

   }

}

void thread::register_at_required_threads()
{

   // register default dependencies

   sp(::aura::application) papp = this;

   sp(::aura::session) psession = this;

   sp(::aura::system) psystem = this;

   if(&Application != NULL)
   {

      Application.register_dependent_thread(this);

      if(psystem == NULL && &Session != NULL)
      {

         Session.register_dependent_thread(this);

         if(Session.m_pplatformcomposite != NULL)
         {

            Session.m_pplatformcomposite->register_dependent_thread(this);

         }

      }

      if(&System != NULL)
      {

         System.register_dependent_thread(this);

      }

   }

}



void thread::unregister_from_required_threads()
{

   synch_lock sl(m_pmutex);

   for(index i = m_threadptraRequired.get_upper_bound(); i >= 0;)
   {

      try
      {

         synch_lock slThread(m_threadptraRequired[i]->m_pmutex);

         m_threadptraRequired[i]->unregister_dependent_thread(this);

      }
      catch(...)
      {

      }

      i--;

      sl.unlock();

      sl.lock();

   }

}


void thread::do_events()
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->do_events();

}


void thread::do_events(const duration & duration)
{

   DWORD dwEnd = (DWORD) (::get_tick_count() + duration.get_total_milliseconds());

   do
   {

      do_events();

   } while(::get_tick_count() < dwEnd);

}


void thread::set_run_thread(bool bRun)
{

   if(bRun)
   {

      m_bRun = true;

   }
   else
   {

      m_durationRunLock = millis(7);

      if(m_peventEvent != NULL)
      {

         m_peventEvent->SetEvent();

      }

      m_bRun = false;


   }

}

void thread::set_end_thread()
{

   set_run_thread(false);

}


void thread::defer_add_thread_run_wait(sync_object_ptra & soa)
{

    UNREFERENCED_PARAMETER(soa);

}


void thread::message_queue_message_handler(::signal_details * pobj)
{

    UNREFERENCED_PARAMETER(pobj);

}
