#include "framework.h"


namespace windows
{


   factory_exchange::factory_exchange(sp(::base::application) papp) :
      element(papp)
   {

      System.factory().cloneable_large    < stdio_file         >  (System.type_info < ::file::text_buffer         > ()        );
      System.factory().cloneable_large    < file               >  (System.type_info < ::file::binary_buffer       > ()  , true);
      System.factory().creatable_large    < file_set           >  (System.type_info < ::file::set                 >());
      System.factory().cloneable          < file_system        >  (System.type_info < ::file::system              > ()  , 1   );
//      System.factory().cloneable          < WinResource        >  (System.type_info < ::core::resource            > ()  , 1   );
      System.factory().creatable          < application        >  (System.type_info < ::base::application          > ()  , 1   );
      System.factory().cloneable          < dir                >  (System.type_info < ::file::dir::system         > ()  , 1   );
      System.factory().cloneable_small    < folder_watch       >  (System.type_info < ::file::folder_watch        > ()        );
      System.factory().creatable          < window_draw        >  (System.type_info < ::user::window_draw         > ()  , 1   );
      System.factory().creatable_large    < thread             >  (System.type_info < ::thread_impl                 > ()        );
      System.factory().creatable_large    < interaction_impl   >  (System.type_info < ::user::interaction_impl              > ()        );
      System.factory().creatable          < os                 >  (System.type_info < ::base::os                  > ()  , 1   );
      System.factory().creatable          < port_forward       >  (System.type_info < ::net::port_forward         > ()  , 1   );
      System.factory().creatable_small    < copydesk           >  (System.type_info < ::base::copydesk            > ()  , 1   );
      System.factory().creatable_small    < crypto              >  (System.type_info < ::crypto::crypto               > ()  , 1   );
      System.factory().creatable_small    < ip_enum            >  (System.type_info < ::net::ip_enum              > ()        );
//      System.factory().creatable          < printer            >  (System.type_info < ::user::printer             > ()  , 1   );
      System.factory().creatable_large          < print_job            >  (System.type_info < ::user::print_job             > ());

   }


   factory_exchange::~factory_exchange()
   {
   }


} // namespace windows


void __node_factory_exchange(sp(::base::application) papp)
{

   windows::factory_exchange factoryexchange(papp);

}




