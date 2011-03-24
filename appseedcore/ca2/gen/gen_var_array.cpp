#include "StdAfx.h"

var_array::var_array()
{
}

var_array::var_array(const stringa & stra)
{
   operator = (stra);
}

var_array::var_array(const int_array & inta)
{
   operator = (inta);
}

var_array::var_array(const gen::property_set & propset)
{
   operator = (propset);
}

var_array::var_array(const var_array & vara)
{
   operator = (vara);
}

index var_array::add(var var)
{
   if(var.get_type() != var::type_empty_argument)
   {
      return array_ptr_alloc < class var >::add(var);
   }
   return -1;
}

count var_array::add(const var_array & vara)
{
   for(int i = 0; i < vara.get_size(); i++)
   {
      add(vara[i]);
   }
   return get_count();
}

string var_array::implode(const char * pszGlue) const
{
   string str;
   for(int i = 0; i < get_count(); i++)
   {
      if(i > 0)
         str += pszGlue;
      str += element_at(i).get_string();
   }
   return str;
}

index var_array::find_first(const char * psz, index find, index last) const
{
   if(find < 0)
      find += get_count();
   if(last < 0)
      last += get_count();
   for(; find < get_count(); find++)
   {
      if(element_at(find).get_string() == psz)
         return find;
   }
   return -1;
}

index var_array::find_first_ci(const char * psz, index find, index last) const
{
   if(find < 0)
      find += get_count();
   if(last < 0)
      last += get_count();
   for(; find < get_count(); find++)
   {
      if(element_at(find).get_string().CompareNoCase(psz) == 0)
         return find;
   }
   return -1;
}


index var_array::find_first(const var & var, index find, index last) const
{
   if(find < 0)
      find += get_count();
   if(last < 0)
      last += get_count();
   for(; find < get_count(); find++)
   {
      if(element_at(find) == var)
         return find;
   }
   return -1;
}

bool var_array::contains_ci(const char * lpcsz, index find, index last, count countMin, count countMax) const
{
   count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_first_ci(lpcsz, find, last)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}

bool var_array::contains(const char * lpcsz, index find, index last, count countMin, count countMax) const
{
   count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_first(lpcsz, find, last)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}

bool var_array::contains(const var & var, index find, index last, count countMin, count countMax) const
{
   count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_first(var, find, last)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}

count var_array::remove_first_ci(const char * lpcsz, index find, index last)
{
   if((find = find_first_ci(lpcsz, find, last)) >= 0)
      remove_at(find);
   return find;
}

count var_array::remove_first(const char * lpcsz, index find, index last)
{
   if((find = find_first(lpcsz, find, last)) >= 0)
      remove_at(find);
   return find;
}

count var_array::remove_first(const var & var, index find, index last)
{
   if((find = find_first(var, find, last)) >= 0)
      remove_at(find);
   return find;
}


count var_array::remove_ci(const char * lpcsz, index find, index last, count countMin, count countMax)
{
   count count = 0;
   if(contains_ci(lpcsz, find, last, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax)
         && (find = remove_first_ci(lpcsz, find, last)) >= 0)
         count++;
   return count;
}


count var_array::remove(const char * lpcsz, index find, index last, count countMin, count countMax)
{
   count count = 0;
   if(contains(lpcsz, find, last, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax)
         && (find = remove_first(lpcsz, find, last)) >= 0)
         count++;
   return count;
}


count var_array::remove(const var & var, index find, index last, count countMin, count countMax)
{
   count count = 0;
   if(contains(var, find, last, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax)
         && (find = remove_first(var, find, last)) >= 0)
         count++;
   return count;
}

count var_array::remove(const var_array & vara)
{
   if(&vara == this)
   {
      return remove_all();
   }
   else
   {
      count count = 0;
      for(index i = 0; i < vara.get_count(); i++)
      {
         count += remove(vara[i]);
      }
      return count;
   }
}

var_array & var_array::operator -=(var var)
{
   remove(var);
   return *this;
}

var_array & var_array::operator -=(var_array vara)
{
   remove(vara);
   return *this;
}

var_array var_array::operator -(var var) const
{
   var_array vara(*this);
   vara.remove(var);
   return vara;
}

var_array var_array::operator -(var_array varaParam) const
{
   var_array vara(*this);
   vara.remove(varaParam);
   return vara;
}

var_array & var_array::operator +=(var var)
{
   add(var);
   return *this;
}

var_array & var_array::operator +=(var_array vara)
{
   add(vara);
   return *this;
}

var_array var_array::operator +(var var) const
{
   var_array vara(*this);
   vara.add(var);
   return vara;
}

var_array var_array::operator +(var_array varaParam) const
{
   var_array vara(*this);
   vara.add(varaParam);
   return vara;
}

var_array & var_array::operator = (const stringa & stra)
{
   remove_all();
   for(int i = 0; i < stra.get_count(); i++)
   {
      add(stra[i]);
   }
   return *this;
}

var_array & var_array::operator = (const int_array & inta)
{
   remove_all();
   for(int i = 0; i < inta.get_count(); i++)
   {
      add(inta[i]);
   }
   return *this;
}

var_array & var_array::operator = (const gen::property_set & propset)
{
   remove_all();
   for(int i = 0; i < propset.m_propertya.get_count(); i++)
   {
      add(propset.m_propertya[i]);
   }
   return *this;
}

var_array & var_array::operator = (const var_array & vara)
{
   if(this != &vara)
   {
      remove_all();
      for(int i = 0; i < vara.get_count(); i++)
      {
         add(vara[i]);
      }
   }
   return *this;
}
