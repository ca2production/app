//
//  macos_os.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#include "framework.h"



CLASS_DECL_AURA bool _istlead(int32_t ch)
{
   
   return false;
   
}








WINBOOL GetCursorPos(LPPOINT lpptCursor)
{
   
/*   HIPoint point;
   
   HICoordinateSpace space = kHICoordSpaceScreenPixel;
   
   HIGetMousePosition(space, NULL, &point);
   
   
   lpptCursor->x = point.x;
   lpptCursor->y = point.y;
  */ 
   
   return TRUE;
   
}

