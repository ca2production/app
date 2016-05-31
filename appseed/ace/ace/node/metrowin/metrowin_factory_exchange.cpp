//#include "framework.h"
//#include "metrowin.h"


namespace metrowin
{


   namespace ace
   {


      factory_exchange::factory_exchange(::ace::application * papp):
         ::object(papp)
      {

         System.factory().cloneable_large < stdio_file            >(System.template type_info < ::file::text_buffer         >());
         System.factory().cloneable_large < file                  >(System.template type_info < ::file::binary_buffer       >());
         System.factory().cloneable_large < file                  >(System.template type_info < ::file::stream_buffer       >());
  //       System.factory().cloneable       < application           >(System.template type_info < ::ace::application         >(),1);
         System.factory().cloneable_small < folder_watch          >(System.template type_info < ::file::folder_watch        >());
         System.factory().creatable_large < ::thread                >(System.template type_info < ::thread               >());
         System.factory().creatable       < os                    >(System.template type_info < ::ace::os                  >(),1);

         System.factory().cloneable       < file_system           >(System.template type_info < ::file::system              >(),1);
         System.factory().cloneable       < dir                   >(System.template type_info < ::file::dir::system         >(),1);

      }


      factory_exchange::~factory_exchange()
      {
      }


   } // namespace ace


} // namespace metrowin



void __node_ace_factory_exchange(::ace::application * papp)
{

   ::metrowin::ace::factory_exchange factoryexchange(papp);

}



