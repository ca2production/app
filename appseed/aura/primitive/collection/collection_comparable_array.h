#pragma once



template < class TYPE,class ARG_TYPE = TYPE const &,class ARRAY_TYPE = comparable_eq_array < TYPE,ARG_TYPE > >
class comparable_array :
   virtual public ARRAY_TYPE
{
public:

   comparable_array();
   comparable_array(const comparable_array & array);
   comparable_array(comparable_array && array);

   void quick_sort(bool bAsc = true);


   comparable_array & operator = (const comparable_array & array);
   comparable_array & operator = (comparable_array && array);


};



template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
comparable_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
comparable_array()
{

}


template < class TYPE,class ARG_TYPE,class ARRAY_TYPE>
comparable_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
comparable_array(const comparable_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE> & a)
{

   this->operator = (a);

}

template < class TYPE,class ARG_TYPE,class ARRAY_TYPE>
comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE>::
comparable_array(comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE> && a)
{

   this->operator = (a);

}


template < class TYPE,class ARG_TYPE,class ARRAY_TYPE>
comparable_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE> & comparable_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
operator = (const comparable_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE> & a)
{

   this->ARRAY_TYPE::operator = (a);
   return *this;

}

template < class TYPE,class ARG_TYPE,class ARRAY_TYPE>
comparable_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE> & comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE>::
operator = (comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE> && a)
{

   this->ARRAY_TYPE::operator = (a);
   return *this;

}


template < class TYPE,class ARG_TYPE = TYPE const &,class ARRAY_TYPE = comparable_array < TYPE,ARG_TYPE >,class COMPARE = ::comparison::compare_type_arg_type < TYPE,ARG_TYPE >  >
class full_comparable_array:
   virtual public ARRAY_TYPE
{
public:
   full_comparable_array();
   full_comparable_array(const full_comparable_array & array);

   inline bool sort_find(ARG_TYPE & arg,index & iIndex,index iStart,index iEnd) const
   {
      if(this->get_size() == 0)
      {
         return false;
      }
      index iLowerBound = iStart;
      index iMaxBound = iEnd;
      index iUpperBound = iMaxBound;
      ::primitive::memory_offset iCompare;
      // do binary search
      iIndex = (iUpperBound + iLowerBound) / 2;
      while(iUpperBound - iLowerBound >= 8)
      {
         iCompare = COMPARE::CompareElements(&this->element_at(iIndex),arg);
         if(iCompare == 0)
         {
            return true;
         }
         else if(iCompare > 0)
         {
            iUpperBound = iIndex - 1;
            if(iUpperBound < 0)
            {
               iIndex = 0;
               break;
            }
         }
         else
         {
            iLowerBound = iIndex + 1;
            if(iLowerBound > iMaxBound)
            {
               iIndex = iMaxBound + 1;
               break;
            }
         }
         iIndex = (iUpperBound + iLowerBound) / 2;
      }
      // do sequential search
      while(iIndex < this->get_count())
      {
         iCompare = COMPARE::CompareElements(&this->element_at(iIndex),arg);
         if(iCompare == 0)
            return true;
         else if(iCompare < 0)
            iIndex++;
         else
            break;
      }
      if(iIndex >= this->get_count())
         return false;
      while(iIndex >= 0)
      {
         iCompare = COMPARE::CompareElements(&this->element_at(iIndex),arg);
         if(iCompare == 0)
            return true;
         else if(iCompare > 0)
            iIndex--;
         else
            break;
      }
      iIndex++;
      return false;

   }


};



template < class TYPE,class ARG_TYPE,class ARRAY_TYPE,class COMPARE>
full_comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE,COMPARE>::
full_comparable_array()
{
}
template < class TYPE,class ARG_TYPE,class ARRAY_TYPE,class COMPARE>
full_comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE,COMPARE>::
full_comparable_array(const full_comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE,COMPARE> & a):
ARRAY_TYPE(a)
{
   this->operator = (a);
}




template < class TYPE, class ARRAY_TYPE = comparable_array < void * > >
class ptr_array :
   virtual public ARRAY_TYPE
{
public:


   inline ptr_array() {}
   inline ptr_array(const ptr_array & a) { this->operator = (a); }
   inline ptr_array(ptr_array && a) { this->operator = (a); }


   inline ptr_array & operator = (const ptr_array & a) { this->ARRAY_TYPE::operator = (a); return *this; }
   inline ptr_array & operator = (ptr_array && a){ this->ARRAY_TYPE::operator = (a); return *this; }

   inline TYPE * & element_at(index i) { return (TYPE* &)ARRAY_TYPE::element_at(i); }
   inline TYPE * element_at(index i) const { return (TYPE*)ARRAY_TYPE::element_at(i); }

   inline TYPE * & operator[](index i) { return element_at(i); }
   inline TYPE * operator[](index i) const { return element_at(i); }
   
   inline TYPE * & first_element(index i = 0) { return (TYPE* &)ARRAY_TYPE::first_element(i); }
   inline TYPE * first_element(index i = 0) const { return (TYPE*)this->first_element(i); }

   inline TYPE * & last_element(index i = -1) { return (TYPE* &)ARRAY_TYPE::last_element(i); }
   inline TYPE * last_element(index i = 0) const { return (TYPE*)ARRAY_TYPE::last_element(i); }

   inline TYPE * & back(index i = -1) { return (TYPE* &)ARRAY_TYPE::back(i); }
   inline TYPE * back(index i = 0) const { return (TYPE*)ARRAY_TYPE::back(i); }

   inline TYPE** get_data() { return (TYPE**)ARRAY_TYPE::get_data(); }


};













class CLASS_DECL_AURA const_char_ptra:
   public ptr_array < const char >
{
};
