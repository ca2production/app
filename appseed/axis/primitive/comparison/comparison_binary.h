#pragma once


namespace comparison
{


   template < typename TYPE, typename ARG_TYPE = const TYPE & >
   class binary
   {
   public:


      int operator ()(ARG_TYPE a, ARG_TYPE b)
      {
         if(a < b)
            return -1;
         else if(b < a)
            return 1;
         else
            return 0;
      }


   };

   template < >
   class CLASS_DECL_AXIS binary < int32_t >
   {
   public:


      inline static int_ptr CompareElements(const int32_t * pElement1, const int32_t * pElement2)
      {
         return *pElement1 - *pElement2;
      }


   };

   class CLASS_DECL_AXIS strid_binary
   {
   public:


      inline static int_ptr CompareElements(const id * pElement1, const id * pElement2)
      {
         return pElement1->m_pstr - pElement2->m_pstr;
      }


   };


} // namespace comparison


