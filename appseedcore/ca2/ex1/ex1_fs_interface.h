#pragma once


namespace ex1
{

   class CLASS_DECL_ca fs_interface
   {
   public:
      virtual void ls_dir(const char * pszPath, stringa & straName);
      virtual void ls_file(const char * pszPath, stringa & straName);
      virtual void query_info(string & straInfo);
      virtual void query_default_info(string & straInfo);
      virtual bool get_info(const char * pszPath, const char * pszInfo, var & varInfo);
   };

} // namespace ex1