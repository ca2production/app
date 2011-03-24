#include "StdAfx.h"

namespace mail
{

   tree_interface::tree_interface(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::user::scroll_view(papp),
      ::user::tree(papp),
      ex1::tree_data(papp),
      ex1::tree(papp),
      ::ca::data(papp),
      ::mail::tree_data(papp)
   {
      m_dataid = "mail::tree_interface";

      m_pdata = this;

      if(!ex1::tree_data::initialize())
         throw simple_exception();
   
   }

   bool tree_interface::initialize()
   {
      if(!::ex1::tree::initialize())
         return false;
      m_pdata = this;
      return true;
   }

   void tree_interface::update_list()
   {
   }


   tree_interface::~tree_interface()
   {
   }


} // namespace mail