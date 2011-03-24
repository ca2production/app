#include "StdAfx.h"

namespace xml
{

   application::application()
   {
      
      m_poptionDefault     = NULL;
      m_pparseinfoDefault  = NULL;

      m_entities.add_entity('&'    , "&amp;" );
      m_entities.add_entity('\"'   , "&quot;");
      m_entities.add_entity('\''   , "&apos;");
      m_entities.add_entity('<'    , "&lt;");
      m_entities.add_entity('>'    , "&gt;");

   }

   application::~application()
   {
   }

   bool application::initialize1()
   {

      if(!::ex2::application::initialize1())
         return false;

      m_poptionDefault     = new disp_option(this);
      m_pparseinfoDefault  = new parse_info(this);

      return true;
   }

   bool application::initialize()
   {

      if(!::ex2::application::initialize())
         return false;

      return true;
   }


} //namespace xml