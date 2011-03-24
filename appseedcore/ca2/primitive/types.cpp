#include "StdAfx.h"


__int64 MulDiv(__int64 nNumber, __int64 nNumerator, __int64 nDenominator)
{
   return MulDiv64(nNumber, nNumerator, nDenominator);
}

bool copy(__rect64 * prectDest, const __rect64 * prectSrc)
{
   *prectDest = *prectSrc;
   return TRUE;
}

bool copy(__rect64 * prectDest, const RECT * prectSrc)
{
   prectDest->left      = prectSrc->left;
   prectDest->top       = prectSrc->top;
   prectDest->right     = prectSrc->right;
   prectDest->bottom    = prectSrc->bottom;
   return TRUE;
}

bool copy(RECT * prectDest, const __rect64 * prectSrc)
{
   if(is64(prectSrc->left)
   || is64(prectSrc->top)
   || is64(prectSrc->right)
   || is64(prectSrc->bottom))
      return FALSE;
   prectDest->left      = (LONG) prectSrc->left;
   prectDest->top       = (LONG) prectSrc->top;
   prectDest->right     = (LONG) prectSrc->right;
   prectDest->bottom    = (LONG) prectSrc->bottom;
   return TRUE;
}
bool is_empty(const __rect64 * prect)
{
   return 
      prect->left   >= prect->right
      && prect->top >= prect->bottom;
}

bool contains(const __rect64 * prect, point64 pt)
{
   return 
      pt.x >= prect->left && pt.x <= prect->right
      && pt.y >= prect->top && pt.y <= prect->bottom;
}

bool set(__rect64 * prectDest, __int64 x1, __int64 y1, __int64 x2, __int64 y2)
{
   prectDest->left      = x1;
   prectDest->top       = y1;
   prectDest->right     = x2;
   prectDest->bottom    = y2;
   return TRUE;
}
bool null(__rect64 * prectDest)
{
   prectDest->left      = 0;
   prectDest->top       = 0;
   prectDest->right     = 0;
   prectDest->bottom    = 0;
   return true;
}
bool is_equal(const __rect64 * prect1, const __rect64 * prect2)
{
   return
      prect1->left      == prect2->left &&
      prect1->top       == prect2->top &&
      prect1->right     == prect2->right &&
      prect1->bottom    == prect2->bottom;
}

bool inflate(__rect64 * prect, __int64 x, __int64 y)
{
   prect->left      -= x;
   prect->top       -= y;
   prect->right     += x;
   prect->bottom    += y;
   return TRUE;
}

bool deflate(__rect64 * prect, __int64 x, __int64 y)
{
   prect->left      += x;
   prect->top       += y;
   prect->right     -= x;
   prect->bottom    -= y;
   return TRUE;
}

bool offset(__rect64 * prect, __int64 x, __int64 y)
{
   prect->left      += x;
   prect->top       += y;
   prect->right     += x;
   prect->bottom    += y;
   return TRUE;
}

bool x_intersect_rect(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2)
{
   prect->left    = max(prect1->left   , prect2->left);
   prect->right   = min(prect1->right  , prect2->right);
   if(prect->right > prect->left)
   {
      return TRUE;
   }
   else
   {
      return FALSE;
   }
}

bool y_intersect_rect(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2)
{
   prect->top     = max(prect1->top    , prect2->top);
   prect->bottom  = min(prect1->bottom , prect2->bottom);
   if(prect->top < prect->bottom)
   {
      return TRUE;
   }
   else
   {
      null(prect);
      return FALSE;
   }
}


bool intersect(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2)
{
   if(x_intersect_rect(prect, prect1, prect2)
   && y_intersect_rect(prect, prect1, prect2))
   {
      return TRUE;
   }
   else
   {
      null(prect);
      return FALSE;
   }
}

bool unite(__rect64 * prect, const __rect64 * prect1, const __rect64 * prect2)
{
   if(is_empty(prect1))
   {
      if(is_empty(prect2))
      {
         ::null(prect);
         return FALSE;
      }
      else
      {
         *prect =* prect2;
         return TRUE;
      }
   }
   else if(is_empty(prect2))
   {
      *prect = *prect1;
      return TRUE;
   }
   prect->left    = min(prect1->left   , prect2->left);
   prect->right   = max(prect1->right  , prect2->right);
   prect->top     = min(prect1->top    , prect2->top);
   prect->bottom  = max(prect1->bottom , prect2->bottom);
   if(prect->right > prect->left &&
      prect->bottom > prect->top)
   {
      return TRUE;
   }
   else
   {
      return FALSE;
   }
}



