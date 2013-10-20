#pragma once


namespace user
{


   class CLASS_DECL_CORE list_cache  :
      public list_cache_interface
   {
   protected:

      
      bool                                                              m_bCaching;
      int32_t                                                               m_iCacheNextIndex;
      string2a                                                          m_cacheArray;
      map < int_ptr, int_ptr, stringa *, stringa *>       m_cacheMap;


   public:


      list_cache();
      virtual ~list_cache();


      void _001Invalidate();
      
      virtual void _001CacheHint(list * plist, int_ptr iItemStart, int_ptr iItemCount);

      virtual void _001GetItemText(::user::list_item * pitem);


   };


} // namespace user

