#pragma once


template <class TYPE, class ARG_TYPE = const TYPE &>
class array_ptr :
   virtual public array_smart_ptr < TYPE, ARG_TYPE >
{
public:
	array_ptr();
	virtual ~array_ptr();

   void remove_at(INT_PTR iIndex);
   count remove_all(bool bDelete = true);
   void remove_last(bool bDelete = true);

};
template <class TYPE, class ARG_TYPE>
array_ptr < TYPE, ARG_TYPE >::array_ptr()
{
}

template <class TYPE, class ARG_TYPE>
array_ptr < TYPE, ARG_TYPE >::~array_ptr()
{
   remove_all();
}

template <class TYPE, class ARG_TYPE>
inline void array_ptr < TYPE, ARG_TYPE >::remove_at(
   index iIndex)
{
   gen::sdel<TYPE>(m_ptra.element_at(iIndex));
   m_ptra.remove_at(iIndex);
}

template <class TYPE, class ARG_TYPE>
inline count array_ptr < TYPE, ARG_TYPE >::remove_all(bool bDelete /*=true*/)
{
   if(bDelete)
   {
      for(int iIndex = 0; iIndex < m_ptra.get_size(); iIndex++)
      {
         gen::sdel<TYPE>(m_ptra.element_at(iIndex));
      }
   }
   return m_ptra.remove_all();
}


template <class TYPE, class ARG_TYPE>
inline void array_ptr < TYPE, ARG_TYPE >::remove_last(bool bDelete /*=true*/)
{
   if(bDelete)
   {
      gen::sdel<TYPE>(m_ptra.last_element());
   }
   m_ptra.remove_last();
}


