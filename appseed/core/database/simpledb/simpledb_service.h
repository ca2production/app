#pragma once


namespace simpledb
{


   class socket_thread;


   class CLASS_DECL_CORE service :
      public plain_service
   {
   public:


      manager *            m_pmanager;
      ptr_array < socket_thread > m_threadptra;


      service(sp(::aura::application) papp);
      virtual ~service();


      virtual void serve();


   };



} // namespace simpledb



