#pragma once


class CLASS_DECL_ca simple_thread :
   virtual public ::radix::thread
{
public:
   simple_thread(::ca::application * papp);
   virtual ~simple_thread();
   virtual bool initialize_instance();
   UINT m_dwFinishTimeout;
};
