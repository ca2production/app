#pragma once




namespace ace
{


   class CLASS_DECL_ACE trace_add_file_and_line
#if defined(VARIADIC_TEMPLATE_FORMAT2)
      : public string_format_printer
#endif
   {
   public:


      ::ace::application *      m_paceapp;
      const char * const         m_pszFileName;
      const int32_t              m_nLineNo;
      string                     m_str;

//#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

      class CLASS_DECL_ACE category_level
      {
      public:


         uint32_t    m_dwCategory;
         UINT     m_nLevel;


      };

//#endif

      trace_add_file_and_line(::ace::application * papp, const char *pszFileName, int32_t nLineNo)
         : m_paceapp(papp),m_pszFileName(pszFileName),m_nLineNo(nLineNo)
      {
      }

      inline sp(::ace::application) get_app() const
      {
         return m_paceapp;
      }

      inline sp(::ace::application) get_app()
      {
         return m_paceapp;
      }

#if defined(VARIADIC_TEMPLATE_FORMAT2)



      void trace_category_level(void * pvoid, const char * psz)
      {

         category_level * pcategorylevel = (category_level *)pvoid;

         System.log().trace_str(m_pszFileName, m_nLineNo, pcategorylevel->m_dwCategory, pcategorylevel->m_nLevel, psz);

      }

      void trace(void *, const char * psz)
      {

         System.log().trace_str(m_pszFileName, m_nLineNo, trace::category_General, 0, psz);

      }

//#if defined(VARIADIC_TEMPLATE_FORMAT)


      inline void __cdecl operator()(uint32_t dwCategory, UINT nLevel, const char *pszFmt) const
      {

         category_level categorylevel;

         categorylevel.m_dwCategory = dwCategory;
         categorylevel.m_nLevel = nLevel;

         string_format format(this, &trace_add_file_and_line::trace_category_level, &categorylevel);

         format.format(pszFmt);


      }

      template<typename T, typename... Args>
      inline void __cdecl operator()(uint32_t dwCategory, UINT nLevel, const char * pszFmt, const T & value, Args... args) const
      {

         category_level categorylevel;

         categorylevel.m_dwCategory = dwCategory;
         categorylevel.m_nLevel = nLevel;

         string_format format(this, &trace_add_file_and_line::trace_category_level, &categorylevel);

         format.format(pszFmt, value, args...);

      }

//#endif

      inline void __cdecl operator()(const char *psz) const
      {

//         string_format format(this, &trace_add_file_and_line::trace, NULL);

//         format.format(pszFmt);

         System.log().trace_str(m_pszFileName, m_nLineNo, trace::category_General, 0, psz);


      }

//#if defined(VARIADIC_TEMPLATE_FORMAT)


      template<typename T, typename... Args>
      inline void __cdecl operator()(const char * pszFmt, const T & value, Args... args) const
      {

         string_format format(this, &trace_add_file_and_line::trace, NULL);

         format.format(pszFmt, value, args...);

      }


#elif !defined(VARIADIC_TEMPLATE_FORMAT)

      inline void __cdecl operator()(uint32_t dwCategory, UINT nLevel, const char *pszFmt, ...) const
      {
         va_list ptr; va_start(ptr, pszFmt);
         System.log().trace_v(m_pszFileName, m_nLineNo, dwCategory, nLevel, pszFmt, ptr);
         va_end(ptr);
      }

      inline void __cdecl operator()(const char *pszFmt, ...) const
      {
         va_list ptr; va_start(ptr, pszFmt);
         System.log().trace_v(m_pszFileName, m_nLineNo, trace::category_General, 0, pszFmt, ptr);
         va_end(ptr);
      }

#endif
   private:
      /* unimplemented */
      trace_add_file_and_line &__cdecl operator=(const trace_add_file_and_line &right);

   };


} // namespace ace













