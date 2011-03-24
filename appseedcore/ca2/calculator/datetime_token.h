#pragma once


namespace datetime
{

   class CLASS_DECL_ca token
   {
   public:
      token();
      ~token();
      /* Tokens */
      enum e_type
      {
         none,
         identifier,
         function,
         number,
         keyword,
         end,
         error,
         addition,
         subtraction,
         multiplication,
         division,
         equal,
         semi_colon,
         open_paren,
         close_paren,
         char_error,
         virgula, // ,
      };
      e_type         value;
      string      m_str;
      int         m_iType;
      bool        m_bKeyword;
   };

} // namespace calculator