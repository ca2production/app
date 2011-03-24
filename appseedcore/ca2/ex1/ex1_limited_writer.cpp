// LimitedStreams.cpp
// from 7-zip on 2012-12-23, lunch time
#include "StdAfx.h"


namespace ex1
{


   void limited_writer::write(const void *data, DWORD_PTR size, DWORD_PTR * processedSize)
   {
      if (processedSize != NULL)
         *processedSize = 0;
      if (size > _size)
      {
         if (_size == 0)
         {
            _overflow = true;
            if (!_overflowIsAllowed)
               throw system_exception(get_app(), E_FAIL);
            if (processedSize != NULL)
               *processedSize = size;
            return;
         }
         size = (uint32)_size;
      }
      if (_stream)
         _stream->write(data, size, &size);
      _size -= size;
      if (processedSize != NULL)
         *processedSize = size;
      return;
   }

} // namespace ex1