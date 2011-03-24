// BitlEncoder.h -- the Least Significant Bit of byte is First
// from 7-zip on 2012-12-23, dawn
#pragma once

//#include "../Common/OutBuffer.h"

namespace ex1
{

   namespace bitl
   {

      template < class TOutByte >
      class encoder
      {
         TOutByte m_Stream;
         unsigned m_BitPos;
         byte m_CurByte;
      public:
         bool Create(uint32 bufferSize) { return m_Stream.Create(bufferSize); }
         void SetStream(writer *outStream) { m_Stream.SetStream(outStream); }
         void ReleaseStream() { m_Stream.ReleaseStream(); }
         uint32 GetBitPosition() const { return (8 - m_BitPos); }
         uint64 GetProcessedSize() const { return m_Stream.GetProcessedSize() + (8 - m_BitPos + 7) /8; }
         void Init()
         {
            m_Stream.Init();
            m_BitPos = 8;
            m_CurByte = 0;
         }
         HRESULT Flush()
         {
            FlushByte();
            return m_Stream.Flush();
         }
         void FlushByte()
         {
            if (m_BitPos < 8)
               m_Stream.WriteByte(m_CurByte);
            m_BitPos = 8;
            m_CurByte = 0;
         }
         void WriteBits(uint32 value, unsigned numBits)
         {
            while (numBits > 0)
            {
               if (numBits < m_BitPos)
               {
                  m_CurByte |= (value & ((1 << numBits) - 1)) << (8 - m_BitPos);
                  m_BitPos -= numBits;
                  return;
               }
               numBits -= m_BitPos;
               m_Stream.WriteByte((byte)(m_CurByte | (value << (8 - m_BitPos))));
               value >>= m_BitPos;
               m_BitPos = 8;
               m_CurByte = 0;
            }
         }
         void WriteByte(byte b) { m_Stream.WriteByte(b);}
      };

      typedef CLASS_DECL_ca encoder < out_buffer > out_buffer_encoder;

   } // namespace bitl

} // namespace compress
