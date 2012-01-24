#include "StdAfx.h"
#include "radix/BSTR.h"

// return string length or -1 if UNICODE string is found in the archive
AFX_STATIC UINT _AfxReadStringLength(ex1::byte_input_stream & ar);

stringa::stringa(::ca::application * papp) :
   ca(papp)
{
}

stringa::stringa(const stringa &base_array)
{
   operator =(base_array);
}

stringa::~stringa()
{
}

void stringa::add_tokens(const char * lpcsz, const char * lpcszSeparator, BOOL bAddEmpty)
{
   string_tokenizer strTokenizer(lpcsz);
   string strToken;
   if(bAddEmpty)
   {
      while(strTokenizer.GetNextToken(strToken, lpcszSeparator, FALSE))
      {
         string_array::add(strToken);
      }
   }
   else
   {
      while(strTokenizer.GetNextToken(strToken, lpcszSeparator, FALSE))
      {
         if(!strToken.is_empty())
            string_array::add(strToken);
      }
   }
}

int g_add_smallest_tokens = 0;

void stringa::add_smallest_tokens(const char * lpcsz, stringa & straSeparator, BOOL bAddEmpty, BOOL bWithSeparator)
{
   string_tokenizer strTokenizer(lpcsz);
   string strToken;
   if(bAddEmpty)
   {
      while(strTokenizer.GetNextSmallestToken(strToken, straSeparator, bWithSeparator))
      {
         string_array::add(strToken);
      }
   }
   else
   {
      while(strTokenizer.GetNextSmallestToken(strToken, straSeparator, bWithSeparator))
      {
         if(straSeparator.get_data() == get_data())
            AfxDebugBreak();
         if(strToken == "cecyn1.at.hotmail.com")
            g_add_smallest_tokens++;
         if(!strToken.is_empty())
            string_array::add(strToken);
         if(straSeparator.get_data() == get_data())
            AfxDebugBreak();
      }
   }
}

void stringa::get_format_string(string & str, const char * lpcszSeparator) const
{
   str.Empty();
   if(m_nSize > 0)
   {
      str = get_at(0);
   }
   for(int i = 1; i < m_nSize; i++)
   {
      str += lpcszSeparator + get_at(i);
   }
}






/*void stringa::XFV001Expand()
{
   stringa strArray;
   dword_array dwa;
   for(int i = 0; i < m_nSize; i++)
   {
      strArray.add_tokens(get_at(i), "/", FALSE);
      if(strArray.get_size() > 1)
      {
         for(int j = 0; j < strArray.get_size(); j++)
         {
            add_unique(strArray.get_at(j));
         }
         if(strArray.get_size() > 1)
         {
            dwa.add(i);
         }
      }
      strArray.remove_all();
   }
   for(i = dwa.get_size(); --i >= 0 ;)
   {
      remove_at(dwa.get_at(i));
   }
   Sort(stringa::Compare);

}*/

index stringa::add_unique(const char * lpcsz)
{
   index find = find_first(lpcsz);
   if(find >= 0)
      return -1;
   return string_array::add(lpcsz);
}

count stringa::add_unique(const string_array & stra)
{
   count count = 0;
   for(int i = 0; i < stra.get_size(); i++)
   {
      if(add_unique(stra[i]) >= 0)
         count++;
   }
   return count;
}

index stringa::add_unique_ci(const char * lpcsz)
{
   index find = find_first_ci(lpcsz);
   if(find >= 0)
      return -1;
   return string_array::add(lpcsz);
}

count stringa::add_unique_ci(const string_array & stra)
{
   count count = 0;
   for(int i = 0; i < stra.get_size(); i++)
   {
      if(add_unique_ci(stra[i]) >= 0)
         count++;
   }
   return count;
}

index stringa::find_first_ci(const char * lpcsz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find < this->get_count(); find++)
   {
      if(this->element_at(find).CompareNoCase(lpcsz) == 0)
         return find;
   }
   return -1;
}

index stringa::find_first(const char * lpcsz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find < this->get_count(); find++)
   {
      if(this->element_at(find).Compare(lpcsz) == 0)
         return find;
   }
   return -1;
}

index stringa::find_first_begins_ci(const char * lpcsz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find < this->get_count(); find++)
   {
      if(gen::str::begins_ci(this->element_at(find), lpcsz))
         return find;
   }
   return -1;
}

index stringa::find_first_begins(const char * lpcsz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find < this->get_count(); find++)
   {
      if(gen::str::begins(this->element_at(find), lpcsz))
         return find;
   }
   return -1;
}

index stringa::str_find_first_begins_ci(const char * lpcsz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find < this->get_count(); find++)
   {
      if(gen::str::begins_ci(lpcsz, this->element_at(find)))
         return find;
   }
   return -1;
}

index stringa::str_find_first_begins(const char * lpcsz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find < this->get_count(); find++)
   {
      if(gen::str::begins(lpcsz, this->element_at(find)))
         return find;
   }
   return -1;
}


bool stringa::contains_ci(const char * lpcsz, index find, index last, count countMin, count countMax) const
{
   count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_first_ci(lpcsz, find, last)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}

bool stringa::contains(const char * lpcsz, index find, index last, count countMin, count countMax) const
{
   count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_first(lpcsz, find, last)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


index stringa::remove_first_ci(const char * lpcsz, index find, index last)
{
   if((find = find_first_ci(lpcsz, find, last)) >= 0)
      remove_at(find);
   return find;
}

index stringa::remove_first(const char * lpcsz, index find, index last)
{
   if((find = find_first(lpcsz, find, last)) >= 0)
      remove_at(find);
   return find;
}

count stringa::remove_ci(const char * lpcsz, index find, index last, count countMin, count countMax)
{
   count count = 0;
   if(contains_ci(lpcsz, find, last, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax)
         && (find = remove_first_ci(lpcsz, find, last)) >= 0)
         count++;
   return count;
}

count stringa::remove(const char * lpcsz, index find, index last, count countMin, count countMax)
{
   count count = 0;
   if(contains(lpcsz, find, last, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax)
         && (find = remove_first(lpcsz, find, last)) >= 0)
         count++;
   return count;
}

count stringa::remove_ci(const string_array & stra)
{
   count count = 0;
   for(int i = 0; i < stra.get_size(); i++)
   {
      count += remove_ci(stra[i]);
   }
   return count;
}

count stringa::remove(const string_array & stra)
{
   count count = 0;
   for(int i = 0; i < stra.get_size(); i++)
   {
      count += remove(stra[i]);
   }
   return count;
}

void stringa::trim_left()
{
   for(int i = 0; i < m_nSize; i++)
   {
      operator[](i).trim_left();
   }
}

void stringa::trim_right()
{
   for(int i = 0; i < m_nSize; i++)
   {
      operator[](i).trim_right();
   }
}

void stringa::trim()
{
   for(int i = 0; i < m_nSize; i++)
   {
      operator[](i).trim();
   }
}

index stringa::add_normal(const char * lpcsz)
{
   return string_array::add(lpcsz);
}

count stringa::remove_empty()
{
   count count = 0;
   for(index i = 0; i < this->get_size();)
   {
      if(this->element_at(i).is_empty())
      {
         remove_at(i);
         count++;
      }
      else
      {
         i++;
      }
   }
   return count;
}


LPTSTR stringa::GetFormatV004()
{
    int iTotalLength = 0;
    int i;

    for(i = 0; i < m_nSize; i++)
    {
        iTotalLength += this->element_at(i).get_length();
        iTotalLength++;
    }

    if(iTotalLength == 0)
    {
        iTotalLength = 2;
    }
    else
    {
        iTotalLength++;
    }

    LPTSTR lpsz = (LPTSTR) malloc(iTotalLength * sizeof(char));

    memset(lpsz, 0x00, iTotalLength * sizeof(char));

    LPTSTR lpszN = lpsz;

//    size_t sizet;

    int iLength;


    for(i = 0; i < m_nSize; i++)
    {
        string * pstr = &this->element_at(i);

        iLength = pstr->get_length();
        strcat_s(lpszN, iLength, *pstr);

        iLength = _tcsnbcnt(lpszN, iLength);

        lpszN = (LPTSTR) ((LPBYTE)lpszN) + iLength + sizeof(char);

    }

    if(iTotalLength == 2)
    {
        memset(lpsz, 0x00, iTotalLength * sizeof(char));
    }
    else
    {
        memset(lpszN, 0x00, sizeof(char));
    }

    return lpsz;



}


stringa & stringa::operator =(const stringa & tokena)
{
   copy((string_array &) tokena);
   return *this;
}

stringa & stringa::operator =(const string_array & tokena)
{
   copy(tokena);
   return *this;
}

stringa & stringa::operator =(const int64_array & ia)
{
   copy(ia);
   return *this;
}


/*int stringa::CountPrefixNoCase(const char * lpcszPrefix)
{
   string str;
   if(lpcszPrefix != NULL)
      str = lpcszPrefix;
   if(str.is_empty())
   {
      return this->get_size();
   }
   else
   {
      int iCount = 0;
      int iLen = str.get_length();
      for(int i = 0; i < this->get_size(); i++)
      {
         string & strLeft = this->element_at(i).Left(iLen);
         if(strLeft.get_length() == iLen)
         {
            if(CompareNoCase(strLeft, str) == 0)
            {
               iCount++;
            }
         }
      }
      return iCount;
   }
}*/

/*void stringa::ExtractPrefixNoSortNoCase(
   stringa &stra,
   const char * lpcsz,
   int iLength,
   int iMinLength)
{
   ASSERT(iLength >= iMinLength);
   remove_all();
   string str;
   if(lpcsz != NULL)
      str = lpcsz;
   if(str.is_empty())
   {
      for(int i = 0; i < stra.get_size(); i++)
      {
         string & strMid = stra[i].Left(iLength);
         if(strMid.get_length() >= iMinLength)
         {
            if(FindFirstNoSortNoCase(strMid) < 0)
            {
               add(strMid);
            }
         }
      }
   }
   else
   {
      int iLen = max(str.get_length(), iMinLength);
      for(int i = 0; i < stra.get_size(); i++)
      {
         string & strMid = stra[i].Left(iLength);
         if(strMid.get_length() >= iLen)
         {
            if(CompareNoCase(strMid.Left(iLen), str) == 0)
            {
               if(FindFirstNoSortNoCase(strMid) < 0)
               {
                  add(strMid);
               }
            }
         }
      }
   }

}

int stringa::FindFirstNoSortNoCase(const char * lpcsz)
{
   for(int i = 0; i < this->get_size(); i++)
   {
      if(CompareNoCase(lpcsz, this->element_at(i)) == 0)
      {
         return i;
      }
   }
   return -1;
}
*/


void stringa::write(ex1::byte_output_stream & ostream)
{
   ostream << m_nSize;
   for(int i = 0; i < this->get_size(); i++)
   {
      ostream << this->element_at(i);
   }
}

void stringa::read(ex1::byte_input_stream & istream)
{
   count iSize;
   istream >> iSize;

   set_size(iSize);
   for(int i = 0; i < this->get_size(); i++)
   {
      istream >> this->element_at(i);
   }
}



ex1::byte_input_stream & operator>>(ex1::byte_input_stream & ar, string & string)
{
   int nConvert = 0;   // if we get UNICODE, convert

   UINT nNewLen = _AfxReadStringLength(ar);
   if (nNewLen == (UINT)-1)
   {
      nConvert = 1 - nConvert;
      nNewLen = _AfxReadStringLength(ar);
      ASSERT(nNewLen != -1);
   }

   char * lpBuf;
   // set length of string to new length
   UINT nByteLen = nNewLen;
   nByteLen += nByteLen * nConvert;    // bytes to read
   if (nNewLen == 0)
      lpBuf = string.GetBufferSetLength(0);
   else
      lpBuf = string.GetBufferSetLength((int)nByteLen+nConvert);

   // read in the characters
   if (nNewLen != 0)
   {
      ASSERT(nByteLen != 0);

      // read new data
      if (ar.read(lpBuf, nByteLen) != nByteLen)
      {
      //   AfxThrowArchiveException(CArchiveException::endOfFile);
      }

      // convert the data if as necessary
      if (nConvert != 0)
      {
         lpBuf[nNewLen] = '\0';    // must be NUL terminated
         string.ReleaseBuffer();   // don't delete the old data
      }
   }
   return ar;
}

// string serialization code
// string format:
//      UNICODE strings are always prefixed by 0xff, 0xfffe
//      if < 0xff chars: len:BYTE, char chars
//      if >= 0xff characters: 0xff, len:WORD, char chars
//      if >= 0xfffe characters: 0xff, 0xffff, len:DWORD, TCHARs

ex1::byte_output_stream & operator<<(ex1::byte_output_stream & ar, const string & string)
{
    if (string.get_length() < 255)
   {
      ar << (BYTE)string.get_length();
   }
   else if (string.get_length() < 0xfffe)
   {
      ar << (BYTE)0xff;
      ar << (WORD)string.get_length();
   }
   else
   {
      ar << (BYTE)0xff;
      ar << (WORD)0xffff;
      ar << (DWORD)string.get_length();
   }

   ar.write((const char *) string, string.get_length());
   return ar;
}

// return string length or -1 if UNICODE string is found in the archive
AFX_STATIC UINT _AfxReadStringLength(ex1::byte_input_stream & ar)
{
   DWORD nNewLen;

   // attempt BYTE length first
   BYTE bLen;
   ar >> bLen;

   if (bLen < 0xff)
      return bLen;

   // attempt WORD length
   WORD wLen;
   ar >> wLen;
   if (wLen == 0xfffe)
   {
      // UNICODE string prefix (length will follow)
      return (UINT)-1;
   }
   else if (wLen == 0xffff)
   {
      // read DWORD of length
      ar >> nNewLen;
      return (UINT)nNewLen;
   }
   else
      return wLen;
}


void stringa::implode(string & str, const char * lpcszSeparator, index start, count count) const
{
   str.Empty();
   string strSeparator(lpcszSeparator);
   if(start < 0)
   {
      start += this->get_size();
   }
   index last;
   if(count < 0)
   {
      last = this->get_size() + count;
   }
   else
   {
      last = start + count - 1;
   }
   for(index i = start; i <= last; i++)
   {
      if(i > start)
      {
         str += strSeparator;
      }
      str += this->element_at(i);
   }
}

string stringa::implode(const char * lpcszSeparator, index iStart, index iEnd) const
{
   string str;
   implode(str, lpcszSeparator, iStart, iEnd);
   return str;
}


void stringa::reverse_implode(string & str, const char * lpcszSeparator, index start, count count) const
{
   str.Empty();
   string strSeparator(lpcszSeparator);
   if(start < 0)
   {
      start += this->get_size();
   }
   index last;
   if(count < 0)
   {
      last = this->get_size() + count;
   }
   else
   {
      last = start + count - 1;
   }
   for(index i = last; i >= start; i--)
   {
      if(i < last)
      {
         str += strSeparator;
      }
      str += this->element_at(i);
   }
}

string stringa::reverse_implode(const char * lpcszSeparator, index iStart, index iEnd) const
{
   string str;
   reverse_implode(str, lpcszSeparator, iStart, iEnd);
   return str;
}

void stringa::explode(const char * lpcszSeparator, const char * psz)
{
   remove_all();
   add_tokens(psz, lpcszSeparator, true);
}


void stringa::replace(const char * lpszSearch, const char * lpszReplace)
{
   for(int i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).replace(lpszSearch, lpszReplace);
   }
}


void stringa::surround(const char * pszPrefix, const char * pszSuffix, int iStart, int iCount)
{
   string strPrefix(pszPrefix);
   string strSuffix(pszSuffix);
   int iEnd;
   if(iStart < 0)
      iStart = this->get_size() + iStart;
   if(iCount < 0)
      iEnd = this->get_size() + iCount;
   else
      iEnd = iStart + iCount - 1;
   for(int i = iStart; i <= iEnd; i++)
   {
      this->element_at(i) = strPrefix + this->element_at(i) + strSuffix;
   }
}

string stringa::surround_and_implode(const char * pszSeparator, const char * pszPrefix, const char * pszSuffix, int iStart, int iCount)
{
   string str;
   string strSeparator(pszSeparator);
   string strPrefix(pszPrefix);
   string strSuffix(pszSuffix);
   int iEnd;
   if(iStart < 0)
      iStart = this->get_size() + iStart;
   if(iCount < 0)
      iEnd = this->get_size() + iCount;
   else
      iEnd = iStart + iCount - 1;
   if(iStart <= iEnd)
   {
      str = strPrefix + this->element_at(iStart) + strSuffix;
      iStart++;
      for(int i = iStart; i <= iEnd; i++)
      {
         str += strSeparator + strPrefix + this->element_at(i) + strSuffix;
      }
   }
   return str;
}

stringa & stringa::operator -=(const string_array & stra)
{
   remove(stra);
   return *this;
}

stringa & stringa::operator +=(const string_array & stra)
{
   add(stra);
   return *this;
}

stringa stringa::operator -(const string_array & straParam) const
{
   stringa stra(*this);
   stra -= straParam;
   return stra;
}

stringa stringa::operator +(const string_array & straParam) const
{
   stringa stra(*this);
   stra += straParam;
   return stra;
}

stringa & stringa::operator = (var var)
{
   if(var.get_type() == var::type_stra)
   {
      *this = var.stra();
   }
   else
   {
      remove_all();
      if(var.get_count() == 1)
      {
         add(var.get_string());
      }
      else if(var.get_count() > 1)
      {
         *this = var.stra();
      }
   }
   return *this;
}

bool stringa::move_ci(const char * lpcsz, index iIndex)
{
   index i = find_first_ci(lpcsz);
   if(i < 0)
      return false;
   remove_at(i);
   insert_at(iIndex, lpcsz);
   return true;
}

bool stringa::preferred(const char * lpcsz)
{
   return move_ci(lpcsz, 0);
}

count stringa::preferred(stringa & stra)
{
   count count = 0;
   for(index i = stra.get_upper_bound(); i >= 0; i--)
   {
      if(preferred(stra[i]))
         count++;
   }
   return count;
}


string stringa::pop(index i)
{
   i = get_upper_bound(i);
   string strRet = this->element_at(i);
   remove_at(i);
   return strRet;
}

void stringa::slice(stringa & stra, index iOffset)
{
   slice(stra, iOffset, this->get_count() - 1 - iOffset);
}

void stringa::slice(stringa & stra, index iOffset, count count)
{
   index iUpperBound = get_upper_bound(iOffset, count);
   for(index i = get_lower_bound(iOffset); i <= iUpperBound; i++)
   {
      stra.add(this->element_at(i));
   }
}

void stringa::remove(index iOffset, count count)
{
   index iLowerBound = get_lower_bound(iOffset);
   index iUpperBound = get_upper_bound(iOffset, count);
   if(iUpperBound < 0)
      return;
   for(index i = iUpperBound; i >= iLowerBound; i--)
   {
      remove_at(i);
   }
}

void stringa::splice(const stringa & stra, index iOffset)
{
   splice(stra, iOffset, this->get_count() - 1 - iOffset);
}

void stringa::splice(const stringa & stra, index iOffset, count count)
{
   UNREFERENCED_PARAMETER(iOffset);
   //index iUpperBound = get_upper_bound(iOffset, count);
   remove(iOffset, count);
   insert_at(iOffset, stra);
}

void stringa::splice(const stringa & stra, index iOffset, stringa & straRemoved)
{
   splice(stra, iOffset, this->get_count() - 1 - iOffset, straRemoved);
}

void stringa::splice(const stringa & stra, index iOffset, count count, stringa & straRemoved)
{
   slice(straRemoved, iOffset, count);
   remove(iOffset, count);
   insert_at(iOffset, stra);
}

bool stringa::is_empty(count countMinimum)
{
   return this->get_size() < countMinimum;
}

bool stringa::has_elements(count countMinimum)
{
   return this->get_count() >= countMinimum;
}


count stringa::get_begins_ci(stringa & stra, const char * lpcsz, index first, index last)
{
   if(last < 0)
      last = this->get_size() + last;
   if(last >= this->get_size())
      last = get_upper_bound();
   if(first < 0)
      first = 0;
   index i = first;
   index iFind;
   count count = 0;
   while(true)
   {
      iFind = find_first_begins_ci(lpcsz, i, last);
      if(iFind < 0)
         return count;
      stra.add(this->element_at(iFind));
      i = iFind + 1;
      count++;
   }
}

count stringa::filter_begins_ci(const char * lpcsz, index first, index last)
{
   if(last < 0)
      last = this->get_size() + last;
   if(last >= this->get_size())
      last = get_upper_bound();
   if(first < 0)
      first = 0;
   index i = first;
   index iFind;
   count count = 0;
   while(true)
   {
      iFind = find_first_begins_ci(lpcsz, i, last);
      if(iFind < 0)
      {
         remove_at(i, last - i + 1);
         return count;
      }
      remove_at(i, iFind - i);
      last -= iFind - i;
      i++;
      count++;

   }
}

index stringa::get_random_index() const
{
   if(this->get_size() <= 0)
      return -1;
   return System.math().RandRange(0, get_upper_bound());
}

string & stringa::random_element()
{
   if(this->get_size() <= 0)
      throw "invalid call";
   return this->element_at(get_random_index());
}

const string & stringa::random_element() const
{
   if(this->get_size() <= 0)
      throw "invalid call";
   return this->element_at(get_random_index());
}

string stringa::pop_random_element()
{
   if(this->get_size() <= 0)
      throw "invalid call";
   index i = get_random_index();
   string str = this->element_at(i);
   remove_at(i);
   return str;
}



void stringa::make_lower()
{
   for(index i = 0; i < this->get_count(); i++)
   {
      this->element_at(i).make_lower();
   }
}

void stringa::make_upper()
{
   for(index i = 0; i < this->get_count(); i++)
   {
      this->element_at(i).make_upper();
   }
}
