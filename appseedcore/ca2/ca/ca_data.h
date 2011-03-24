#pragma once

namespace ca
{

   class data_listener;


   class CLASS_DECL_ca data :
      virtual public ::radix::object
   {
   public:

      class CLASS_DECL_ca writing :
         public interlocked_long_pulse
      {
      public:


         sp(data) m_spdata;


         writing(data * pdata);
         virtual ~writing();

      };

      class CLASS_DECL_ca saving :
         public interlocked_long_pulse
      {
      public:


         sp(data) m_spdata;


         saving(data * pdata);
         virtual ~saving();


      };

      comparable_array < data_listener * > m_listenerptra;

      // writing to this data
      interlocked_long  m_lockedlongWriting;

      // reading data - for saving for example;
      interlocked_long  m_lockedlongSaving;

      data(::ca::application * papp);
      virtual ~data();

      virtual bool is_in_use() const;


      virtual void on_update_data(int iHint);
   };

} // namespace ca