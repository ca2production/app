#pragma once

inline uint32_t natural(int32_t i)
{
   return i >= 0 ? (uint32_t) i : 0;
}

inline uint64_t natural(int64_t i)
{
   return i >= 0 ? (uint64_t) i : 0;
}

// return minimum zero or positive integer
// otherwise, return third optional default -1 argument
inline int32_t natural_min(int32_t i1, int32_t i2, int32_t iEscape = -1)
{
   if(i1 >= 0)
   {
      if(i2 >= 0)
      {
         if(i2 < i1)
            return i2;
         else
            return i1;
      }
      else
      {
         return i1;
      }
   }
   else
   {
      if(i2 >= 0)
      {
         return i2;
      }
      else
      {
         return iEscape;
      }
   }
}
