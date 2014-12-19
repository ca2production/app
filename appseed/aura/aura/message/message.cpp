#include "framework.h"


namespace message
{

   class ::signal * CreateSignal()
   {
      return new class ::signal();
   }



   UINT translate_to_os_message(UINT uiMessage)
   {

#ifdef WINDOWS

      switch(uiMessage)
      {
      case message_create:
         return WM_CREATE;
      default:
         return uiMessage;
      };
#elif defined(LINUX) ||  defined(APPLEOS)
      switch(uiMessage)
      {
      case message_create:
         return WM_CREATE;
      default:
         return uiMessage;
      };

#else
      switch(uiMessage)
      {
      default:
         return uiMessage;
      };
#endif

   }





} // namespace message








