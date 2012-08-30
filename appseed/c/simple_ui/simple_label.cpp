#include "framework.h"

#ifdef WINDOWS
#include <GdiPlus.h>
#endif


simple_label::simple_label()
{
   
}

simple_label::~simple_label()
{
}



void simple_label::draw_this(HDC hdc)
{


   Gdiplus::Graphics graphics2(hdc);


#if CA2_PLATFORM_VERSION == CA2_BASIS
   Gdiplus::SolidBrush b(Gdiplus::Color(223, 84, 49, 77));
#else
   Gdiplus::SolidBrush b(Gdiplus::Color(223, 49, 84, 23));
#endif

   Gdiplus::Font f(L"Geneva", (float) (height(&m_rect) - 4), 0.0f, Gdiplus::UnitPixel);

   wchar_t * pwsz = utf8_to_16(m_strText);

   graphics2.DrawString(pwsz, wcslen_dup(pwsz), &f, Gdiplus::PointF((float) (m_rect.left + 2), (float) m_rect.top), &b);

   ca2_free(pwsz);

}

