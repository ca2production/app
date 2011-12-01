#pragma once

#include "sort.h"

template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
class key_sort_array
{
public:
   key_sort_array();
   virtual ~key_sort_array();

   void SetKeyProperty(KEY (TYPE::* lpfnKeyProperty)());
   bool FindFirst(KEY k, int & iIndex);
   bool FindFirst(KEY k, int & iIndex, int iStart, int iEnd);

   int add(ARG_TYPE type);

   int GetSize();

   TYPE & ElementAt(int iIndex);

protected:


   KEY (TYPE::* m_lpfnKeyProperty)();
   // ARRAY must implement:
   // InsertAt(int iIndex, ARG_TYPE)
   // TYPE & ElementAt(int iIndex)
   // int GetSize()
   ARRAY m_array;

};
template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
key_sort_array()
{
}
template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
~key_sort_array()
{
}


template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
TYPE & key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
ElementAt(int iIndex)
{
   return m_array.ElementAt(iIndex);
}


template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
bool key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
FindFirst(KEY k, int & iIndex)
{
   return FindFirst(k, iIndex, 0, GetSize() - 1);
}


template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
bool key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
FindFirst(KEY k, int & iIndex, int iStart, int iEnd)
{
   if(GetSize() == 0)
   {
      return false;
   }
   int iLBound = iStart;
   int iMaxBound = iEnd;
   int iUBound = iMaxBound;

   while(true)
   {
      iIndex = (iUBound + iLBound) / 2;
      if((ElementAt(iIndex).*m_lpfnKeyProperty)() == k)
      {
         while(iIndex > 0)
         {
            if((ElementAt(iIndex - 1).*m_lpfnKeyProperty)() == k)
            {
               iIndex--;
            }
            else
            {
               break;
            }
         }
         return true;
      }
      else if((ElementAt(iIndex).*m_lpfnKeyProperty)() > k)
      {
         iUBound = iIndex - 1;
         if(iUBound < 0)
         {
            iIndex = 0;
            break;
         }
         if(iUBound < iLBound)
         {
            iIndex = iLBound;
            break;
         }
      }
      else
      {
         iLBound = iIndex + 1;
         if(iLBound > iMaxBound)
         {
            iIndex = iMaxBound + 1;
            break;
         }
         if(iUBound < iLBound)
         {
            iIndex = iLBound;
            break;
         }
      }

   }
   return false;

}

template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
int key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
add(ARG_TYPE t)
{
   int iIndex = 0;
   FindFirst((t.*m_lpfnKeyProperty)(), iIndex);
   m_array.InsertAt(iIndex, t);
   return iIndex;
}

template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
int key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
GetSize()
{
   return m_array.GetSize();
}

