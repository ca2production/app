#include "framework.h"


namespace primitive
{


   memory_container ::memory_container(::ca::application * papp) :
      ca(papp)
   {
      m_dwAllocationAddUp = 1024;
   }


   memory_container ::memory_container(::ca::application * papp, void * pmemory, memory_size dwSize) :
      ca(papp)
   {
      m_spmemory(new primitive::memory(this, pmemory, dwSize));
   }


   memory_container ::memory_container(::ca::application * papp, memory_base * pmemory) :
      ca(papp)
   {
      m_spmemory = pmemory;
   }


   memory_container ::memory_container(const memory_container & container) :
      ::radix::object(container)
   {
      operator = (container);
   }


   memory_container ::   ~memory_container()
   {
   }


   void memory_container ::allocate_add_up(memory_size dwAddUp)
   {
      allocate(this->get_size() + dwAddUp);
   }


   void memory_container::allocate(memory_size dwNewLength)
   {

      if(dwNewLength <= 0)
      {
         
         if(m_spmemory.is_set())
         {
            
            if(!m_spmemory->allocate(dwNewLength))
            {

               throw memory_exception();

            }

         }

         return;
      }

      if(m_spmemory == NULL)
      {
         
         m_spmemory(new primitive::memory(this));

         if(m_spmemory.is_null())
         {
         
            throw memory_exception();

         }

         m_spmemory->m_dwAllocationAddUp = m_dwAllocationAddUp;

      }

      if(!m_spmemory->allocate(dwNewLength))
      {

         throw memory_exception();

      }

   }


   void memory_container ::allocate_internal(memory_size dwNewLength)
   {
      if(m_spmemory == NULL)
      {
         m_spmemory(new primitive::memory(this));
         if(m_spmemory.is_null())
         {
            throw new memory_exception;
         }
         m_spmemory->m_dwAllocationAddUp = m_dwAllocationAddUp;
      }
      m_spmemory->allocate_internal(dwNewLength);
   }


   memory_base * memory_container::get_memory() const
   {

      if(m_spmemory.is_null())
      {
         (const_cast < memory_container * > (this))->m_spmemory((const_cast < memory_container * > (this))->create_memory());
      }

      return m_spmemory;

   }

   ::primitive::memory_base * memory_container::create_memory()
   {

      return new primitive::memory(this);

   }




   void memory_container ::FullLoad(memory_base * pmemory)
   {
      if(m_spmemory.is_null())
      {
         m_spmemory(new primitive::memory(this));
      }
      m_spmemory->copy_from(pmemory);
   }


   void memory_container ::FullLoad(ex1::file & file)
   {
      if(m_spmemory.is_null())
      {
         m_spmemory(new primitive::memory(this));
      }
      m_spmemory->FullLoad(file);
   }


   void memory_container ::keep_pointer(void **ppvoid)
   {
         m_vppa.add(ppvoid);
   }


   void memory_container ::offset_kept_pointers(memory_offset iOffset)
   {
      for(int i = 0; i < m_vppa.get_size(); i++)
      {
         *m_vppa.element_at(i) = ((LPBYTE) *m_vppa.element_at(i)) + iOffset;
      }
   }

   bool memory_container ::IsValid() const
   {
      return true;
   }


   memory_container & memory_container ::operator =(const memory_container &container)
   {
      if(container.m_spmemory.is_null())
         m_spmemory.destroy();
      else
      {
         m_spmemory(new primitive::memory(this));
         m_spmemory->copy_from(container.m_spmemory);
      }
      m_vppa.remove_all();
      return *this;
   }


   bool memory_container ::Attach(memory_base * pstorage)
   {

      m_spmemory(pstorage);

      return true;

   }


   memory_base * memory_container::detach()
   {

      return m_spmemory.detach();

   }


   memory *          memory_container::get_primitive_memory()
   {
      return dynamic_cast < ::primitive::memory * > (m_spmemory.m_p);
   }

   shared_memory *   memory_container::get_shared_memory()
   {
      return dynamic_cast < ::primitive::shared_memory * > (m_spmemory.m_p);
   }

   virtual_memory *  memory_container::get_virtual_memory()
   {
      return dynamic_cast < ::primitive::virtual_memory * > (m_spmemory.m_p);
   }


   memory *          memory_container::detach_primitive_memory()
   {
      ::primitive::memory_base * pmemorybase = m_spmemory.detach();
      if(pmemorybase != NULL)
         return NULL;
      ::primitive::memory * pmemory = dynamic_cast < ::primitive::memory * > (pmemorybase);
      if(pmemory != NULL)
      {
         return pmemory;
      }
      pmemory = new ::primitive::memory(*pmemorybase);
      delete pmemorybase;
      return pmemory;
   }

   shared_memory *   memory_container::detach_shared_memory()
   {
      ::primitive::memory_base * pmemorybase = m_spmemory.detach();
      if(pmemorybase != NULL)
         return NULL;
      ::primitive::shared_memory * psharedmemory = dynamic_cast < ::primitive::shared_memory * > (pmemorybase);
      if(psharedmemory != NULL)
      {
         return psharedmemory;
      }
      psharedmemory = new ::primitive::shared_memory(*pmemorybase);
      delete pmemorybase;
      return psharedmemory;
   }

   virtual_memory *  memory_container::detach_virtual_memory()
   {
      ::primitive::memory_base * pmemorybase = m_spmemory.detach();
      if(pmemorybase != NULL)
         return NULL;
      ::primitive::virtual_memory * pvirtualmemory = dynamic_cast < ::primitive::virtual_memory * > (pmemorybase);
      if(pvirtualmemory != NULL)
      {
         return pvirtualmemory;
      }
      pvirtualmemory = new ::primitive::virtual_memory(*pmemorybase);
      delete pmemorybase;
      return pvirtualmemory;
   }


   LPBYTE            memory_container::detach_primitive_storage()
   {
      ::primitive::memory * pmemory = detach_primitive_memory();
      LPBYTE p = pmemory->detach();
      delete pmemory;
      return p;
   }

   HGLOBAL           memory_container::detach_shared_storage()
   {
      ::primitive::shared_memory * psharedmemory = detach_shared_memory();
      HGLOBAL h = psharedmemory->detach();
      delete psharedmemory;
      return h;
   }

   LPBYTE            memory_container::detach_virtual_storage()
   {
      ::primitive::virtual_memory * pvirtualmemory = detach_virtual_memory();
      LPBYTE p = pvirtualmemory->detach();
      delete pvirtualmemory;
      return p;
   }

   void memory_container::str(const string & str)
   {
      
      allocate(str.get_length());

      memcpy(get_data(), str, get_size());

   }



} // namespace primitive



