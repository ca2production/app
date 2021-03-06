#pragma once


namespace ios
{
   
   
   namespace axis
   {
      
      
      class CLASS_DECL_AXIS dir :
         virtual public ::file::dir::axis::system,
         virtual ::ios::dir
      {
      public:
         
         
         //      dir(::aura::application *   papp);
         //
         //
         //      virtual void  ls_pattern(::aura::application *   papp, const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, bool_array * pbaIsDir = NULL, int64_array * piaSize = NULL);
         //      virtual void  ls(::aura::application *   papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, bool_array * pbaIsDir = NULL, int64_array * piaSize = NULL);
         //      virtual void  rls_pattern(::aura::application *   papp, const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, bool_array * pbaIsDir = NULL, int64_array * piaSize = NULL, e_extract eextract = extract_first);
         //      virtual void  rls(::aura::application *   papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, e_extract eextract = extract_first);
         //      virtual void  rls_dir(::aura::application *   papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL);
         //      virtual void  ls_dir(::aura::application *   papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);
         //      virtual bool  has_subdir(::aura::application *   papp, const char * lpcsz);
         //      virtual void  ls_file(::aura::application *   papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);
         //      virtual bool  is(const char * lpcsz, ::aura::application *   papp);
         //      virtual bool  is(const string & str, ::aura::application *   papp);
         //      virtual bool  name_is(const string & str, ::aura::application *   papp);
         //      virtual bool  is_inside(const char * lpcszDir, const char * lpcszPath, ::aura::application *   papp);
         //      virtual bool  is_inside_time(const char * lpcsz, ::aura::application *   papp);
         //      virtual void root_ones(stringa & stra, stringa & straTitle, ::aura::application *   papp);
         //      virtual bool mk(const char * lpcsz, ::aura::application *   papp);
         //      virtual bool rm(::aura::application *   papp, const char * psz, bool bRecursive = true);
         //
         //
         //      virtual string name(const char * lpcsz);
         //      virtual string name(const string & str);
         //
         //      virtual string votagus(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         //      virtual string time(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         //      virtual string stage(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         //      virtual string stageapp(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         //      virtual string netseed(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         //
         //      // stage in ccvotagus spalib
         //      virtual string element(const char * lpcsz, const char * lpcsz2 = NULL);
         //      virtual string element();
         //      virtual string element(const string & str);
         //      virtual string element(const string & str, const string & str2);
         //      virtual string element(const char * lpcsz, const string & str2);
         //      virtual string element(const string & str, const char * lpcsz2);
         //
         //      virtual string module(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         //      virtual string ca2module(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         //      virtual void time_square(string &str);
         //      virtual string time_log(const char * pszId);
         //
         //
         //      virtual string trash_that_is_not_trash(const char * psz);
         //
         //      virtual string appdata(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         //      virtual string commonappdata(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         //
         //      virtual string usersystemappdata(::aura::application *   papp, const char * lpcszPrefix, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         //      virtual string userappdata(::aura::application *   papp, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         //      virtual string userdata(::aura::application *   papp, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         //      virtual string userfolder(::aura::application *   papp, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         //      virtual string default_os_user_path_prefix(::aura::application *   papp);
         //      virtual string default_userappdata(::aura::application *   papp, const char * lpcszPrefix, const char * lpcszLogin , const char * pszRelativePath = NULL);
         //      virtual string default_userdata(::aura::application *   papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = NULL);
         //      virtual string default_userfolder(::aura::application *   papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = NULL);
         //      virtual string userquicklaunch(::aura::application *   papp, const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);
         //      virtual string userprograms(::aura::application *   papp, const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);
         //
         //      virtual string commonprograms(const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);
         //
         //      virtual bool initialize();
         //   protected:
         //      class path     m_path;
         //      string         m_strTimeFolder;
         //      string         m_strNetSeedFolder;
         
         
         dir(::aura::application * papp);
         
         
         //virtual string relpath(const char * lpcszSource,const char * lpcszRelative,const char * lpcsz2 = NULL);
         virtual ::file::listing & ls(::aura::application * papp, ::file::listing & ls);
         
         //virtual bool  is(const char * lpcsz,::aura::application * papp);
         virtual bool  is(const ::file::path & str,::aura::application * papp);
         virtual bool  name_is(const ::file::path & str,::aura::application * papp);
         //virtual bool  is_inside(const char * lpcszDir,const char * lpcszPath,::aura::application * papp);
         //virtual bool  is_inside_time(const char * lpcsz,::aura::application * papp);
         //virtual void root_ones(stringa & patha,stringa & straTitle,::aura::application * papp);
         //virtual bool mk(const char * lpcsz,::aura::application * papp);
         //virtual bool rm(::aura::application * papp,const char * psz,bool bRecursive = true);
         
         
         //virtual string name(const char * lpcsz);
         //virtual string name(const string & str);
         
         //virtual string time(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
         //virtual string stage(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
         //virtual string stageapp(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
         //virtual string netseed(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
         
         //// stage in ca2os spalib
         //virtual string element(const char * lpcsz,const char * lpcsz2 = NULL);
         //virtual string element();
         //virtual string element(const string & str);
         //virtual string element(const string & str,const string & str2);
         //virtual string element(const char * lpcsz,const string & str2);
         //virtual string element(const string & str,const char * lpcsz2);
         
         //virtual string module(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
         //virtual string ca2module(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
         //virtual void time_square(string &str);
         //virtual string time_log(const char * pszId);
         
         
         //virtual string trash_that_is_not_trash(const char * psz);
         
         //virtual string appdata(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
         //virtual string commonappdata(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
         //virtual string element_commonappdata(const string & strElement,const char * lpcsz = NULL,const char * lpcsz2 = NULL);
         
         //virtual string usersystemappdata(::aura::application * papp,const char * lpcszPrefix,const char * lpcsz = NULL,const char * lpcsz2 = NULL);
         //virtual string userappdata(::aura::application * papp,const char * lpcsz = NULL,const char * lpcsz2 = NULL);
         //virtual string userdata(::aura::application * papp,const char * lpcsz = NULL,const char * lpcsz2 = NULL);
         //virtual string userfolder(::aura::application * papp,const char * lpcsz = NULL,const char * lpcsz2 = NULL);
         //virtual string default_os_user_path_prefix(::aura::application * papp);
         //virtual string default_userappdata(::aura::application * papp,const string & lpcszPrefix,const string & lpcszLogin,const char * pszRelativePath = NULL);
         //virtual string default_userdata(::aura::application * papp,const string & lpcszPrefix,const string & lpcszLogin,const char * pszRelativePath = NULL);
         //virtual string default_userfolder(::aura::application * papp,const string & lpcszPrefix,const string & lpcszLogin,const char * pszRelativePath = NULL);
         //virtual string userquicklaunch(::aura::application * papp,const char * pszRelativePath = NULL,const char * lpcsz2 = NULL);
         //virtual string userprograms(::aura::application * papp,const char * pszRelativePath = NULL,const char * lpcsz2 = NULL);
         
         //virtual string commonprograms(const char * pszRelativePath = NULL,const char * lpcsz2 = NULL);
         
         virtual bool initialize();
         
         
      };
      
      
   } // namespace axis
   
   
} // namespace ios


