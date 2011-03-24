#include "StdAfx.h"

namespace kar
{

   LyricViewLineSelection::LyricViewLineSelection(::ca::application * papp) :
ca(papp)
   {
      m_estate = state_initial;

   }

   LyricViewLineSelection::~LyricViewLineSelection()
   {

   }


   void LyricViewLineSelection::relay_event(LyricViewLine & viewline, gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::base, pbase, pobj);

      UINT message = pbase->m_uiMessage;

      if(message != WM_MOUSEMOVE
         || message != WM_TIMER
         || message != WM_LBUTTONDOWN
         || message != WM_LBUTTONUP)
      {
         return;
      }
    
       int iToken;
       int iChar;
       if((message == WM_MOUSEMOVE && GetState() == StateTracking)
          || message == WM_LBUTTONDOWN
          || message == WM_LBUTTONUP)
       {
          bool bInside;
          point ptCursor(
             LOWORD(pbase->m_lparam),  // horizontal position of cursor 
             HIWORD(pbase->m_lparam));  // vertical position of cursor 
          
          rect rectPlacement;
          viewline.GetPlacement(rectPlacement);
          bInside = rectPlacement.contains(ptCursor) != 0;
          if(!bInside && GetState() == StateTracking)
          {
             if(message == WM_LBUTTONUP
                || message == WM_MOUSEMOVE)
             {   
                if(ptCursor.y < rectPlacement.top
                   ||
                   (ptCursor.y <= rectPlacement.bottom &&
                   ptCursor.x < rectPlacement.left))
                {
                   SetSelBefore(viewline);
                   viewline.GetKaraokeView()->_001RedrawWindow();
                }
                else
                {
                   SetSelAfter(viewline);
                   viewline.GetKaraokeView()->_001RedrawWindow();
                }
                if(message == WM_LBUTTONUP)
                {
                   OnSelEvent(viewline, EventEnd);
                }
             }
             return;
          }
          else if(bInside)
          {
             //DWORD fwKeys = pbase->m_wparam; // key flags 
             if(message == WM_LBUTTONDOWN)
             {   
                if(viewline.CalcChar(ptCursor, iToken, iChar))
                {
                   m_item.SetTokenStart(iToken);
                   m_item.SetCharStart(iChar);
                   m_item.SetTokenEnd(iToken);
                   m_item.SetCharEnd(iChar);
   //                m_etype = TypeMaskStartHere;
                }
                else
                {
                   m_item.SetTokenStart(-1);
                   m_item.SetCharStart(-1);
                   m_item.SetTokenEnd(-1);
                   m_item.SetCharEnd(-1);
                }
                viewline.GetKaraokeView()->_001RedrawWindow();
                OnSelEvent(viewline, EventStart);
                pbase->m_bRet = true;
                return;         
             }
             else if(
                (message == WM_LBUTTONUP
                || message == WM_MOUSEMOVE)
                && GetState() == StateTracking)
             {   
                if(viewline.m_tokenaMain.get_size() <= 0)
                   return;
                if(viewline.CalcChar(ptCursor, iToken, iChar))
                {
                   m_item.SetTokenEnd(iToken);
                   m_item.SetCharEnd(iChar);
   //                m_item.NormalizeSel();
   //                m_etype |= TypeMaskEndHere;
                     viewline.GetKaraokeView()->_001RedrawWindow();
                }
                else
                {
                   if(ptCursor.x < viewline.m_tokenaMain.element_at(0).GetPosition())
                   {
                      SetSelBefore(viewline);
                   }
                   {
                      SetSelAfter(viewline);
                   }
                   viewline.GetKaraokeView()->_001RedrawWindow();
                   
                }
                if(message == WM_LBUTTONUP)
                {
                   OnSelEvent(viewline, EventEnd);
                   if(m_iTokenStartSource == m_item.GetTokenStart()
                      && m_iTokenEndSource == m_item.GetTokenEnd()
                      && m_iCharStartSource == m_item.GetCharStart()
                      && m_iCharEndSource == m_item.GetCharEnd())
                   {
                      string str;
                      point pt;
                      System.get_cursor_pos(&pt);
                      if(viewline.GetLink(str, pt))
                      {
                        kar::KaraokeView * pview = viewline.GetKaraokeView();
                        pview->OnLinkClick(str);
                      }
                   }
                }
                pbase->m_bRet = true;
                return;
             }
             else if(message == WM_MOUSEMOVE)
             {   
                point pt;
                System.get_cursor_pos(&pt);
                viewline.UpdateHover(pt);
             }
          }
      }
      else if(message == WM_TIMER)
      {
         UINT nIDEvent = pbase->m_wparam;
         if(nIDEvent == gen::Timer::ID_HOVER)
         {
            point pt;
            System.get_cursor_pos(&pt);
            viewline.UpdateHover(pt);
            if(!viewline.IsInHover())
            {
               ::user::interaction * pwnd = viewline.GetKaraokeView();
               pwnd->KillTimer(gen::Timer::ID_HOVER);
            }
         }
      }
   }

   void LyricViewLineSelection::OnSelEvent(LyricViewLine & viewline, LyricViewLineSelection::e_event eevent)
   {
      switch(eevent)
      {
      case EventStart:
         m_iTokenStartSource  = m_item.GetTokenStart();
         m_iTokenEndSource      = m_item.GetTokenEnd();
         m_iCharStartSource   = m_item.GetCharStart();
         m_iCharEndSource      = m_item.GetCharEnd();
         m_estate               = StateTracking;
         
         viewline.GetTemplate()->OnSelStart(&viewline);
         break;
      case EventEnd:
         //NormalizeSel(viewline);
         m_item.NormalizeSel();
         Select(
            m_item.GetTokenStart(),
            m_item.GetTokenEnd(), 
            m_item.GetCharStart(),
            m_item.GetCharEnd(), false);
         m_estate = state_initial;
         viewline.GetTemplate()->OnSelEnd(&viewline);
         
         break;
      default:
         ASSERT(FALSE);
      }
   }

   bool LyricViewLineSelection::SetSelBefore(LyricViewLine & viewline)
   {
   /*   if(m_etype & TypeMaskEndHere)
      {
         if(m_etype & TypeMaskStartHere)
         {
            m_etype &= ~TypeMaskStartHere;*/
            m_item.SetTokenStart(viewline.GetFirstToken());
            m_item.SetCharStart(0);
   /*      }
      }
      else if(m_etype &  TypeMaskStartHere)
      {
         m_etype &= ~TypeMaskStartHere;
         m_etype |= TypeMaskEndHere;
         m_item.SetTokenStart(viewline.GetFirstToken());
         m_item.SetCharStart(0);
      }
      else
      {
         string str;
         viewline.m_tokenaMain.element_at(viewline.GetTokenCount() - 1).GetText(str);
         m_item.SetTokenStart(viewline.GetFirstToken());
         m_item.SetCharStart(0);
         m_item.SetTokenEnd(viewline.GetFirstToken() + viewline.GetTokenCount() - 1);
         m_item.SetCharEnd(viewline.m_tokenaMain.last_element().GetCharCount() - 1);
      }*/
      return true;
   }

   bool LyricViewLineSelection::SetSelAfter(LyricViewLine & viewline)
   {
      if(viewline.GetTokenCount() > 0)
      {
         string str;
         viewline.m_tokenaMain.element_at(viewline.GetTokenCount() - 1).GetText(str);
         m_item.SetTokenEnd(viewline.GetFirstToken() + viewline.m_tokenaMain.get_size() - 1);
         m_item.SetCharEnd(str.get_length());
      }

   /*   if(m_etype & TypeMaskEndHere)
      {
         if(m_etype & TypeMaskStartHere)
         {*/
      /*         string str;
            viewline.m_tokenaMain.element_at(viewline.GetTokenCount() - 1).GetText(str);
   //         m_etype &= ~TypeMaskEndHere;
            m_item.SetTokenEnd(viewline.GetFirstToken() + viewline.m_tokenaMain.get_size() - 1);
            m_item.SetCharEnd(str.get_length());*/
   /*      }
         else
         {
            string str;
            viewline.m_tokenaMain.element_at(viewline.GetTokenCount() - 1).GetText(str);
            m_etype &= ~TypeMaskEndHere;
            m_etype |= TypeMaskStartHere;
            m_item.SetTokenEnd(viewline.GetFirstToken() + viewline.m_tokenaMain.get_size() - 1);
            m_item.SetCharEnd(str.get_length() - 1);
         }
      }
      else if(m_etype &  TypeMaskStartHere)
      {
      }
      else
      {
         string str;
         viewline.m_tokenaMain.element_at(viewline.GetTokenCount() - 1).GetText(str);
         m_item.SetTokenStart(viewline.GetFirstToken());
         m_item.SetCharStart(0);
         m_item.SetTokenEnd(viewline.GetFirstToken() + viewline.m_tokenaMain.get_size() - 1);
         m_item.SetCharEnd(str.get_length() - 1);
      }*/
      return true;
   }

   void LyricViewLineSelection::NormalizeSel(LyricViewLine & viewline)
   {
      UNREFERENCED_PARAMETER(viewline);
      ASSERT(FALSE);
   /*   string str;   
      if(m_item.m_iTokenStart < 0)
      {
      }
      else if(m_item.m_iTokenStart >= viewline.m_tokenaMain.get_size())
      {
         m_item.m_iTokenStart = viewline.m_tokenaMain.get_size() - 1;
         if(m_item.m_iTokenStart < 0)
         {
            m_item.m_iCharStart = -1;
         }
         else
         {
            m_item.m_iCharStart = 0;
         }
      }
      if(m_item.m_iTokenStart < 0)
      {
      }
      else
      {
         viewline.m_tokenaMain[m_item.m_iTokenStart].GetText(str);
         if(m_item.m_iCharStart >= str.get_length())
         {
            if(str.is_empty())
            {
               m_item.m_iCharStart = 0;
            }
            else
            {
               m_item.m_iCharStart = str.get_length() - 1;
            }
         }
         if(m_item.m_iTokenEnd < 0)
         {
            m_item.m_iTokenEnd = m_item.m_iTokenStart;
            m_item.m_iCharEnd = m_item.m_iCharStart;
         }
         else if(m_item.m_iCharEnd < 0)
         {
            m_item.m_iCharEnd = m_item.m_iCharStart;
         }
         
         if(m_item.m_iTokenEnd >= viewline.m_tokenaMain.get_size())
         {
            m_item.m_iTokenEnd = viewline.m_tokenaMain.get_size() - 1;
            if(m_item.m_iTokenEnd < 0)
            {
               m_item.m_iCharEnd = -1;
            }
            else
            {
               viewline.m_tokenaMain[m_item.m_iTokenEnd].GetText(str);
               if(str.is_empty())
               {
                  m_item.m_iCharEnd = 0;
               }
               else
               {
                  m_item.m_iCharEnd = str.get_length() - 1;
               }
            }
         }
         viewline.m_tokenaMain[m_item.m_iTokenEnd].GetText(str);
         if(m_item.m_iCharEnd >= str.get_length())
         {
            if(str.is_empty())
            {
               m_item.m_iCharEnd = 0;
            }
            else
            {
               m_item.m_iCharEnd = str.get_length() - 1;
            }
         }
      }*/
      
   }

   LyricViewLineSelection & LyricViewLineSelection::operator =(LyricViewLineSelection & selection)
   {
      m_estate = selection.m_estate;
      m_etype = selection.m_etype;
      return *this;
   }


   LyricViewLineSelectionItem::LyricViewLineSelectionItem()
   {
   }
   LyricViewLineSelectionItem::LyricViewLineSelectionItem(
      int      iTokenStart,
      int      iTokenEnd,
      int      iCharStart,
      int      iCharEnd
      )
   {
      m_iTokenStart = iTokenStart;
      m_iTokenEnd = iTokenEnd;
      m_iCharStart = iCharStart;
      m_iCharEnd = iCharEnd;
   }
   LyricViewLineSelectionItem::~LyricViewLineSelectionItem()
   {
   }

   LyricViewLineSelectionItem & LyricViewLineSelectionItem::operator =(const LyricViewLineSelectionItem & item)
   {
      m_iTokenStart   = item.m_iTokenStart;
      m_iTokenEnd      = item.m_iTokenEnd;
      m_iCharStart   = item.m_iCharStart;
      m_iCharEnd      = item.m_iCharEnd;
      return *this;
   }

   void LyricViewLineSelection::Select(
      int      iTokenStart,
      int      iTokenEnd,
      int      iCharStart,
      int      iCharEnd,
      bool    bMerge)
   {
      UNREFERENCED_PARAMETER(bMerge);
      for(int i = 0; i < m_itema.get_size(); i++)
      {
         if(m_itema.element_at(i).Intersect(iTokenStart, iTokenEnd))
         {
            m_itema.element_at(i).SetTokenStart(iTokenStart);
            m_itema.element_at(i).SetTokenEnd(iTokenEnd);
            m_itema.element_at(i).SetCharStart(iCharStart);
            m_itema.element_at(i).SetCharEnd(iCharEnd);
            return;
         }
      }
      m_itema.remove_all();
      m_itema.add(
         LyricViewLineSelectionItem(
            iTokenStart,
            iTokenEnd,
            iCharStart,
            iCharEnd));
   }

   bool LyricViewLineSelection::OnLButtonDown(LyricViewLine & viewline, UINT user, point pt)
   {
      UNREFERENCED_PARAMETER(user);
      
      bool bInside;

          int iToken;
          int iChar;
          rect rectPlacement;
          viewline.GetPlacement(rectPlacement);
          bInside = rectPlacement.contains(pt) != 0;
          if(!bInside && GetState() == StateTracking)
          {
             return false;
          }
          else if(bInside)
          {
             //DWORD fwKeys = user; // key flags 
                if(viewline.CalcChar(pt, iToken, iChar))
                {
                   m_item.SetTokenStart(iToken);
                   m_item.SetCharStart(iChar);
                   m_item.SetTokenEnd(iToken);
                   m_item.SetCharEnd(iChar);
   //                m_etype = TypeMaskStartHere;
                }
                else
                {
                   m_item.SetTokenStart(-1);
                   m_item.SetCharStart(-1);
                   m_item.SetTokenEnd(-1);
                   m_item.SetCharEnd(-1);
                }
               viewline.GetKaraokeView()->_001RedrawWindow();
                OnSelEvent(viewline, EventStart);
                return true;         
          }

          return false;
   }

   bool LyricViewLineSelection::OnMouseMove(LyricViewLine & viewline, UINT user, point pt)
   {
      UNREFERENCED_PARAMETER(viewline);
      UNREFERENCED_PARAMETER(user);
      UNREFERENCED_PARAMETER(pt);
      return false;
   }

   bool LyricViewLineSelection::OnLButtonUp(LyricViewLine & viewline, UINT user, point pt)
   {
      UNREFERENCED_PARAMETER(user);
      if(!viewline.IsVisible())
         return false;

       bool bInside;
       
              int iToken;
          int iChar;

       rect rectPlacement;
       viewline.GetPlacement(rectPlacement);
       bInside = rectPlacement.contains(pt) != 0;
       if(!bInside && GetState() == StateTracking)
       {
          if(pt.y < rectPlacement.top
             ||
             (pt.y <= rectPlacement.bottom &&
             pt.x < rectPlacement.left))
          {
             SetSelBefore(viewline);
             viewline.GetKaraokeView()->_001RedrawWindow();
          }
          else
          {
             SetSelAfter(viewline);
             viewline.GetKaraokeView()->_001RedrawWindow();
          }
          return false;
       }
       else if(bInside)
       {
          //DWORD fwKeys = user; // key flags 
            if(GetState() == StateTracking)
          {   
             if(viewline.m_tokenaMain.get_size() <= 0)
                return false;
             if(viewline.CalcChar(pt, iToken, iChar))
             {
                m_item.SetTokenEnd(iToken);
                m_item.SetCharEnd(iChar);
                m_item.NormalizeSel();
   //             m_etype |= TypeMaskEndHere;
               viewline.GetKaraokeView()->_001RedrawWindow();
             }
             else
             {
                if(pt.x < viewline.m_tokenaMain.element_at(0).GetPosition())
                {
                   SetSelBefore(viewline);
                }
                {
                   SetSelAfter(viewline);
                }
                viewline.GetKaraokeView()->_001RedrawWindow();
                
             }
             OnSelEvent(viewline, EventEnd);
             if(m_iTokenStartSource == m_item.GetTokenStart()
                && m_iTokenEndSource == m_item.GetTokenEnd()
                && m_iCharStartSource == m_item.GetCharStart()
                && m_iCharEndSource == m_item.GetCharEnd())
             {
                string str;
                if(viewline.GetLink(str, pt) == ::user::line_hit_link)
                {
                   kar::KaraokeView * pview = viewline.GetKaraokeView();
                   pview->OnLinkClick(str);
                }
             }
             return true;
          }
       }
      
      return false;
   }

   bool LyricViewLineSelection::OnTimer(LyricViewLine & viewline, UINT user)
   {
      UINT nIDEvent = user;
      if(nIDEvent == gen::Timer::ID_HOVER)
      {
         if(viewline.IsInHover())
         {
            point pt;
            GetCursorPos(&pt);
            viewline.GetKaraokeView()->ScreenToClient(&pt);
            viewline.UpdateHover(pt);
            if(!viewline.IsInHover())
            {
               rect rectPlacement;
               viewline.GetPlacement(rectPlacement);
               viewline.GetKaraokeView()->_001RedrawWindow();
            }
   //         ::ca::window * pwnd = viewline.GetWnd();
   //         pwnd->KillTimer(gen::Timer::ID_HOVER);
         }
      }
      return false;
   }

   void LyricViewLineSelectionItem::NormalizeSel()
   {
      if(m_iTokenStart > m_iTokenEnd)
      {
         gen::swap(m_iTokenEnd, m_iTokenStart);
         gen::swap(m_iCharEnd, m_iCharStart);
      }
      else if(m_iTokenStart == m_iTokenEnd
         && m_iCharStart > m_iCharEnd)
      {
         gen::swap(m_iCharEnd, m_iCharStart);
      }

   }

   int LyricViewLineSelectionItem::GetTokenStart()
   {
      return m_iTokenStart;
   }
   
   int LyricViewLineSelectionItem::GetTokenEnd()
   {
      return m_iTokenEnd;
   }
   
   int LyricViewLineSelectionItem::GetCharStart()
   {
      return m_iCharStart;
   }
   
   int LyricViewLineSelectionItem::GetCharEnd()
   {
      return m_iCharEnd;
   }
   
   void LyricViewLineSelectionItem::SetTokenStart(int iToken)
   {
      m_iTokenStart = iToken;
   }
   
   void LyricViewLineSelectionItem::SetTokenEnd(int iToken)
   {
      m_iTokenEnd = iToken;
   }
   
   void LyricViewLineSelectionItem::SetCharStart(int iChar)
   {
      m_iCharStart = iChar;
   }
   
   void LyricViewLineSelectionItem::SetCharEnd(int iChar)
   {
      m_iCharEnd = iChar;
   }



   LyricViewLineSelection::e_state LyricViewLineSelection::GetState()
   {
      return m_estate;
   }


   bool LyricViewLineSelectionItem::Intersect(int iFirstToken, int iLastToken)
   {

      return max(iFirstToken, m_iTokenStart) <= min(iLastToken, m_iTokenEnd);

   }

   bool LyricViewLineSelection::get_item(LyricViewLineSelectionItem &item, LyricViewLine &viewline)
   {
      if(m_item.Intersect(viewline))
      {
         item = m_item;
         item.NormalizeSel();
         return true;
      }
      for(int iItem = 0; iItem < m_itema.get_size(); iItem++)
      {
         LyricViewLineSelectionItem & itemTest = m_itema.element_at(iItem);
         if(itemTest.Intersect(viewline))
         {
            item = itemTest;
            item.NormalizeSel();
            return true;
         }

      }
      return false;
   }

} // namespace kar

