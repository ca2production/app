#pragma once


namespace primitive
{


   class CLASS_DECL_ca internal_shared_memory :
      virtual public ::primitive::base_memory
   {
   public:


      LPBYTE                                 m_pbStorage;
      UINT                                   m_nAllocFlags;
      HGLOBAL                                m_hGlobalMemory;
      BOOL                                   m_bAllowGrow;

   
      internal_shared_memory();
      virtual ~internal_shared_memory();


/*      void from_string(const wchar_t * pwsz);
      void from_string(const char * psz);
      void to_string(string & str);*/

      // shared primitive::memory interface
      virtual void SetHandle(HGLOBAL hGlobalMemory, BOOL bAllowGrow = TRUE);
      virtual BYTE* Alloc(SIZE_T nBytes);
      virtual BYTE* Realloc(BYTE* lpMem, SIZE_T nBytes);
      virtual void Free(BYTE* lpMem);



/*      void set_data(void * pdata, memory_size uiSize);
      void copy_from(const ::primitive::memory_base * pstorage);
      bool IsEnabled() const;
      bool IsLocked() const;


      void To(string & str, memory_position iStart = 0, memory_position iEnd = -1);
      void From(const char * psz);

      void ToAsc(string & str);
      void FromAsc(const char * psz);*/

      
      
      LPBYTE detach_shared_memory(HGLOBAL & hglobal);
      virtual bool allocate_internal(memory_size dwNewLength);

      HGLOBAL detach();

      LPBYTE internal_get_data() const;
      void free_data();


   };






   inline LPBYTE internal_shared_memory::internal_get_data() const
   {
      if(is_enabled())
         return m_pbStorage + m_iOffset;
      else
      {
         ASSERT(FALSE);
         return NULL;
      }
   }






   
   class CLASS_DECL_ca shared_memory :
      virtual public memory_base < internal_shared_memory >
   {
   public:


      shared_memory(const base_memory & memory);
      shared_memory(memory_container * pmsc = NULL, memory_size dwAllocationAddUp = 4096, UINT nAllocFlags = 0);
      shared_memory(memory_container * pmsc, void * pMemory, memory_size dwSize);
      virtual ~shared_memory();


/*      void from_string(const wchar_t * pwsz);
      void from_string(const char * psz);
      void to_string(string & str);*/

      // shared primitive::memory interface
      virtual void SetHandle(HGLOBAL hGlobalMemory, BOOL bAllowGrow = TRUE);
      virtual BYTE* Alloc(SIZE_T nBytes);
      virtual BYTE* Realloc(BYTE* lpMem, SIZE_T nBytes);
      virtual void Free(BYTE* lpMem);



      /*void set_data(void * pdata, memory_size uiSize);
      void copy_from(const ::primitive::memory_base * pstorage);*/
      /*bool IsEnabled() const;
      bool IsLocked() const;*/


      /*void To(string & str, memory_position iStart = 0, memory_position iEnd = -1);
      void From(const char * psz);

      void ToAsc(string & str);
      void FromAsc(const char * psz);*/

      
      
/*      LPBYTE DetachStorage();
      virtual bool allocate_internal(memory_size dwNewLength);

      HGLOBAL detach();

      LPBYTE internal_get_data() const;
      void free_data();*/

   };


} // namespace primitive


