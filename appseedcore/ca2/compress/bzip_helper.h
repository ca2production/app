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
      int len=gzip.Length;      // Length is length of zipped data;

      CGZIP2A plain(pgzip,len);  // do decompressing here

      char *pplain=plain.psz;    // psz is plain data pointer
      int  aLen=plain.Length;    // Length is length of unzipped data.
    }
//////////////////////////////////////////////////////////////////////////////
*/


#pragma once


class bzip
{
public:
   ex1::output_stream * m_postream;
   primitive::memory m_memory;
   int m_CurrentBufferSize;
   bz_stream m_zstream;
   int      m_z_err;   /* error code for last stream operation */
   //byte     *m_outbuf; /* output buffer */
   uLong    m_crc;     /* crc32 of uncompressed data */


   bzip(ex1::file * pfileDest);
   bzip(ex1::output_stream & ostreamDest);
   virtual ~bzip();

   bool write(void * buf, int iSize);
   void finish();

protected:
   void construct();
};

/*
template< int t_nBufferLength = 1024>
class CGZIP2AT
{
  public:
   char *psz;
   int  Length;
   CGZIP2AT(LPGZIP pgzip,int len):m_gzip(pgzip),m_gziplen(len),psz(0),Length(0),m_pos(0)
  {
    Init(); 
  }
  ~CGZIP2AT()
  {
    if(psz!=m_buffer) TRYFREE(psz);  
  }
  void Init()
  {
   if(m_gzip==0)
   {
     psz=0; 
     Length=0;
     return ;
   }
   m_CurrentBufferSize=t_nBufferLength;
   psz=m_buffer;
   memset(psz,0,m_CurrentBufferSize+1);

   m_zstream.zalloc = (alloc_func)0;
    m_zstream.zfree = (free_func)0;
    m_zstream.opaque = (voidpf)0;
    m_zstream.next_in = m_inbuf = Z_NULL;
    m_zstream.next_out = Z_NULL;
    m_zstream.avail_in = m_zstream.avail_out = 0;
    m_z_err = Z_OK;
   m_z_eof = 0;
   m_transparent = 0;
    m_crc = crc32(0L, Z_NULL, 0);
    
   m_zstream.next_in  =m_inbuf = (byte*)ALLOC(Z_BUFSIZE);
    int  err = inflateInit2(&(m_zstream), -MAX_WBITS);
   if (err != Z_OK || m_inbuf == Z_NULL)
   {
     destroy();
     return;
    }
    m_zstream.avail_out = Z_BUFSIZE;
   check_header();
   char outbuf[Z_BUFSIZE];
   int nRead;
   while(true)
   {
     nRead=gzread(outbuf,Z_BUFSIZE);
     if(nRead<=0) break;
     write(outbuf,nRead);
   }
   destroy();
  }
  private:
   char m_buffer[t_nBufferLength+1];
   int m_CurrentBufferSize;
   z_stream m_zstream;
   int      m_z_err;   /* error code for last stream operation */
   /*byte     *m_inbuf; /* output buffer */
   /*uLong    m_crc;     /* crc32 of uncompressed data */
   /*int      m_z_eof;
   int      m_transparent;

   int      m_pos;
   LPGZIP   m_gzip;
   int      m_gziplen;
   
  void check_header()
  {
    int method; /* method byte */
    /*int flags;  /* flags byte */
    /*uInt len;
    int c;

    /* Check the gzip magic header */
    /*for (len = 0; len < 2; len++) {
   c = get_byte();
   if (c != gz_magic[len]) {
       if (len != 0) m_zstream.avail_in++, m_zstream.next_in--;
       if (c != EOF) {
      m_zstream.avail_in++, m_zstream.next_in--;
      m_transparent = 1;
       }
       m_z_err =m_zstream.avail_in != 0 ? Z_OK : Z_STREAM_END;
       return;
   }
    }
    method = get_byte();
    flags = get_byte();
    if (method != Z_DEFLATED || (flags & RESERVED) != 0) {
   m_z_err = Z_DATA_ERROR;
   return;
    }
    /* Discard time, xflags and OS code: */
    /*for (len = 0; len < 6; len++) (void)get_byte();

    if ((flags & EXTRA_FIELD) != 0) { /* skip the extra field */
   /*len  =  (uInt)get_byte();
   len += ((uInt)get_byte())<<8;
   /* len is garbage if EOF but the loop below will quit anyway */
   /*while (len-- != 0 && get_byte() != EOF) ;
    }
    if ((flags & ORIG_NAME) != 0) { /* skip the original file name */
   /*while ((c = get_byte()) != 0 && c != EOF) ;
    }
    if ((flags & COMMENT) != 0) {   /* skip the .gz file comment */
   /*while ((c = get_byte()) != 0 && c != EOF) ;
    }
    if ((flags & HEAD_CRC) != 0) {  /* skip the header crc */
   /*for (len = 0; len < 2; len++) (void)get_byte();
    }
    m_z_err = m_z_eof ? Z_DATA_ERROR : Z_OK;
  }

  int get_byte()
  {
    if (m_z_eof) return EOF;
    if (m_zstream.avail_in == 0) 
   {
    errno = 0;
    m_zstream.avail_in =read(m_inbuf,Z_BUFSIZE);
    if(m_zstream.avail_in == 0)
    {
       m_z_eof = 1;
       return EOF;
    }
    m_zstream.next_in = m_inbuf;
    }
    m_zstream.avail_in--;
    return *(m_zstream.next_in)++;
 }
 int read(LPGZIP buf,int size)
 {
   int nRead=size;
   if(m_pos+size>=m_gziplen)
   {
    nRead=m_gziplen-m_pos;
   }
   if(nRead<=0) return 0;
   memcpy(buf,m_gzip+m_pos,nRead);
   m_pos+=nRead;
   return nRead;
  }

 int gzread(char* buf,int len)
 {
    Bytef *start = (Bytef*)buf; /* starting point for crc computation */
    /*byte  *next_out; /* == stream.next_out but not forced far (for MSDOS) */

     
   /*if (m_z_err == Z_DATA_ERROR || m_z_err == Z_ERRNO) return -1;
    if (m_z_err == Z_STREAM_END) return 0;  /* EOF */

    /*next_out = (byte*)buf;
    m_zstream.next_out = (Bytef*)buf;
    m_zstream.avail_out = len;
    while (m_zstream.avail_out != 0) {
   if (m_transparent)
   {
       /* copy first the lookahead bytes: */
      /* uInt n = m_zstream.avail_in;
       if (n > m_zstream.avail_out) n = m_zstream.avail_out;
       if (n > 0) 
      {
      zmemcpy(m_zstream.next_out,m_zstream.next_in, n);
      next_out += n;
      m_zstream.next_out = next_out;
      m_zstream.next_in   += n;
      m_zstream.avail_out -= n;
      m_zstream.avail_in  -= n;
       }
       if (m_zstream.avail_out > 0) {
       m_zstream.avail_out -=read(next_out,m_zstream.avail_out);
       }
       len -= m_zstream.avail_out;
       m_zstream.total_in  += (uLong)len;
       m_zstream.total_out += (uLong)len;
        if (len == 0) m_z_eof = 1;
       return (int)len;
   }
    if (m_zstream.avail_in == 0 && !m_z_eof)
   {
          errno = 0;
          m_zstream.avail_in = read(m_inbuf,Z_BUFSIZE);
          if (m_zstream.avail_in == 0)
        {
             m_z_eof = 1;
        }
          m_zstream.next_in = m_inbuf;
        }
        m_z_err = inflate(&(m_zstream), Z_NO_FLUSH);
      if (m_z_err == Z_STREAM_END)
      {
       /* Check CRC and original size */
       /*m_crc = crc32(m_crc, start, (uInt)(m_zstream.next_out - start));
       start = m_zstream.next_out;
       if (getLong() != m_crc) {
          m_z_err = Z_DATA_ERROR;
       }else
      {
          (void)getLong();
            check_header();
         if (m_z_err == Z_OK)
         {
          uLong total_in = m_zstream.total_in;
          uLong total_out = m_zstream.total_out;
          inflateReset(&(m_zstream));
          m_zstream.total_in = total_in;
          m_zstream.total_out = total_out;
          m_crc = crc32(0L, Z_NULL, 0);
      }
       }
   }
   if (m_z_err != Z_OK || m_z_eof) break;
    }
    m_crc = crc32(m_crc, start, (uInt)(m_zstream.next_out - start));
    return (int)(len - m_zstream.avail_out);
 }
 uLong getLong()
 {
    uLong x = (uLong)get_byte();
    int c;
    x += ((uLong)get_byte())<<8;
    x += ((uLong)get_byte())<<16;
    c = get_byte();
    if (c == EOF) m_z_err = Z_DATA_ERROR;
    x += ((uLong)c)<<24;
    return x;
 }
 int write(char* buf,int count)
 {
     if(buf==0) return 0;
    if(Length+count>m_CurrentBufferSize)
    {
      int nTimes=(Length+count)/t_nBufferLength +1;
      char *pTemp=psz;
      psz=static_cast<char*>( malloc(nTimes*t_nBufferLength+1));
      m_CurrentBufferSize=nTimes*t_nBufferLength;
      memset(psz,0,m_CurrentBufferSize+1);
      memcpy(psz,pTemp,Length);
      if(pTemp!=m_buffer) free(pTemp);
    }
    memcpy(psz+Length,buf,count);
    Length+=count;
    return count;
 }
 int destroy()
 {
    int err = Z_OK;
   if (m_zstream.state != NULL) {
       err = inflateEnd(&(m_zstream));
   }
    if (m_z_err < 0) err = m_z_err;
    TRYFREE(m_inbuf);
    return err;
}

};
typedef CGZIP2AT<> CGZIP2A;
*/