#pragma once


namespace user
{

   class CLASS_DECL_CORE document_request_interface :
      virtual public object
   {
   public:

     
      virtual sp(::user::document_interface) open_new_document();
      virtual sp(::user::document_interface) open_document_file(sp(::create_context) pcreatecontext);
      virtual sp(::user::document_interface) open_document_file(var varFile = ::var(), bool bMakeVisible = true, sp(::user::interaction) puiParent = NULL);


   };

} // namespace user


