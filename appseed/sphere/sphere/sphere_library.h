#pragma once


namespace sphere
{


   class CLASS_DECL_SPHERE library :
      virtual public ::aura::single_application_library < application >,
      virtual public ::filehandler::menu_library
   {
   public:


      library(::aura::application * papp);
      

      virtual void get_app_list(stringa & stra);

      virtual void get_extension_list(stringa & stra);

      virtual void get_extension_app(stringa & straApp, const char * pszExtension);

//      virtual sp(::aura::application) get_new_app(const char * pszAppId);


   };


} // namespace sphere



