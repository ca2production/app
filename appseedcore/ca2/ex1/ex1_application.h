#pragma once

namespace ex1
{

   class CLASS_DECL_ca application :
      virtual public ::radix::application,
      virtual public request_interface
   {
   public:
      application();
      virtual ~application();

      virtual void Ex1OnFactoryExchange();

      virtual void on_request(var & varFile, var & varQuery);

   };

} // namespace ex1