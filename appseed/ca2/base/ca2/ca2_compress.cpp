#include "framework.h"
#if defined(LINUX) || defined(MACOS) || defined(ANDROID)
#define _O_BINARY 0
#define _O_RDONLY O_RDONLY
#else
#include <io.h>
#endif
#include <wchar.h>
#include <fcntl.h>
#include <sys/stat.h>
#if !defined(LINUX) && !defined(MACOS) && !defined(ANDROID)
#include <share.h>
#endif

#ifdef WINDOWS
int32_t my_open(const char * psz, int32_t i)
{
   return _wopen(::str::international::utf8_to_unicode(psz), i);
}
FILE * my_fopen(const char * psz, const char * pszMode)
{
   return _wfopen(::str::international::utf8_to_unicode(psz), ::str::international::utf8_to_unicode(pszMode));
}
#else

void _get_errno(int32_t * perrno)
{
   *perrno = errno;
}

int32_t my_open(const char * psz, int32_t i)
{
   return open(psz, i);
}
FILE * my_fopen(const char * psz, const char * pszMode)
{
   return fopen(psz, pszMode);
}
#endif



namespace ca2
{

   bool compress::ungz(::file::writer & ostreamUncompressed, const char * lpcszGzFileCompressed)
   {
      int32_t fileUn = my_open(lpcszGzFileCompressed, _O_BINARY | _O_RDONLY);
      if (fileUn == -1)
      {
         TRACE("ungz wopen error %s", lpcszGzFileCompressed);
         return false;
      }
      gzFile file = gzdopen(fileUn, "rb");
      if (file == NULL)
      {
         TRACE("ungz gzopen error %s", lpcszGzFileCompressed);
         return false;
      }
      class primitive::memory memory;
      memory.allocate(1024 * 256);
      int_ptr uncomprLen;
      while((uncomprLen = gzread(file, memory, (uint32_t) memory.get_size())) > 0)
      {
         ostreamUncompressed.write(memory, uncomprLen);
      }
      gzclose(file);
      return true;
   }


   bool compress::ungz(::::file::memory_buffer & memoryfile)
   {

      int64_t dataLength = memoryfile.get_length();

      bool done = false;
      int32_t status;

      z_stream strm;
      strm.next_in = (byte *)memoryfile.get_data();
      strm.avail_in = (uint32_t)dataLength;
      strm.total_out = 0;
      strm.zalloc = Z_NULL;
      strm.zfree = Z_NULL;

      ::::file::memory_buffer memoryfileOut(get_app());
      class primitive::memory memory;
      memory.allocate(1024 * 256);
      ASSERT(memory.get_size() <= UINT_MAX);

      // inflateInit2 knows how to deal with gzip format
      if (inflateInit2(&strm, (15+32)) != Z_OK)
      {
	      return false;
      }

      while (!done)
      {

	      strm.next_out = memory.get_data();
	      strm.avail_out = (uint32_t) memory.get_size();

	      // Inflate another chunk.
	      status = inflate (&strm, Z_SYNC_FLUSH);

         memoryfileOut.write(memory.get_data(), memory.get_size() - strm.avail_out);

	      if (status == Z_STREAM_END)
	      {
		      done = true;
	      }
	      else if (status != Z_OK)
	      {
		      break;
	      }
      }

      memoryfile.FullLoad(memoryfileOut);

      if (inflateEnd (&strm) != Z_OK || !done)
      {
	      return true;
      }

      return true;

   }


   bool compress::gz(::file::writer & ostreamCompressed, const char * lpcszUncompressed)
   {
      string str(lpcszUncompressed);
      FILE * fileUn = my_fopen(lpcszUncompressed, "rb");
      if (fileUn == NULL)
      {
         int32_t err;
         _get_errno(&err);
         fprintf(stderr, "gz fopen error %d %s", err, lpcszUncompressed);
         return false;
      }
      gzip gz(ostreamCompressed);
      class primitive::memory memory;
      memory.allocate(1024 * 256);
      ::primitive::memory_size uncomprLen;
      while((uncomprLen = (::primitive::memory_size) fread(memory, 1, (size_t) memory.get_size(), fileUn)) > 0)
      {
         gz.write(memory, uncomprLen);
      }
      fclose(fileUn);
      gz.finish();
      return true;
   }

   bool compress::null(::file::writer & ostream, ::file::reader & istream)
   {
      class primitive::memory memory;
      memory.allocate(1024 * 256);
      ::primitive::memory_size  uiRead;
      while((uiRead = istream.read(memory, memory.get_size())) > 0)
      {
         ostream.write(memory, uiRead);
      }
      return true;
   }

   bool compress::ungz(sp(base_application) papp, const char * lpcszUncompressed, const char * lpcszGzFileCompressed)
   {
      return System.file().output(papp, lpcszUncompressed, this, &compress::ungz, lpcszGzFileCompressed);
   }

   bool compress::gz(sp(base_application) papp, const char * lpcszGzFileCompressed, const char * lpcszUncompressed)
   {
      return System.file().output(papp, lpcszGzFileCompressed, this, &compress::gz, lpcszUncompressed);
   }

   bool compress::unbz(::file::writer & ostreamUncompressed, const char * lpcszBzFileCompressed)
   {
      BZFILE * file = BZ2_bzopen(lpcszBzFileCompressed, "rb");
      if (file == NULL)
      {
         TRACE("unbz bzopen error %s", lpcszBzFileCompressed);
         return false;
      }
      primitive::memory memory;
      memory.allocate(1024 * 16 * 1024);
      int32_t uncomprLen;
      while((uncomprLen = BZ2_bzread(file, memory, (int32_t) memory.get_size())) > 0)
      {
         ostreamUncompressed.write(memory, uncomprLen);
      }
      BZ2_bzclose(file);
      return true;
   }

   bool compress::bz(::file::writer & ostreamBzFileCompressed, const char * lpcszUncompressed)
   {
      ::file::binary_buffer_sp file = Application.file().get_file(lpcszUncompressed, ::file::mode_read | ::file::type_binary);
      if(file.is_null())
      {
         return false;
      }
      return bz_stream(ostreamBzFileCompressed, file);
   }

   bool compress::bz_stream(::file::writer & ostreamBzFileCompressed, ::file::reader & istreamFileUncompressed)
   {
      bzip bz(ostreamBzFileCompressed);
      class primitive::memory memory;
      memory.allocate(1024 * 256);
      ::primitive::memory_size uncomprLen;
      while((uncomprLen = istreamFileUncompressed.read(memory, memory.get_size())) > 0)
      {
         bz.write(memory, uncomprLen);
      }
      bz.finish();
      return true;
   }

   bool compress::unbz(sp(base_application) papp, const char * lpcszUncompressed, const char * lpcszGzFileCompressed)
   {
      return System.file().output(papp, lpcszUncompressed, this, &compress::unbz, lpcszGzFileCompressed);
   }

   bool compress::bz(sp(base_application) papp, const char * lpcszGzFileCompressed, const char * lpcszUncompressed)
   {
      return System.file().output(papp, lpcszGzFileCompressed, this, &compress::bz, lpcszUncompressed);
   }

   bool compress::_compress(class primitive::memory & memory, void * pdata, ::primitive::memory_size ulSize)
   {
      memory.allocate(compressBound((uLong) ulSize) * 2);
      uLongf ulDestSize = (uLongf) memory.get_size();
      int32_t i = ::compress(memory.get_data(), &ulDestSize, (BYTE *) pdata, (uLongf) ulSize);
      memory.allocate(ulDestSize);
      return i == Z_OK;
   }

   bool compress::_uncompress(primitive::memory & memoryUncompressed, primitive::memory & memoryCompressed, ::primitive::memory_size sizeUncompressed)
   {
      memoryUncompressed.allocate(sizeUncompressed);
      uLongf ulSizeUncompressed =(uLongf) sizeUncompressed;
      int32_t i = ::uncompress(memoryUncompressed.get_data(), &ulSizeUncompressed, memoryCompressed.get_data(), (uLong) memoryCompressed.get_size());
      return i == Z_OK;
   }


   void compress::extract_all(const char * pszFile, sp(base_application) papp)
   {
      string strDir = pszFile;
      ::str::ends_eat_ci(strDir, ".zip");
      App(papp).file().copy(strDir, pszFile, false);
   }

   void compress::zip(const char * pszZip, const char * psz, sp(base_application) papp)
   {
      zip::InFile infile(papp);

      if(!infile.zip_open(pszZip, 0))
      {
         throw "Could not open zip file";
         return;
      }

      if(System.dir().is(psz, papp))
      {
         stringa straPath;
         stringa straRelative;
         string strPath;
         ::file::binary_buffer_sp file;
         System.dir().rls(papp, psz, &straPath, NULL, &straRelative);
         for(int32_t i = 0; i < straPath.get_size(); i++)
         {
            strPath = straPath[i];
            if(!System.dir().is(strPath, papp))
            {
               infile.add_file(psz, straRelative[i]);

            }
         }
      }

   }

   void compress::zip(const char * psz, sp(base_application) papp)
   {
   }

} // namespace ca2
