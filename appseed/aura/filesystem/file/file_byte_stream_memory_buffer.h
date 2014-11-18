#pragma once


namespace file
{


   class CLASS_DECL_AURA byte_stream_memory_buffer :
      virtual public byte_stream
   {
   public:


      memory_buffer_sp        m_spmemorybuffer;


      byte_stream_memory_buffer(::aura::application * papp);
      byte_stream_memory_buffer(::primitive::memory_base * pbase);
      byte_stream_memory_buffer(::aura::application * papp, const void * data, ::primitive::memory_size c);
      byte_stream_memory_buffer(byte_stream_memory_buffer && b);
      virtual ~byte_stream_memory_buffer();


      virtual file_size get_length();
      virtual void * get_data();
      operator void * () { return get_data(); }

   };


} // namespace file


