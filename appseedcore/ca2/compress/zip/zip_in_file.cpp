#include "StdAfx.h"
#include "InFile.h"

namespace zip
{

   InFile::InFile(::ca::application * papp) :
      ca(papp)
   {
      m_bCloseOnDelete = true;
   }

   InFile::~InFile()
   {
      if(get_zip_file() != NULL && m_bCloseOnDelete)
         close();
   }


   ex1::file * InFile::Duplicate() const
   {
   //   ASSERT_VALID(this);
      ASSERT(get_zip_file() != NULL);

   /*   InFile* pFile = new InFile(hFileNull);
      HANDLE hFile;
      if (!::DuplicateHandle(::GetCurrentProcess(), (HANDLE)m_hFile,
         ::GetCurrentProcess(), &hFile, 0, FALSE, DUPLICATE_SAME_ACCESS))
      {
         delete pFile;
   //xxx      Ex1WinFileException::ThrowOsError((LONG)::GetLastError());
         throw 0;
      }
      pFile->m_hFile = (UINT)hFile;
      ASSERT(pFile->m_hFile != (UINT)hFileNull);
      pFile->m_bCloseOnDelete = m_bCloseOnDelete;*/
      return NULL;
      //return new ex1::filesp(this);
   }

   BOOL InFile::open(const char * lpszFileName, UINT, ex1::file_exception_sp *)
   { 
      m_filea.remove_all();
      m_izfilea.remove_all();
      m_straPath.remove_all();
      m_straPrefix.remove_all();

      string strFile;
      strFile = lpszFileName;

      int iFind = -1;
      int iStart = 0;
      while((iFind = gen::str::find_ci(".zip:", lpszFileName, iStart)) >= 0)
      {
         m_straPath.add(string(&lpszFileName[iStart], iFind + strlen(".zip")));
         iStart = iFind + strlen(".zip:");
      }
      if(gen::str::ends_ci(lpszFileName, ".zip"))
      {
         m_straPath.add(string(&lpszFileName[iStart]));
      }

      if(m_straPath.get_size() == 0)
         return FALSE;

      m_filea.add(new File(get_app()));
      if(!m_filea.last_element().open(m_straPath[0]))
         return false;

      string str;
      int i;
      for(i = 1; i < m_straPath.get_size(); i++)
      {
         m_izfilea.add(new InFile(get_app()));
         str = m_straPath[i];
         if(!m_izfilea.last_element().open(&m_filea.last_element(), str))
         {
            m_filea.remove_all();
            m_izfilea.remove_all();
            return FALSE;
         }
         m_filea.add(new File(get_app()));
         if(!m_filea.last_element().open(&m_izfilea.last_element()))
         {
            m_filea.remove_all();
            m_izfilea.remove_all();
            return FALSE;
         }
         m_straPrefix.add(m_straPath[i]);
      }
      if(gen::str::ends(strFile, ":"))
         return TRUE;
      iFind = strFile.reverse_find(L':');
      strFile = strFile.Mid(iFind + 1);
      gen::str::begins_eat(strFile, "/");
      gen::str::begins_eat(strFile, "\\");
      if(!locate(strFile))
      {
         if(!locate(strFile + "/"))
            return FALSE;
      }
      return TRUE;
   }


   bool InFile::locate(const char * pszFileName)
   {
      string strFile(pszFileName);
      int iFind = strFile.find(":");
      if(iFind >= 0)
         strFile = strFile.Left(iFind);
      strFile.replace("\\", "/");
      if(unzLocateFile(get_zip_file()->m_pf, strFile, 0) != UNZ_OK)
         return false;
      if(unzOpenCurrentFile(get_zip_file()->m_pf) != UNZ_OK)
         return false;
      if(unzGetCurrentFileInfo(get_zip_file()->m_pf,
                            &m_fi,
                            NULL,
                            0,
                            NULL,
                            0,
                            NULL,
                            0) != UNZ_OK)
         return false;

      m_iPosition = 0;
      m_strFileName = strFile;
      return true;
   }

   BOOL InFile::open(File * pzfile, const char * lpcszFileName)
   {
      ASSERT(AfxIsValidString(lpcszFileName));
      m_filea.add(pzfile);
      if(!locate(lpcszFileName))
         return FALSE;
      return TRUE;
   }


   bool InFile::dump(ex1::file * pfile)
   {
      if(m_strFileName.is_empty())
         return false;
      BYTE buf[1024];
      int iRead;
      while((iRead = read(buf, sizeof(buf))) > 0)
      {
         pfile->write(buf, iRead);
      }  
      return true;
   }

   DWORD_PTR InFile::read(void * lpBuf, DWORD_PTR nCount)
   {
   //   ASSERT_VALID(this);
      ASSERT(get_zip_file() != NULL);

      if (nCount == 0)
         return 0;   // avoid Win32 "null-read"

      ASSERT(lpBuf != NULL);
      ASSERT(fx_is_valid_address(lpBuf, nCount));

      DWORD_PTR iRead;
      iRead = unzReadCurrentFile(get_zip_file()->m_pf, lpBuf, nCount);
      m_iPosition += iRead;

      return (UINT)iRead;
   }

   void InFile::write(const void * lpBuf, DWORD_PTR nCount)
   {
      UNREFERENCED_PARAMETER(lpBuf);
      UNREFERENCED_PARAMETER(nCount);
      //ASSERT_VALID(this);
      ASSERT(get_zip_file() != NULL);

      ASSERT(FALSE);
   }

   INT_PTR InFile::seek(INT_PTR lOff, UINT nFrom)
   {
   //   ASSERT_VALID(this);
      ASSERT(get_zip_file() != NULL);
      ASSERT(nFrom == ::ex1::seek_begin || nFrom == ::ex1::seek_end || nFrom == ::ex1::seek_current);
      ASSERT(::ex1::seek_begin == FILE_BEGIN && ::ex1::seek_end == FILE_END && ::ex1::seek_current == FILE_CURRENT);
   /*typedef struct unz_file_pos_s
   {
       uLong pos_in_zip_directory;   /* offset in zip file directory */
     //  uLong num_of_file;            /* # of file */
   //} unz_file_pos;


      DWORD_PTR iNewPos;
      if(nFrom == ::ex1::seek_begin)
      {
         iNewPos = lOff;
      }
      else if(nFrom == ::ex1::seek_end)
      {
         iNewPos = m_fi.uncompressed_size - lOff;
      }
      else if(nFrom == ::ex1::seek_current)
      {
         iNewPos = m_iPosition + lOff;
      }
      else
      {
         ASSERT(FALSE);
      }

      if(iNewPos < m_iPosition)
      {
         if(unzCloseCurrentFile(get_zip_file()->m_pf) != UNZ_OK)
            return -1;
         if(unzOpenCurrentFile(get_zip_file()->m_pf) != UNZ_OK)
            return -1;
         m_iPosition = 0;
      }

      if(iNewPos > m_iPosition)
      {
         int iRemain = iNewPos - m_iPosition;
         int iGet;
         int iRead;
         BYTE lpbBuf[1024];
         while(iRemain > 0)
         {
            iGet = min(iRemain, 1024);
            iRead = unzReadCurrentFile(get_zip_file()->m_pf, lpbBuf, iGet);
            iRemain -= iRead;
            if(iRead < iGet)
               break;
         }
         iNewPos -= iRemain;
      }

      m_iPosition = iNewPos;

      return iNewPos;
   }

   DWORD_PTR InFile::GetPosition() const
   {
      return m_iPosition;
   }

   void InFile::Flush()
   {
   //   ASSERT_VALID(this);

   }

   void InFile::close()
   {
   //   ASSERT_VALID(this);
      //ASSERT(get_zip_file() != NULL);

      BOOL bError = FALSE;
      /*if(get_zip_file() != NULL)
      {
         unzCloseCurrentFile(get_zip_file()->m_pf);
      }*/

      m_filea.remove_all();
      m_izfilea.remove_all();
      m_straPath.remove_all();
      m_straPrefix.remove_all();
      m_bCloseOnDelete = false;
      m_strFileName.Empty();

      if (bError)
         throw 0;
   }

   void InFile::Abort()
   {
   }

   void InFile::LockRange(DWORD_PTR dwPos, DWORD_PTR dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void InFile::UnlockRange(DWORD_PTR dwPos, DWORD_PTR dwCount)
   {
      UNREFERENCED_PARAMETER(dwPos);
      UNREFERENCED_PARAMETER(dwCount);
   }

   void InFile::SetLength(DWORD_PTR dwNewLen)
   {
      UNREFERENCED_PARAMETER(dwNewLen);
   //   ASSERT_VALID(this);
      ASSERT(get_zip_file() != NULL);
      ASSERT(FALSE);
   }

   DWORD_PTR InFile::get_length() const
   {
      return m_fi.uncompressed_size;
   }

   // InFile does not support direct buffering (CMemFile does)
   DWORD_PTR InFile::GetBufferPtr(UINT nCommand, DWORD_PTR /*nCount*/, void ** /*ppBufStart*/, void ** /*ppBufMax*/)
   {
      ASSERT(nCommand == bufferCheck);
      UNUSED(nCommand);    // not used in retail build

      return 0;   // no support
   }



   /*/////////////////////////////////////////////////////////////////////////////
   // InFile implementation helpers

   #ifdef AfxGetFileName
   #undef AfxGetFileName
   #endif

   #ifndef _AFX_NO_OLE_SUPPORT

   HRESULT AFX_COM::CreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter,
      REFIID riid, LPVOID* ppv)
   {
      // find the object's class factory
      LPCLASSFACTORY pf = NULL;
      HRESULT hRes = GetClassObject(rclsid, IID_IClassFactory, (LPVOID*)&pf);
      if (FAILED(hRes))
         return hRes;

      // call it to create the instance
      ASSERT(pf != NULL);
      hRes = pf->CreateInstance(pUnkOuter, riid, ppv);

      // let go of the factory
      pf->Release();
      return hRes;
   }

   HRESULT AFX_COM::GetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
   {
      *ppv = NULL;
      HINSTANCE hInst = NULL;

      // find server name for this class ID

      string strCLSID = AfxStringFromCLSID(rclsid);
      string strServer;
      if (!AfxGetInProcServer(strCLSID, strServer))
         return REGDB_E_CLASSNOTREG;

      // try to load it
      hInst = LoadLibrary(strServer);
      if (hInst == NULL)
         return REGDB_E_CLASSNOTREG;

   #pragma warning(disable:4191)
      // get its entry point
      HRESULT (STDAPICALLTYPE* pfn)(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
      pfn = (HRESULT (STDAPICALLTYPE*)(REFCLSID rclsid, REFIID riid, LPVOID* ppv))
         GetProcAddress(hInst, "DllGetClassObject");
   #pragma warning(default:4191)

      // call it, if it worked
      if (pfn != NULL)
         return pfn(rclsid, riid, ppv);
      return CO_E_ERRORINDLL;
   }*/


   /////////////////////////////////////////////////////////////////////////////
   // InFile diagnostics

   #ifdef _DEBUG
   void InFile::assert_valid() const
   {
      //::radix::object::assert_valid();
      // we permit the descriptor m_hFile to be any value for derived classes
   }

   void InFile::dump(dump_context & dumpcontext) const
   {
   //   ::radix::object::dump(dumpcontext);

      dumpcontext << "with handle " << (UINT)get_zip_file();
      dumpcontext << " and name \"" << m_strFileName << "\"";
      dumpcontext << "\n";
   }
   #endif


   // IMPLEMENT_DYNAMIC(InFile, ::radix::object)


   /////////////////////////////////////////////////////////////////////////////
   // FileException helpers

   #ifdef _DEBUG
   static const char * rgszFileExceptionCause[] =
   {
      "none",
      "generic",
      "fileNotFound",
      "badPath",
      "tooManyOpenFiles",
      "accessDenied",
      "invalidFile",
      "removeCurrentDir",
      "directoryFull",
      "badSeek",
      "hardIO",
      "sharingViolation",
      "lockViolation",
      "diskFull",
      "endOfFile",
   };
   static const char szUnknown[] = "unknown";
   #endif


   /*void vfxThrowFileException(int cause, LONG lOsError,
   //   const wchar_t * lpszFileName /* == NULL */
   /*{
   #ifdef _DEBUG
      const char * lpsz;
      if (cause >= 0 && cause < _countof(rgszFileExceptionCause))
         lpsz = rgszFileExceptionCause[cause];
      else
         lpsz = szUnknown;
      TRACE3("InFile exception: %hs, InFile %W, App error information = %ld.\n",
         lpsz, (lpszFileName == NULL) ? L"Unknown" : lpszFileName, lOsError);
   #endif
      THROW(new FileException(cause, lOsError, lpszFileName));
   }*/

   /* Error Codes */

   #define EPERM           1
   #define ENOENT          2
   #define ESRCH           3
   #define EINTR           4
   #define EIO             5
   #define ENXIO           6
   #define E2BIG           7
   #define ENOEXEC         8
   #define EBADF           9
   #define ECHILD          10
   #define EAGAIN          11
   #define ENOMEM          12
   #define EACCES          13
   #define EFAULT          14
   #define EBUSY           16
   #define EEXIST          17
   #define EXDEV           18
   #define ENODEV          19
   #define ENOTDIR         20
   #define EISDIR          21
   #define EINVAL          22
   #define ENFILE          23
   #define EMFILE          24
   #define ENOTTY          25
   #define EFBIG           27
   #define ENOSPC          28
   #define ESPIPE          29
   #define EROFS           30
   #define EMLINK          31
   #define EPIPE           32
   #define EDOM            33
   #define ERANGE          34
   #define EDEADLK         36
   #define ENAMETOOLONG    38
   #define ENOLCK          39
   #define ENOSYS          40
   #define ENOTEMPTY       41
   #define EILSEQ          42

   /*
    * Support EDEADLOCK for compatibiity with older MS-C versions.
    */
   #define EDEADLOCK       EDEADLK




   bool InFile::IsOpened()
   {
      return get_zip_file() != NULL;
   }

   File * InFile::get_zip_file()
   {
      if(m_filea.get_count() <= 0)
         return NULL;
      else
         return &m_filea.last_element();
   }

   const File * InFile::get_zip_file() const
   { 
      if(m_filea.get_count() <= 0)
         return NULL;
      else
         return &m_filea.last_element();
   }

} // namespace zip
