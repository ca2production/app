#pragma once


namespace datetime
{


   class CLASS_DECL_AURA file_time:
      public FILETIME
   {
   public:
      file_time() NOTHROW;
      file_time(const FILETIME& ft) NOTHROW;
      file_time(ULONGLONG nTime) NOTHROW;

      static file_time WINAPI get_current_time() NOTHROW;

      file_time& operator=(const FILETIME& ft) NOTHROW;

      file_time& operator+=(file_time_span span) NOTHROW;
      file_time& operator-=(file_time_span span) NOTHROW;

      file_time operator+(file_time_span span) const NOTHROW;
      file_time operator-(file_time_span span) const NOTHROW;
      file_time_span operator-(file_time ft) const NOTHROW;

      bool operator==(file_time ft) const NOTHROW;
      bool operator!=(file_time ft) const NOTHROW;
      bool operator<(file_time ft) const NOTHROW;
      bool operator>(file_time ft) const NOTHROW;
      bool operator<=(file_time ft) const NOTHROW;
      bool operator>=(file_time ft) const NOTHROW;

      ULONGLONG get_time() const NOTHROW;
      void SetTime(ULONGLONG nTime) NOTHROW;

      file_time UTCToLocal() const NOTHROW;
      file_time LocalToUTC() const NOTHROW;

      static const ULONGLONG Millisecond;
      static const ULONGLONG Second;
      static const ULONGLONG Minute;
      static const ULONGLONG Hour;
      static const ULONGLONG Day;
      static const ULONGLONG Week;
   };

   // Used only if these strings could not be found in resources.
   extern CLASS_DECL_AURA const char * const szInvalidDateTime;
   extern CLASS_DECL_AURA const char * const szInvalidDateTimeSpan;

   const int32_t maxTimeBufferSize = 128;
   const long maxDaysInSpan  =   3615897L;




} // namesace datetime












