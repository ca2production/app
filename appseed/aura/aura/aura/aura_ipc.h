#pragma once


#ifdef APPLEOS
typedef int key_t;
#elif defined(LINUX)
typedef __key_t key_t;
#elif defined(ANDROID)
#else
//#include "ca_mutex.h"
#endif


namespace aura
{


   namespace ipc
   {


      class CLASS_DECL_AURA base
      {
      public:


#ifdef WINDOWS
         oswindow        m_oswindow;
#else
         key_t   m_key;
         int      m_iQueue;

         struct data_struct
         {
            long     mtype;          /* Message type */
            int      request;        /* Work request number */
            int      size;
            char     data[512];
         } msg;
#endif

         
         string   m_strBaseChannel;


         base();
         virtual ~base();


      };




      class CLASS_DECL_AURA tx:
         virtual public  base
      {
      public:


         bool open(const char * pszChannel,launcher * plauncher = NULL);
         bool close();


         bool send(const char * pszMessage,unsigned int dwTimeout);
         bool send(int message,void * pdata,int len,unsigned int dwTimeout);


         bool is_tx_ok();

      };




      class CLASS_DECL_AURA rx:
         virtual public base
      {
      public:

         class CLASS_DECL_AURA receiver
         {
         public:

            virtual void on_receive(rx * prx,const char * pszMessage);
            virtual void on_receive(rx * prx,int message,void * pdata,int len);
            virtual void on_post(rx * prx,long long int a,long long int b);

         };

         receiver *        m_preceiver;

#ifdef WINDOWS
         string          m_strWindowProcModule;
#else
         bool              m_bRunning;
         bool              m_bRun;
         void *            m_pthread;
#endif


         rx();
         virtual ~rx();


#ifdef WINDOWS
         bool create(const char * pszChannel,const char * pszWindowProcModule);
#else
         bool create(const char * pszChannel);
#endif
         bool destroy();


         virtual void * on_receive(rx * prx,const char * pszMessage);
         virtual void * on_receive(rx * prx,int message,void * pdata,int len);
         virtual void * on_post(rx * prx,long long int a,long long int b);


         virtual bool on_idle();

#ifdef WINDOWS
         ATOM register_class(HINSTANCE hInstance);
         static LRESULT CALLBACK s_message_queue_proc(oswindow oswindow,UINT message,WPARAM wParam,LPARAM lParam);
         LRESULT message_queue_proc(UINT message,WPARAM wParam,LPARAM lParam);
#else
         bool start_receiving();
#ifndef SOLARIS
         static void * receive_proc(void * param);
#endif
         void * receive();
#endif

         bool is_rx_ok();

      };




      class CLASS_DECL_AURA ipc:
         virtual public tx,
         virtual public rx::receiver
      {
      public:


         rx                      m_rx;
         string                  m_strChannel;
         unsigned int            m_dwTimeout;


         ipc();

#ifdef WINDOWS
         bool open_ab(const char * pszChannel,const char * pszModule,launcher * plauncher = NULL);
         bool open_ba(const char * pszChannel,const char * pszModule,launcher * plauncher = NULL);
#else
         bool open_ab(const char * pszChannel, launcher * plauncher = NULL);
         bool open_ba(const char * pszChannel, launcher * plauncher = NULL);
#endif
         bool close();

         virtual void restart_aura_ipc();

         bool ensure_tx(const char * pszMessage,unsigned int dwTimeout = INFINITE);
         bool ensure_tx(int message,void * pdata,int len,unsigned int dwTimeout = INFINITE);


         bool is_rx_tx_ok();


      };






      CLASS_DECL_AURA string app_install(string strPlatform = "");


   } // namespace ipc


} // namespace aura



