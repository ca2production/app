#pragma once


class CLASS_DECL_AURA invalid_argument_exception :
   virtual public simple_exception
{
public:


   invalid_argument_exception(::aura::application * papp);
   invalid_argument_exception(::aura::application * papp, const char * pszMessage);
   virtual ~invalid_argument_exception();


};

