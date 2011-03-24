#pragma once

namespace calculator
{

   class CLASS_DECL_ca document :
      public ::userbase::document
   {
   public:


      document(::ca::application * papp);   


      DECL_GEN_VSIGNAL(data_on_after_change);

      virtual BOOL on_new_document();
   public:
      virtual ~document();
#ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

      bool on_open_document(var varFile);


   };

} //
