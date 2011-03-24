#pragma once

template <class ARG_TYPE>
inline index BaseSortCompare(ARG_TYPE t1, ARG_TYPE t2)
{
   return t1 - t2;
}

template <>
inline index BaseSortCompare(float f1, float f2)
{
   if(f1 > f2)
      return 1;
   else if(f1 < f2)
      return -1;
   else
      return 0;
}

template <>
inline index BaseSortCompare(double d1, double d2)
{
   if(d1 > d2)
      return 1;
   else if(d1 < d2)
      return -1;
   else
      return 0;
}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY = comparable_array < TYPE, ARG_TYPE > >
class sort_array :
   public BASE_ARRAY
{
public:
   

   bool BaseSortFind(ARG_TYPE t, INT_PTR & iIndex) const;
   bool BaseSortFind(ARG_TYPE t, INT_PTR & iIndex, INT_PTR iStart, INT_PTR iEnd) const;
   

   index BaseSortInsert(ARG_TYPE t);
   index BaseSortInsert(ARG_TYPE t, INT_PTR iStart, INT_PTR iEnd);

   //void AddCoupledSwapInterface(CBaseSwapInterface * pswap);

   void QuickSort();

   void QuickSort(INT_PTR i1, INT_PTR i2);

   //virtual void OnAfterSwap(index i1, index i2);

   void Paste(base_array <TYPE, ARG_TYPE> & base_array);


protected:


   //DispatchPtrArray < CBaseSwapInterface, CBaseSwapInterface *>
     //    m_swapptra;
   
};



template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
bool
sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
BaseSortFind(ARG_TYPE t, index & iIndex) const 
{
   return BaseSortFind(t, iIndex, 0, get_size() - 1);
}


template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
bool
sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
BaseSortFind(ARG_TYPE t, index & iIndex, index iStart, index iEnd) const
{
   if(get_size() == 0)
   {
      return false;
   }
   index iLBound = iStart;
   index iMaxBound = iEnd;
   index iUBound = iMaxBound;
   index iCompare;
   // do binary search
   iIndex = (iUBound + iLBound) / 2;
   while(iUBound - iLBound >= 8)
   {
      iCompare = BaseSortCompare((ARG_TYPE) element_at(iIndex), (ARG_TYPE) t);
      if(iCompare == 0)
      {
         return true;
      }
      else if(iCompare > 0)
      {
         iUBound = iIndex - 1;
         if(iUBound < 0)
         {
            iIndex = 0;
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
      }
      iIndex = (iUBound + iLBound) / 2;
   }
   // do sequential search
   while(iIndex < get_count())
   {
      iCompare = BaseSortCompare((ARG_TYPE) element_at(iIndex), (ARG_TYPE) t);
      if(iCompare == 0)
         return true;
      else if(iCompare < 0)
         iIndex++;
      else
         break;
   }
   if(iIndex >= get_count())
      return false;
   while(iIndex >= 0)
   {
      iCompare = BaseSortCompare((ARG_TYPE) element_at(iIndex), (ARG_TYPE) t);
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

template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
index
sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
BaseSortInsert(ARG_TYPE t)
{
   index iIndex = 0;
   BaseSortFind(t, iIndex);
   insert_at(iIndex, t);
   return iIndex;
}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
index
sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
BaseSortInsert(ARG_TYPE t, index iStart, index iEnd)
{
   index iIndex = BaseSortFind(t, iIndex);
   insert_at(iIndex, t);
   return iIndex;
}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
void sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
Paste(base_array <TYPE, ARG_TYPE> & a)
{
   a.set_size(get_size());
   for(index i = 0; i < get_size(); i++)
   {
      a.set_at(i, element_at(i));
   }
}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
void
sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
QuickSort()
{
   QuickSort(0, get_size() - 1);
}

template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
void
sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
QuickSort(index i1, index i2)
{
   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
   //   TYPE t;
   
   if(get_size() >= 2)
   {
      stackLowerBound.push(i1);
      stackUpperBound.push(i2);
      while(true)
      {
         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();
         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;
         while(true)
         {
            while(true)
            {
               if(iMPos == iUPos)
                  break;
               if(BaseSortCompare(element_at(iMPos), element_at(iUPos)) <= 0)
                  iUPos--;
               else
               {
                  swap(iMPos, iUPos);
                  break;
               }
            }
            if(iMPos == iUPos)
               break;
            iMPos = iUPos;
            while(true)
            {
               if(iMPos == iLPos)
                  break;
               if(BaseSortCompare(element_at(iLPos), element_at(iMPos)) <= 0)
                  iLPos++;
               else
               {
                  swap(iLPos, iMPos);
                  break;
               }
            }
            if(iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
         if(iLowerBound < iMPos - 1)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos - 1);
         }
         if(iMPos + 1 < iUpperBound)
         {
            stackLowerBound.push(iMPos + 1);
            stackUpperBound.push(iUpperBound);
         }
         if(stackLowerBound.get_size() == 0)
            break;
      }
   }
}

