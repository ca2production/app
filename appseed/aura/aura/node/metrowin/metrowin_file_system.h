#pragma once


//CLASS_DECL_AXIS bool vfxFullPath(wchar_t * lpszPathOut, const wchar_t * lpszFileIn);
//CLASS_DECL_AXIS bool vfxFullPath(wstring & wstrFullPath, const wstring & wstrPath);
//CLASS_DECL_AXIS UINT vfxGetFileName(const wchar_t * lpszPathName, wchar_t * lpszTitle, UINT nMax);
//CLASS_DECL_AXIS void vfxGetModuleShortFileName(HINSTANCE hInst, string & strShortName);
//CLASS_DECL_AXIS void vfxGetModuleShortFileName(HINSTANCE hInst, string& strShortName);


namespace metrowin
{


   class CLASS_DECL_AURA file_system :
      virtual public ::file::system
   {
   public:
      
      
      file_system(::aura::application *  papp);
      virtual ~file_system();


      virtual bool FullPath(string & str, const char * lpszFileIn);
      virtual bool FullPath(wstring & wstrFullPath, const wstring & wstrPath);
      virtual UINT GetFileName(const char * lpszPathName, string & str);
      virtual void GetModuleShortFileName(HINSTANCE hInst, string & strShortName);

      virtual var length(const char * pszPath);

   };


} // namespace metrowin


