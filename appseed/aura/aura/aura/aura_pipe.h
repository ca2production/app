#pragma once


namespace aura
{


   class CLASS_DECL_AURA pipe
   {
   public:

      
      char *               m_pchBuf;
      string               m_strRead;


      pipe(bool bInherit);
      virtual ~pipe();


      bool create(bool bBlock = true);


      bool not_inherit_read();
      bool not_inherit_write();

      bool write(const char * psz);
      string read();
      string one_pass_read();


   };

   
   class CLASS_DECL_AURA cross_pipe
   {
   public:


      sp(pipe)    m_spipeIn;
      sp(pipe)    m_sppipeOut;


      cross_pipe(bool bInherit);


      bool create(bool bBlock = true);


   };


} // namespace aura


































