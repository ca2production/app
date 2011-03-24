/* 
* libepp-nicbr 1.10 on 2010-14-10 2009 Registro.br
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
* 1. Redistribution of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
* 
* THIS SOFTWARE IS PROVIDED BY REGISTRO.BR ``AS IS AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIE OF FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
* EVENT SHALL REGISTRO.BR BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*/
/* $Id: BrOrgCheckResponse.cpp 1040 2009-10-01 17:49:12Z fneves $ */
#include "StdAfx.h"


namespace libepp 
{

   void BrOrgCheckResponse::insert_unavailability(const char *organization,  const struct BrOrgCheckResponse::Unavailability& unavail)
   {
      _unavailability_list[organization] = unavail;
   }

   collection::string_map < BrOrgCheckResponse::Unavailability > BrOrgCheckResponse::get_unavailability_list() const
   {
      return _unavailability_list;
   }

} // namespace libepp
