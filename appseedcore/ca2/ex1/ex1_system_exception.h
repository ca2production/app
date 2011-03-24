// Common/Exception.h
// from 7-zip on 2012-12-23, dawn
#pragma once

namespace ex1
{

   class CLASS_DECL_ca system_exception :
      virtual public simple_exception
   {
   public:
      HRESULT ErrorCode;
      system_exception(::ca::application * papp, HRESULT errorCode) :
         ca(papp),
         ErrorCode(errorCode) 
      {
      }
   };

} // namespace ex1
