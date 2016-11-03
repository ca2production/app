#pragma once


namespace file_watcher
{


   class CLASS_DECL_AURA listener_thread :
      virtual public ::thread,
      virtual public file_watcher,
      virtual public file_watch_listener
   {
   public:


      struct op :
         virtual public object
      {

         string                  m_str;
         bool                    m_bRecursive;
         file_watch_listener *   m_plistener;
         event                   m_event;
         id                      m_id;
         bool                    m_bOwn;

         op() : m_event(get_thread_app(), false, true) {}

      };


      listener_thread(::aura::application * papp);


      virtual int32_t run();



      id add_file_watch(const char * directory, bool bRecursive);

      id add_file_watch(const char * directory, file_watch_listener * plistener, bool bRecursive, bool bOwn = false);

      template < typename PRED >
      id pred_add_watch(const char * directory, PRED pred, bool bRecursive)
      {

         return add_file_watch(directory, new pred_file_watch_listener < PRED >(pred), bRecursive, true);

      }

      virtual void install_message_handling(::message::dispatch * pdispatch) override;

      DECL_GEN_SIGNAL(_001OnUser123);

   };


} // namespace file_watcher



