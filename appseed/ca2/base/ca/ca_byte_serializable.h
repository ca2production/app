#pragma once


#include "ca_byte_stream.h"


namespace ca
{


   class byte_input_stream;
   class byte_output_stream;


   class CLASS_DECL_ca2 byte_serializable :
      virtual public ::ca::ca
   {
   public:


      virtual void write(byte_output_stream & ostream) = 0;
      virtual void read(byte_input_stream & istream) = 0;


   };


   template < class type_array >
   class byte_serializable_array :
      virtual public type_array,
      virtual public byte_serializable
   {
   public:
      virtual void write(byte_output_stream & ostream);
      virtual void read(byte_input_stream & istream);
      virtual void on_after_read();
   };

   template < class type_pointer_array >
   class byte_serializable_pointer_array :
      virtual public type_pointer_array,
      virtual public byte_serializable
   {
   public:
      virtual void write(byte_output_stream & ostream);
      virtual void read(byte_input_stream & istream);
      virtual void on_after_read();
   };

   template < class type_array >
   void byte_serializable_array < type_array >::write(byte_output_stream & ostream)
   {
      ::count count = this->get_count();
      ostream.write_arbitrary(count);
      for(index index = 0; index < count; index++)
      {
         ostream << this->element_at(index);
      }
   }

   template < class type_array >
   void byte_serializable_array < type_array >::read(byte_input_stream & istream)
   {
      ::count count;
      //istream >> count;
      istream.read_arbitrary(count);
      this->set_size(count);
      for(index index = 0; index < count; index++)
      {
         istream >> this->element_at(index);
      }
      on_after_read();
   }

   template < class type_pointer_array >
   void byte_serializable_pointer_array < type_pointer_array >::write(byte_output_stream & ostream)
   {
      ::count count = this->get_count();
      ostream.write_arbitrary(count);
      for(index index = 0; index < count; index++)
      {
         ostream << *this->element_at(index);
      }
   }

   template < class type_pointer_array >
   void byte_serializable_pointer_array < type_pointer_array >::read(byte_input_stream & istream)
   {
      ::count count;
      //istream >> count;
      istream.read_arbitrary(count);
      this->set_size_create(count);
      for(index index = 0; index < count; index++)
      {
         istream >> *this->element_at(index);
      }
      on_after_read();
   }

   template < class type_array >
   void byte_serializable_array < type_array >::on_after_read()
   {
   }

   template < class type_pointer_array >
   void byte_serializable_pointer_array < type_pointer_array >::on_after_read()
   {
   }

   template < class type_map >
   class byte_serializable_map :
      virtual public type_map,
      virtual public byte_serializable
   {
   public:


      byte_serializable_map(::ca::application * papp = ::null(), ::count nBlockSize = 10);
      byte_serializable_map(const byte_serializable_map & map);


      virtual void write(byte_output_stream & ostream);
      virtual void read(byte_input_stream & istream);
      virtual void on_after_read();


      byte_serializable_map & operator = (const byte_serializable_map & map);

   };

   template < class type_map >
   byte_serializable_map < type_map >::byte_serializable_map(::ca::application * papp, ::count nBlockSize) :
      type_map(papp, nBlockSize)
   {
   }

   template < class type_map >
   byte_serializable_map < type_map >::byte_serializable_map(const byte_serializable_map & map) :
      type_map(dynamic_cast < const type_map & > (map))
   {
   }

   template < class type_map >
   void byte_serializable_map < type_map >::write(byte_output_stream & ostream)
   {
      ::count count = this->get_count();
      ostream.write_arbitrary(count);
      typename type_map::pair * p = this->PGetFirstAssoc();
      for(index index = 0; index < count; index++)
      {
         ostream << p->m_element1;
         ostream << p->m_element2;
         p = this->PGetNextAssoc(p);
      }
   }

   template < class type_map >
   void byte_serializable_map < type_map >::read(byte_input_stream & istream)
   {
      ::count count;
      istream.read_arbitrary(count);
      typename type_map::BASE_KEY key;
      typename type_map::BASE_VALUE value;
      for(index index = 0; index < count; index++)
      {
         istream >> key;
         istream >> value;
         this->set_at(key, value);
      }
      on_after_read();
   }

   template < class type_map >
   void byte_serializable_map < type_map >::on_after_read()
   {
   }

   template < class type_map >
   byte_serializable_map < type_map > & byte_serializable_map < type_map >::operator = (const byte_serializable_map & map)
   {

      if(this != &map)
      {

         type_map::m_nBlockSize = map.type_map::m_nBlockSize;
         type_map::operator = (map);

      }

      return *this;

   }

}
