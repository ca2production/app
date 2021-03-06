#pragma once


namespace zip
{

   class Util;

}


namespace file
{


   namespace dir
   {


      namespace axis
      {


         class CLASS_DECL_AXIS application:
            virtual public ::file::dir::application
         {
         public:


            application(::aura::application * papp);
            virtual ~application();


            //virtual string locale_schema(const char * pszLocale = NULL,const char * pszStyle = NULL);
            //virtual stringa locale_schema_matter(const char * pszLocale = NULL,const char * pszStyle = NULL,const char * pszRoot = NULL,const char * pszApp = NULL);
            //virtual string matter(const string & str,bool bDir = false,const char * pszRoot = NULL,const char * pszApp = NULL);
            //virtual string matter(const string & str,const string & str2,bool bDir = false,const char * pszRoot = NULL,const char * pszApp = NULL);
            //virtual string matter(const string & str,const char * psz,bool bDir = false,const char * pszRoot = NULL,const char * pszApp = NULL);
            //virtual string matter(const char * psz,const string & str,bool bDir = false,const char * pszRoot = NULL,const char * pszApp = NULL);
            //virtual string matter(const char * lpcsz = NULL,const char * lpcsz2 = NULL,bool bDir = false,const char * pszRoot = NULL,const char * pszApp = NULL);
            //virtual string matter(const stringa & stra,bool bDir = false,const char * pszRoot = NULL,const char * pszApp = NULL);

            //virtual void   matter_ls(const string & str,stringa & stra);
            virtual ::file::path matter_file(const ::file::path & path,bool bDir = false);
            //virtual void   matter_ls_file(const string & str,stringa & stra);

            //virtual string usersystemappdata(const char * lpcszPrefix,const char * lpcsz = NULL,const char * lpcsz2 = NULL);
            //virtual string userappdata(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
            //virtual string userdata(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
            //virtual string userfolder(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
            //virtual string default_os_user_path_prefix();
            //virtual string default_userappdata(const char * lpcszPrefix,const char * lpcszLogin,const char * pszRelativePath = NULL);
            //virtual string default_userdata(const char * lpcszPrefix,const char * lpcszLogin,const char * pszRelativePath = NULL);
            //virtual string default_userfolder(const char * lpcszPrefix,const char * lpcszLogin,const char * pszRelativePath = NULL);
            //virtual string userquicklaunch(const char * pszRelativePath = NULL,const char * lpcsz2 = NULL);
            //virtual string userprograms(const char * pszRelativePath = NULL,const char * lpcsz2 = NULL);




            //virtual bool  is(const char * lpcsz);
            //virtual bool  is(const string & str);
            //virtual bool  is(const var & var);
            //virtual bool  is_inside(const char * lpcszDir,const char * lpcszPath);
            //virtual bool  is_inside_time(const char * lpcsz);
            //virtual bool  has_subdir(const char * lpcsz);


            //virtual void  root_ones(stringa & patha,stringa & straTitle);
            //virtual bool  mk(const char * lpcsz);
            //virtual bool  rm(const char * psz,bool bRecursive = true);


            //virtual string pathfind(const char * pszEnv,const char * pszTopic,const char * pszMode);


         };


      } // namespace axis


   } // namespace dir


} // namespace file










































