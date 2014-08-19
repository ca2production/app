/* version: 1.0, Feb, 2003
   Author : Gao Dasheng
   Copyright (C) 1995-2002 Gao Dasheng(dsgao@hotmail.com)
   
  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
//////////////////////////////////////////////////////////////////////////////
  Introduce:
     This file includes two classes CA2GZIP and CGZIP2A which do compressing and 
    uncompressing in primitive::memory. and It 's very easy to use for small data compressing.
    Some compress and uncompress codes came from gzip  unzip function of zlib 1.1.x. 

  Usage: 
     these two classes work used with zlib 1.1.x (http://www.gzip.org/zlib/).
    They were tested in Window OS.
  Exmaple:
     #include "GZipHelper.h"
    void main()
    {
        char plainText[]="Plain text here";
      CA2GZIP gzip(plainText,strlen(plainText));  // do compressing here;
      LPGZIP pgzip=gzip.pgzip;  // pgzip is zipped data pointer, you can use it directly
      int32_t len=gzip.Length;      // Length is length of zipped data;

      CGZIP2A plain(pgzip,len);  // do decompressing here

      char *pplain=plain.psz;    // psz is plain data pointer
      int32_t  aLen=plain.Length;    // Length is length of unzipped data.
    }
//////////////////////////////////////////////////////////////////////////////
*/
#pragma once
#ifdef _ZLIB_LIBRARY
#define CLASS_DECL_ZLIB  _declspec(dllexport)
#else
#define CLASS_DECL_ZLIB  _declspec(dllimport)
#endif

class CLASS_DECL_ZLIB gzip_stream:
   virtual public ::file::output_stream
{
public:


   primitive::memory             m_memory;
   z_stream                      m_zstream;
   int32_t                       m_z_err;   /* error code for last stream operation */
   uint32_t                      m_crc;     /* crc32 of uncompressed data */


   gzip_stream(::file::stream_buffer *  pfileDest);
   gzip_stream(::file::output_stream & ostreamDest);
   virtual ~gzip_stream();

   using ::file::output_stream::write;
   virtual void write(const void * buf, ::primitive::memory_size iSize);
   void finish();

protected:
   
   
   void construct();
   int32_t _finish();
   int32_t destroy();
   void putLong (uint_ptr x);
   
   
};



