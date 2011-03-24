#include "StdAfx.h"

void NESSIEinit(struct NESSIEstruct * const structpointer);
void NESSIEadd(const unsigned char * const source, unsigned long sourceBits, struct NESSIEstruct * const structpointer);
void NESSIEfinalize(struct NESSIEstruct * const structpointer, unsigned char * const result);


namespace ca4
{

   file::file()
   {
      m_path.m_pfile = this;
   }

   file::path & file::path36()
   {
      return m_path;
   }

   bool file::path::rename(const char *pszNew, const char *psz)
   {
      string strDir = System.dir().name(psz);
      string strDirNew = System.dir().name(pszNew);
      if(strDir == strDirNew)
      {
         string strOld = System.file().name_(psz);
      }
      throw not_implemented_exception();
      //if(!System.file_as_string().move(psz, pszNew))
      {
         gen::property_set propertyset;
         System.message_box("err\\::fontopus::user\\file_system\\could_not_rename_file.xml", propertyset);
         return false;
      }
      return true;
   }

   string file::md5(const char * psz)
   {
      ex1::filesp spfile(get_app());
      try
      {
         if(!spfile->open(psz, ::ex1::file::type_binary | ::ex1::file::mode_read))
            return "";
      }
      catch(ex1::file_exception * pe)
      {
         gen::del(pe);
         return "";
      }
      int iBufSize = 1024 * 256;
      unsigned char * buf = new unsigned char[iBufSize];
      MD5_CTX ctx;
      MD5_Init(&ctx);
      int iRead;
      while((iRead = spfile->read(buf, iBufSize)) > 0)
      {
         MD5_Update(&ctx, buf, iRead);
      }
      MD5_Final(buf,&ctx);
      string str;
      string strFormat;
      for(int i = 0; i < 16; i++)
      {
         strFormat.Format("%02x", buf[i]);
         str += strFormat;
      }
      delete [] buf;
      return str;
   }


   void file::dtf(const char * pszFile, const char * pszDir)
   {
      stringa stra;
      stringa straRelative;
      System.dir().rls(pszDir, &stra, NULL, &straRelative);
      dtf(pszFile, stra, straRelative);
   }

   void file::dtf(const char * pszFile, stringa & stra, stringa & straRelative)
   {
      ex1::filesp spfile(get_app());
      if(!spfile->open(pszFile, ::ex1::file::mode_create | ::ex1::file::mode_write  | ::ex1::file::type_binary))
         throw "failed";
      string strVersion;
      strVersion = "fileset v1";
         MD5_CTX ctx;
      write_ex1_string(spfile, NULL, strVersion);
         ex1::filesp file2(get_app());
         int iBufSize = 1024 * 1024;
         int uiRead;
      unsigned char * buf = (unsigned char *)  malloc(iBufSize);
      string strMd5 = "01234567012345670123456701234567";
      int iPos;
      for(int i = 0; i < stra.get_size(); i++)
      {
         if(gen::str::ends_ci(stra[i], ".zip"))
         {
         }
         else if(System.dir().is(stra[i]))
            continue;
         write_n_number(spfile, NULL, 1);
         iPos = spfile->GetPosition();
         write_ex1_string(spfile, NULL, strMd5);
         MD5_Init(&ctx);
         write_ex1_string(spfile, &ctx, straRelative[i]);
         if(!file2->open(stra[i], ::ex1::file::mode_read | ::ex1::file::type_binary))
            throw "failed";
         write_n_number(spfile, &ctx, file2->get_length());
         while((uiRead = file2->read(buf, iBufSize)) > 0)
         {
            spfile->write(buf, uiRead);
            MD5_Update(&ctx, buf, uiRead);
         }
         spfile->seek(iPos, ::ex1::seek_begin);
         MD5_Final(buf,&ctx);
         strMd5.Empty();
         string strFormat;
         for(int i = 0; i < 16; i++)
         {
            strFormat.Format("%02x", buf[i]);
            strMd5 += strFormat;
         }
         write_ex1_string(spfile, NULL, strMd5);
         spfile->seek_to_end();

      }
      write_n_number(spfile, NULL, 2);
   }

   void file::ftd(const char * pszDir, const char * pszFile)
   {
      string strVersion;
      ex1::filesp spfile(get_app());
      if(!spfile->open(pszFile,  ::ex1::file::mode_read  | ::ex1::file::type_binary))
         throw "failed";
      read_ex1_string(spfile, NULL, strVersion);
      int n;
      string strRelative;
      string strMd5;
      string strMd5New;
      int iBufSize = 1024 * 1024;
      unsigned char * buf = (unsigned char *)  malloc(iBufSize);
      int iLen;
      MD5_CTX ctx;
      ex1::filesp file2(get_app());
      UINT uiRead;
      if(strVersion == "fileset v1")
      {
         while(true)
         {
            read_n_number(spfile, NULL, n);
            if(n == 2)
               break;
            read_ex1_string(spfile, NULL, strMd5);
            MD5_Init(&ctx);
            read_ex1_string(spfile, &ctx, strRelative);
            string strPath = System.dir().path(pszDir, strRelative);
            System.dir().mk(System.dir().name(strPath));
            if(!file2->open(strPath, ::ex1::file::mode_create | ::ex1::file::type_binary | ::ex1::file::mode_write))
               throw "failed";
            read_n_number(spfile, &ctx, iLen);
            while(iLen > 0)
            {
             uiRead = spfile->read(buf, min(iBufSize, iLen ));
             if(uiRead == 0)
                break;
               file2->write(buf, uiRead);
               MD5_Update(&ctx, buf, uiRead);
               iLen -= uiRead;
            }
            file2->close();
            MD5_Final(buf,&ctx);
            strMd5New.Empty();
            string strFormat;
            for(int i = 0; i < 16; i++)
            {
               strFormat.Format("%02x", buf[i]);
               strMd5New += strFormat;
            }
            if(strMd5 != strMd5New)
               throw "failed";
         }
      }
   }

   void file::write_n_number(ex1::file * pfile, MD5_CTX  * pctx, int iNumber)
   {
      string str;
      str.Format("%dn", iNumber);
      pfile->write((const char *) str, str.get_length());
      if(pctx != NULL)
      {
         MD5_Update(pctx, (const char *) str, str.get_length());
      }
   }

   void file::read_n_number(ex1::file * pfile, MD5_CTX * pctx, int & iNumber)
   {
      UINT uiRead;
      string str;
      char ch;
      while((uiRead = pfile->read(&ch, 1)) == 1)
      {
         if(ch >= '0' && ch <= '9')
            str += ch;
         else
            break;
         if(pctx != NULL)
         {
            MD5_Update(pctx, &ch, 1);
         }
      }
      if(ch != 'n')
         throw "failed";
      if(pctx != NULL)
      {
         MD5_Update(pctx, &ch, 1);
      }
      iNumber = atoi(str);
   }

   void file::write_ex1_string(ex1::file * pfile, MD5_CTX * pctx, string & str)
   {
      int iLen = str.get_length();
      write_n_number(pfile, pctx, iLen);
      pfile->write((const char *) str, str.get_length());
      if(pctx != NULL)
      {
         MD5_Update(pctx, (const char *) str, str.get_length());
      }
   }

   void file::read_ex1_string(ex1::file * pfile, MD5_CTX * pctx, string & str)
   {
      int iLen;
      read_n_number(pfile, pctx, iLen);
      LPTSTR lpsz = str.GetBufferSetLength(iLen + 1);
      pfile->read(lpsz, iLen);
      if(pctx != NULL)
      {
         MD5_Update(pctx, lpsz, iLen);
      }
      lpsz[iLen] = '\0';
      str.ReleaseBuffer();
   }


} // namespace ca36