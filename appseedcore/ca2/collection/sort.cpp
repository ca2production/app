#include "StdAfx.h"

namespace  sort
{

   void QuickSort(
      base_array<DWORD, DWORD> & base_array,
      int fCompare(const DWORD, const DWORD),
      void swap(void * lpVoidSwapArg, int iA, int iB),
      void * lpVoidSwapArg)
   {
      dword_array stackLowerBound;
      dword_array stackUpperBound;
      int iLowerBound;
      int iUpperBound;
      int iLPos, iUPos, iMPos;
      DWORD t;

      if(base_array.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(base_array.get_upper_bound());
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
                  if(fCompare(base_array.get_at(iMPos), base_array.get_at(iUPos)) <= 0)
                     iUPos--;
                  else
                  {
                     t = base_array.get_at(iMPos);
                     base_array.set_at(iMPos, base_array.get_at(iUPos));
                     base_array.set_at(iUPos, t);
                     swap(lpVoidSwapArg, iUPos, iMPos);
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
                  if(fCompare(base_array.get_at(iLPos), base_array.get_at(iMPos)) <= 0)
                     iLPos++;
                  else
                  {
                     t = base_array.get_at(iMPos);
                     base_array.set_at(iMPos, base_array.get_at(iLPos));
                     base_array.set_at(iLPos, t);
                     swap(lpVoidSwapArg, iLPos, iMPos);
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

   void BubbleSort(LPINT lpInt, int size)
   {
      for(int i = 0; i < size; i++)
         for(int j = i + 1; j < size; j++)
         {
            if(lpInt[i] > lpInt[j])
            {
               INT swap = lpInt[j];
               lpInt[j] = lpInt[i];
               lpInt[i] = swap;
            }
         }

   }



   void CLASS_DECL_ca QuickSort(
      index iSize,
      base_array < ARG_COMPARE_FUNCTION, ARG_COMPARE_FUNCTION > & comparefna,
      base_array < ARG_SWAP_FUNCTION, ARG_SWAP_FUNCTION > & swapfna,
      base_array < void *, void * > & comparearga,
      base_array < void *, void * > & swaparga)
   {
      dword_array stackLowerBound;
      dword_array stackUpperBound;
      int iLowerBound;
      int iUpperBound;
      int iLPos, iUPos, iMPos;
      int iCmp;

      int iCompare;

      if(iSize >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(iSize - 1);
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
                  iCmp = 0;
                  for(int i = 0; i < comparefna.get_size(); i++)
                  {
                     iCompare = comparefna[i](comparearga[i], iMPos, iUPos);
                     if(iCompare > 0)
                     {
                        iCmp = 1;
                        break;
                     }
                     else if(iCompare < 0)
                     {
                        iCmp = -1;
                        break;
                     }
                  }
                  if(iCmp <= 0)
                     iUPos--;
                  else
                  {
                     for(int i = 0; i < swapfna.get_size(); i++)
                     {
                        swapfna[i](swaparga[i], iMPos, iUPos);
                     }
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
                  iCmp = 0;
                  for(int i = 0; i < comparefna.get_size(); i++)
                  {
                     iCompare = comparefna[i](comparearga[i], iLPos, iMPos);
                     if(iCompare > 0)
                     {
                        iCmp = 1;
                        break;
                     }
                     else if(iCompare < 0)
                     {
                        iCmp = -1;
                        break;
                     }
                  }
                  if(iCmp <= 0)
                     iLPos++;
                  else
                  {
                     for(int i = 0; i < swapfna.get_size(); i++)
                     {
                        swapfna[i](swaparga[i], iLPos, iMPos);
                     }
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

} // namespace sort