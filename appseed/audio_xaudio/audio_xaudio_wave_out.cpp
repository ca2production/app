#include "framework.h"
// thank you (casey) : tahnk oy coed prjsoetc China Cai Tao

namespace multimedia
{


   namespace audio_xaudio
   {



      wave_out::wave_out(sp(::axis::application) papp) :
         ::object(papp),
         ::thread(papp),
         wave_base(papp),
         ::multimedia::audio::wave_out(papp)
      {




         m_estate             = state_initial;
         m_pthreadCallback    = NULL;
         m_iBufferedCount     = 0;
         m_peffect            = NULL;
         m_dwLostSampleCount  = 0;

      }

      wave_out::~wave_out()
      {

      }

      void wave_out::install_message_handling(::message::dispatch * pinterface)
      {

         ::multimedia::audio::wave_out::install_message_handling(pinterface);

      }


      bool wave_out::initialize_instance()
      {

         if(!::multimedia::audio::wave_out::initialize_instance())
            return false;

         set_thread_priority(::multithreading::priority_time_critical);

         return true;

      }

      int32_t wave_out::run()
      {
         //m_durationRunLock = millis(1);
         while(m_bRun)
         {
            ::thread::run();
         }



         return 0;
      }

      //bool wave_out::on_run_step()
      //{

      //   return ::thread::on_run_step();

      //}

      int32_t wave_out::exit_instance()
      {

         ::multimedia::audio::wave_out::exit_instance();

         return ::thread::exit_instance();

      }

      ::multimedia::e_result wave_out::wave_out_open(::thread * pthreadCallback, int32_t iBufferCount, int32_t iBufferSampleCount)
      {

         single_lock sLock(&m_mutex, TRUE);


         if(m_pxaudio != NULL && m_pvoice != NULL && m_psourcevoice != NULL && m_estate != state_initial)
            return ::multimedia::result_success;


         m_pthreadCallback = pthreadCallback;
         ::multimedia::e_result mmr;
         ASSERT(m_pxaudio == NULL);
         ASSERT(m_pvoice == NULL);
         ASSERT(m_psourcevoice == NULL);
         ASSERT(m_estate == state_initial);

         // by (indirect casey)
         if(FAILED(XAudio2Create(&m_pxaudio,0,XAUDIO2_DEFAULT_PROCESSOR)))
         {

            return ::multimedia::result_error;

         }

         HRESULT hr;

         if(FAILED(hr = m_pxaudio->CreateMasteringVoice(&m_pvoice)))
         {
            return ::multimedia::result_error;
         }

         // Set up the source voice and register the callback class
         //VoiceCallback voiceCallback;

         m_pwaveformat->wFormatTag = WAVE_FORMAT_PCM;
         m_pwaveformat->nChannels = 2;
         m_pwaveformat->nSamplesPerSec = 44100;
         m_pwaveformat->wBitsPerSample = sizeof(::multimedia::audio::WAVEBUFFERDATA) * m_pwaveformat->nChannels * 8;
         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize = 0;
         sp(::multimedia::audio::wave) audiowave = Application.audiowave();

         if(FAILED(hr = m_pxaudio->CreateSourceVoice(&m_psourcevoice,wave_format(), 0,XAUDIO2_DEFAULT_FREQ_RATIO,this,NULL,NULL)))
         {
            return ::multimedia::result_error;
         }
         //if(mmr = xaudio::translate(waveOutOpen(
         //   &m_hwaveout,
         //   audiowave->m_uiWaveInDevice,
         //   wave_format(),
         //   get_os_int(),
         //   (uint32_t) 0,
         //   CALLBACK_THREAD))))
         //   goto Opened;
         //m_pwaveformat->nSamplesPerSec = 22050;
         //m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         //if(MMSYSERR_NOERROR == (mmr = xaudio::translate(waveOutOpen(
         //   &m_hwaveout,
         //   WAVE_MAPPER,
         //   ,
         //   (uint32_t) get_os_int(),
         //   (uint32_t) 0,
         //   CALLBACK_THREAD))))
         //   goto Opened;
         //m_pwaveformat->nSamplesPerSec = 11025;
         //m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         //if(MMSYSERR_NOERROR == (mmr = xaudio::translate(waveOutOpen(
         //   &m_hwaveout,
         //   WAVE_MAPPER,
         //   wave_format(),
         //   (uint32_t) get_os_int(),
         //   (uint32_t) 0,
         //   CALLBACK_THREAD))))
         //   goto Opened;

         //if(mmr != ::multimedia::result_success)
         //{
         //   return mmr;
         //}

Opened:
         uint32_t uiBufferSizeLog2;
         uint32_t uiBufferSize;
         uint32_t uiAnalysisSize;
         uint32_t uiAllocationSize;
         uint32_t uiInterestSize;
         uint32_t uiSkippedSamplesCount;
         uint32_t uiBufferCount = iBufferCount;

         if(m_pwaveformat->nSamplesPerSec == 44100)
         {
            uiBufferSizeLog2 = 16;
            uiBufferSize = m_pwaveformat->nChannels * 2 * iBufferSampleCount; // 512 kbytes
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            if(iBufferCount > 0)
            {
               uiAllocationSize = iBufferCount * uiAnalysisSize;
            }
            else
            {
               uiAllocationSize = 8 * uiAnalysisSize;
            }
            uiInterestSize = 200;
            uiSkippedSamplesCount = 2;
         }
         else if(m_pwaveformat->nSamplesPerSec == 22050)
         {
            uiBufferSizeLog2 = 10;
            uiBufferSize = 4 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 200;
            uiSkippedSamplesCount = 1;
         }
         else if(m_pwaveformat->nSamplesPerSec == 11025)
         {
            uiBufferSizeLog2 = 10;
            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 2 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 200;
            uiSkippedSamplesCount = 1;
         }

         wave_out_get_buffer()->PCMOutOpen(this, uiBufferSize, uiBufferCount, 2048,m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(
            this, // callback thread (thread)
            m_pwaveformat->nChannels, // channel count
            uiBufferCount, // group count
            iBufferSampleCount); // group sample count


         // TODO(casey): DSBCAPS_GETCURRENTPOSITION2




         m_estate = state_opened;

         return ::multimedia::result_success;

      }

      ::multimedia::e_result wave_out::wave_out_open_ex(thread * pthreadCallback, int32_t iBufferCount, int32_t iBufferSampleCount, uint32_t uiSamplesPerSec, uint32_t uiChannelCount, uint32_t uiBitsPerSample, ::multimedia::audio::e_purpose epurpose)
      {

         single_lock sLock(&m_mutex, TRUE);

         if(m_pxaudio != NULL && m_pvoice != NULL && m_psourcevoice != NULL && m_estate != state_initial)
            return ::multimedia::result_success;

         m_iBuffer = 0;

         m_pthreadCallback = pthreadCallback;
         ::multimedia::e_result mmr;
         ASSERT(m_pxaudio == NULL);
         ASSERT(m_pvoice == NULL);
         ASSERT(m_psourcevoice == NULL);
         ASSERT(m_estate == state_initial);

         CoInitializeEx(nullptr,COINIT_MULTITHREADED);

         // by (indirect casey)
         if(FAILED(XAudio2Create(&m_pxaudio,0,XAUDIO2_DEFAULT_PROCESSOR)))
         {

            return ::multimedia::result_error;

         }

#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/) && defined(_DEBUG)
         // To see the trace output, you need to view ETW logs for this application:
         //    Go to Control Panel, Administrative Tools, Event Viewer.
         //    View->Show Analytic and Debug Logs.
         //    Applications and Services Logs / Microsoft / Windows / XAudio2.
         //    Right click on Microsoft Windows XAudio2 debug logging, Properties, then Enable Logging, and hit OK
         XAUDIO2_DEBUG_CONFIGURATION debug ={0};
         debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
         debug.BreakMask = XAUDIO2_LOG_ERRORS;
         m_pxaudio->SetDebugConfiguration(&debug,0);
#endif


         HRESULT hr;

         if(FAILED(hr = m_pxaudio->CreateMasteringVoice(&m_pvoice,uiChannelCount, uiSamplesPerSec)))
         {
            return ::multimedia::result_error;
         }
         int iSampleRate = XAUDIO2_MIN_SAMPLE_RATE;
         mmr = ::multimedia::result_success;
         m_pwaveformat->wFormatTag = WAVE_FORMAT_PCM;
         m_pwaveformat->nChannels = uiChannelCount;
         m_pwaveformat->nSamplesPerSec = uiSamplesPerSec;
         m_pwaveformat->wBitsPerSample = sizeof(::multimedia::audio::WAVEBUFFERDATA) * 8 ;
         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample  * uiChannelCount / 8;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize = 0;
         sp(::multimedia::audio::wave) audiowave = Application.audiowave();

         //if(FAILED(hr = m_pxaudio->CreateSourceVoice(&m_psourcevoice,wave_format(),XAUDIO2_VOICE_NOSRC | XAUDIO2_VOICE_NOPITCH,1.0f,this)))
         if(FAILED(hr = m_pxaudio->CreateSourceVoice(&m_psourcevoice,wave_format(),0,1.0f,this)))
         {
            return ::multimedia::result_error;
         }

         if(mmr != ::multimedia::result_success)
         {

            TRACE0(::multimedia::strerror(mmr));

            return mmr;

         }

Opened:
         if(epurpose == ::multimedia::audio::purpose_playback)
         {

            iBufferCount = 8;
            iBufferSampleCount = (1 << 9);

         }
         else if(epurpose == ::multimedia::audio::purpose_playground)
         {

            iBufferCount = 1;
            iBufferSampleCount = (1 << 9);

         }
         else
         {

            iBufferCount = 4;
            iBufferSampleCount = (1 << 9);

         }

         int iAlign = 2048;

         uint32_t uiBufferSize = iBufferSampleCount * m_pwaveformat->nChannels * 2;

         uiBufferSize = MAX(uiBufferSize,2048);

         ASSERT((uiBufferSize % 2048) == 0);// Streaming size must be 2K aligned to use for async I/O





         wave_out_get_buffer()->PCMOutOpen(this, uiBufferSize, iBufferCount,iAlign, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(this, m_pwaveformat->nChannels, iBufferCount, iBufferSampleCount);

         m_pprebuffer->SetMinL1BufferCount(wave_out_get_buffer()->GetBufferCount());

         m_estate = state_opened;

         m_epurpose = epurpose;

         return ::multimedia::result_success;

      }



      ::multimedia::e_result wave_out::wave_out_close()
      {

         single_lock sLock(&m_mutex, TRUE);

         if(m_estate == state_playing)
         {
            wave_out_stop();
         }

         if(m_estate != state_opened)
            return ::multimedia::result_success;

         ::multimedia::e_result mmr;

         int32_t i, iSize;

         iSize =  wave_out_get_buffer()->GetBufferCount();

         //for(i = 0; i < iSize; i++)
         //{

         mmr = xaudio::translate(m_psourcevoice->Stop());

         //for(i = 0; i < iSize; i++)
         //{

         //   delete m_bufferptra[i];

         //}


         //m_psourcevoice->DestroyVoice();

         try
         {

            m_psourcevoice->DestroyVoice();

            m_psourcevoice.Release();

         }
         catch(...)
         {

         }

         //m_bufferptra.remove_all();


         try
         {


            if(m_pvoice != NULL)
            {

               m_pvoice->DestroyVoice();

               m_pvoice->Release();

               m_pvoice = NULL;

            }
         }
         catch (...)
         {

         }

         try
         {


            if(m_pxaudio != nullptr)
            {

               m_pxaudio->StopEngine();
            
               m_pxaudio = NULL;

            }

         }
         catch (...)
         {

         }

         //mmr = xaudio::translate(waveOutClose(m_hwaveout));

         //m_hwaveout = NULL;

		 ::multimedia::audio::wave_out::wave_out_close();

         return ::multimedia::result_success;

      }


      /*
      * Find the first occurrence of the byte string s in byte string l.
      */

      void *
         memmem(const void *l,size_t l_len,const void *s,size_t s_len)
      {
         register char *cur,*last;
         const char *cl = (const char *)l;
         const char *cs = (const char *)s;

         /* we need something to compare */
         if(l_len == 0 || s_len == 0)
            return NULL;

         /* "s" must be smaller or equal to "l" */
         if(l_len < s_len)
            return NULL;

         /* special case where s_len == 1 */
         if(s_len == 1)
            return memchr((void *) l,(int)*cs,l_len);

         /* the last position where its possible to find "s" in "l" */
         last = (char *)cl + l_len - s_len;

         for(cur = (char *)cl; cur <= last; cur++)
            if(cur[0] == cs[0] && memcmp(cur,cs,s_len) == 0)
               return cur;

         return NULL;
      }
      void wave_out::wave_out_buffer_ready(int iBuffer)
      {

         if(wave_out_get_state() != state_playing)
         {
            TRACE("ERROR wave_out::BufferReady while wave_out_get_state() != state_playing");
            return;
         }

         ::multimedia::audio::wave_buffer * pwbuffer = wave_out_get_buffer();
         ::multimedia::audio::wave_buffer::buffer * pbuffer = pwbuffer->get_buffer(iBuffer);

         ::multimedia::e_result mmr;
         if(m_peffect != NULL)
         {
            m_peffect->Process16bits((int16_t *)pbuffer->m_pData,pwbuffer->m_uiBufferSize / 2);
         }

         XAUDIO2_BUFFER b;
         ZERO(b);
         b.pContext = pbuffer;
         b.AudioBytes = pwbuffer->m_uiBufferSize;
         b.pAudioData = (const BYTE *)pbuffer->m_pData;
         b.Flags = m_bEOS ? XAUDIO2_END_OF_STREAM : 0;

         //single_lock sLock(&m_mutex,TRUE);

         char sz[16];

         ZERO(sz);

         if(memmem(b.pAudioData,pwbuffer->m_uiBufferSize,sz,sizeof(sz)))
         {
            //output_debug_string("too much zeros in audio buffer\n");
         }

         static DWORD g_dwLastBuffer;
         DWORD dwTick = get_tick_count();
         if(dwTick-g_dwLastBuffer > 50)
         {
            output_debug_string("too much delay for submitting audio buffer\n");
         }
            g_dwLastBuffer = dwTick;

         mmr = xaudio::translate(m_psourcevoice->SubmitSourceBuffer(&b));

         VERIFY(::multimedia::result_success == mmr);

         if(mmr == ::multimedia::result_success)
         {

            m_iBufferedCount++;

         }

      }




      ::multimedia::e_result wave_out::wave_out_stop()
      {

         single_lock sLock(&m_mutex, TRUE);

         if(m_estate != state_playing && m_estate != state_paused)
            return ::multimedia::result_error;

         m_eventStopped.ResetEvent();

         m_pprebuffer->Stop();

         m_estate = state_stopping;

         //// waveOutReset
         //// The waveOutReset function stops playback on the given
         //// waveform-audio_xaudio output device and resets the current position
         //// to zero. All pending playback buffers are marked as done and
         //// returned to the application.
         m_mmr = xaudio::translate(m_psourcevoice->Stop());

         if(m_mmr == ::multimedia::result_success)
         {

            m_estate = state_opened;

         }

         return m_mmr;

      }


      ::multimedia::e_result wave_out::wave_out_pause()
      {

         single_lock sLock(&m_mutex, TRUE);

         ASSERT(m_estate == state_playing);

         if(m_estate != state_playing)
            return ::multimedia::result_error;

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_xaudio output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.

         m_mmr = xaudio::translate(m_psourcevoice->Stop());

         ASSERT(m_mmr == ::multimedia::result_success);

         if(m_mmr == ::multimedia::result_success)
         {
            m_estate = state_paused;
         }

         return m_mmr;

      }

      ::multimedia::e_result wave_out::wave_out_start(const imedia::position & position)
      {

         single_lock sLock(&m_mutex,TRUE);

         if(m_estate == state_playing)
            return result_success;

         ASSERT(m_estate == state_opened || m_estate == state_stopped);

         m_bEOS = false;

         m_estate = state_playing;

         for(index i = 0; i < wave_out_get_buffer()->GetBufferCount(); i++)
         {

            wave_out_free(i);

         }

         m_mmr = xaudio::translate(m_psourcevoice->Start(0,XAUDIO2_COMMIT_NOW));

         //         m_prunstepthread = new run_step_thread(this);


         return result_success;

      }


      ::multimedia::e_result wave_out::wave_out_restart()
      {

         single_lock sLock(&m_mutex, TRUE);

         ASSERT(m_estate == state_paused);

         if(m_estate != state_paused)
            return ::multimedia::result_error;

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_xaudio output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_mmr = xaudio::translate(m_psourcevoice->Start(0,XAUDIO2_COMMIT_NOW));

         ASSERT(m_mmr == ::multimedia::result_success);

         if(m_mmr == ::multimedia::result_success)
         {

            m_estate = state_playing;

         }

         return m_mmr;

      }


      /*imedia_time wave_out::GetPositionMillisForSynch()
      {
         int64_t dwMillis = GetPositionMillis();
         int64_t dwPosition = m_pprebuffer->m_position * 8;
         dwPosition /= m_pwaveformat->wBitsPerSample;
         dwPosition *= 1000;
         dwPosition /= m_pwaveformat->nChannels * m_pwaveformat->nSamplesPerSec;
         if(m_pprebuffer != NULL && m_pprebuffer->m_pdecoder != NULL)
            return dwMillis + dwPosition - m_pprebuffer->m_pdecoder->DecoderGetLostMillis(dwMillis + dwPosition) - (((int64_t) m_dwLostSampleCount) /  ((int64_t) m_pwaveformat->nSamplesPerSec));
         else
            return dwMillis + dwPosition - ((m_dwLostSampleCount) * 1000 / m_pwaveformat->nSamplesPerSec);
      }*/

      imedia_time wave_out::wave_out_get_position_millis()
      {

         single_lock sLock(&m_mutex, TRUE);

         ::multimedia::e_result                mmr;

         XAUDIO2_VOICE_STATE s;

         if(m_psourcevoice != NULL)
         {

            m_psourcevoice->GetState(&s);

            int64_t i = s.SamplesPlayed;
            i *= 1000;
            i /= m_pwaveformat->nChannels * m_pwaveformat->nSamplesPerSec;
            return i;

         }
         else
            return 0;


      }

      /*imedia::position wave_out::get_position_for_synch()
      {
         imedia::position position = get_position();
         if(m_pprebuffer != NULL && m_pprebuffer->m_pdecoder != NULL)
            return m_pprebuffer->m_position + position - m_pprebuffer->m_pdecoder->DecoderGetLostPositionOffset(position) - m_dwLostSampleCount * m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         else
            return m_pprebuffer->m_position + position - m_dwLostSampleCount * m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
      }*/

      imedia::position wave_out::wave_out_get_position()
      {

         single_lock sLock(&m_mutex, TRUE);

         ::multimedia::e_result                mmr;

         XAUDIO2_VOICE_STATE s;

         if (m_psourcevoice != NULL)
         {

            m_psourcevoice->GetState(&s);

               return s.SamplesPlayed;
         }
         else
            return 0;


      }

      void wave_out::wave_out_free(int iBuffer)
      {

         //wave_out_free(wave_hdr(iBuffer));

         ::multimedia::audio::wave_out::wave_out_free(iBuffer);

      }


      void wave_out::wave_out_on_playback_end()
      {

         wave_out_stop();

         if(m_pprebuffer->m_pstreameffectOut != NULL)
         {
            ::multimedia::iaudio::wave_stream_effect * peffect = m_pprebuffer->m_pstreameffectOut;
            m_pprebuffer->m_pstreameffectOut = NULL;
            delete peffect;
         }

         m_eventStopped.SetEvent();

         m_pplayer->OnEvent(::multimedia::audio::wave_player::EventPlaybackEnd);

      }

      int32_t wave_out::wave_out_get_buffered_buffer_count()
      {

         return ::multimedia::audio::wave_out::wave_out_get_buffered_buffer_count();

      }


      WAVEFORMATEX * wave_out::wave_format()
      {

         xaudio::translate(m_waveformatex, m_pwaveformat);

         return &m_waveformatex;

      }


      void * wave_out::get_os_data()
      {
         return m_psourcevoice;
      }


      void wave_out::wave_out_run_step()
      {

         int iPlay =  -1;


      }

      void wave_out::wave_out_prebuffer_eof()
      {

         ::multimedia::audio::wave_out::wave_out_prebuffer_eof();

      }


      void wave_out::OnStreamEnd()
      {
         
         //wave_out_on_playback_end();

      }


      //
      // Callback handlers, only implement the buffer events for maintaining play state
      //
      void wave_out::OnVoiceProcessingPassStart(UINT32 /*bytesRequired*/)
      {
      }
      void wave_out::OnVoiceProcessingPassEnd()
      {
      }

      void wave_out::OnBufferStart(void* pBufferContext)
      {

         ::multimedia::audio::wave_buffer::buffer * pbuffer = (::multimedia::audio::wave_buffer::buffer *)pBufferContext;

         //pbuffer->m_bIsPlaying =  true;

      }

      void wave_out::OnBufferEnd(void* pBufferContext)
      {

         if(get_thread_priority() != ::multithreading::priority_time_critical)
         {

            set_thread_priority(::multithreading::priority_time_critical);

         }

         unsigned __int64 freq;
         QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
         double timerFrequency = (1.0 / freq);
         unsigned __int64 startTime;
         QueryPerformanceCounter((LARGE_INTEGER *)&startTime);


         ::multimedia::audio::wave_buffer::buffer * pbuffer = (::multimedia::audio::wave_buffer::buffer *)pBufferContext;

         m_iBufferedCount--;


         //pbuffer->m_bIsPlaying = false;

         int32_t iBuffer = (int32_t)pbuffer->m_iIndex;

         wave_out_out_buffer_done(iBuffer);

         unsigned __int64 endTime;
         QueryPerformanceCounter((LARGE_INTEGER *)&endTime);
         double timeDifferenceInseconds = ((endTime - startTime) * timerFrequency);
         if(timeDifferenceInseconds > 0.040)
         {
            ::output_debug_string("too much delay to create audio\n");
         }
       
      

      }


      void wave_out::OnLoopEnd(void* /*bufferContext*/)
      {
      }
      void wave_out::OnVoiceError(void* /*bufferContext*/, HRESULT /*error*/)
      {
      }
      wave_out::run_step_thread::run_step_thread(wave_out * pout):
         ::thread(pout->get_app())
{
}


      int32_t wave_out::run_step_thread::run()
      {

         while(m_bRun && m_pout->m_estate == wave_out::state_playing)
         {
            m_pout->wave_out_run_step();
         }


         return 0;
      }


   } // namespace audio_xaudio


} // namespace multimedia






