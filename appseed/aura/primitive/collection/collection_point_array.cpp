//#include "framework.h"
//#include <math.h>

point_array::point_array(const POINTD * lppt,::count c)
{
   while(c > 0)
   {
      add((int32_t) lppt->x,(int32_t) lppt->y);
      lppt++;
      c--;
   }
}

point_array::~point_array()
{
}

/*	public void rotatePoint(point p, float angle)
		{
		point lp = new point(p.x, p.y);
		p.x = lp.x * Math.cos(angle) - lp.y * Math.sin(angle);
		p.y = lp.x * Math.sin(angle) + lp.y * Math.cos(angle);
		} */

	/*public void translatePolygonD(PolygonD p, int32_t dx, int32_t dy)
		{
		double lx, ly;
		for(int32_t i = 0; i < p.npoints; i++)
			{
			p.xpoints[i] += dx;
			p.ypoints[i] += dy;
			}
		}*/




point64_array::~point64_array()
{
}

//void point64_array::offset(int64_t x, int64_t y)
//{
//   for(int32_t i = 0; i < this->get_size(); i++)
//   {
//      this->element_at(i).x += x;
//      this->element_at(i).y += y;
//   }
//}


pointd_array::~pointd_array()
{
}

//void pointd_array::offset(double x, double y)
//{
//   for(int32_t i = 0; i < this->get_size(); i++)
//   {
//      this->element_at(i).x += x;
//      this->element_at(i).y += y;
//   }
//}
//
//
//
//
//void pointd_array::get_bounding_rect(LPRECTD lprect) const
//{
//
//   get_bounding_rect(lprect, get_data(), get_count());
//
//}
//
//void pointd_array::get_bounding_rect(LPRECTD lprect, const POINTD * lppoint, ::count count)
//{
//
//   if(count <= 0)
//   {
//
//      lprect->left      = 0;
//      lprect->top       = 0;
//      lprect->right     = 0;
//      lprect->bottom    = 0;
//
//   }
//   else
//   {
//      lprect->left      = lppoint[0].x;
//      lprect->top       = lppoint[0].y;
//      lprect->right     = lppoint[0].x;
//      lprect->bottom    = lppoint[0].y;
//
//      for(int32_t i = 1; i < count; i++)
//      {
//         if(lppoint[i].x < lprect->left)
//            lprect->left = lppoint[i].x;
//         else if(lppoint[i].x > lprect->right)
//            lprect->right = lppoint[i].x;
//         if(lppoint[i].y < lprect->top)
//            lprect->top = lppoint[i].y;
//         else if(lppoint[i].y > lprect->bottom)
//            lprect->bottom = lppoint[i].y;
//      }
//
//   }
//
//}
//
//
//bool pointd_array::bounding_rect_contains_pt(pointd pt)
//{
//   rectd rect;
//   get_bounding_rect(rect);
//   return rect.contains(pt);
//}
//
//
//
//void pointd_array::rotate(double dAngle)
//{
//
//   double x;
//   double y;
//   double dCos = cos(dAngle);
//   double dSin = sin(dAngle);
//
//   for(int32_t i = 0; i < get_count(); i++)
//   {
//      x = element_at(i).x;
//      y = element_at(i).y;
//      element_at(i).x = (x * dCos - y * dSin);
//      element_at(i).y = (x * dSin + y * dCos);
//   }
//
//}
//
