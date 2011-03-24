#include "StdAfx.h"

Mixer::Mixer(::ca::application * papp) :
   ca(papp),
   m_mixerwnd(papp)
{
   m_mixerwnd.m_pmixer = this;
   m_pdevice = new MixerDevice(this);
}

Mixer::~Mixer()
{
   if(m_mixerwnd.IsWindow())
   {
      m_mixerwnd.DestroyWindow();
   }
   if(m_pdevice != NULL)
   {
      delete m_pdevice;
      m_pdevice = NULL;
   }
}

MMRESULT Mixer::SetNewDevice(
    UINT uiMixerId)
{
   MMRESULT            mmrc;

   if(MMSYSERR_NOERROR != (mmrc = m_pdevice->open(
      uiMixerId,
      (DWORD) m_mixerwnd._get_handle(),
      0,
      CALLBACK_WINDOW)))
   {
      return mmrc;
   }
   return mmrc;
}


BOOL Mixer::GetComponentName
(
    LPMIXERLINE             pmxl,
    string                 &strComponent
)
{
    //
    //
    //
    if (0 == (MIXERLINE_LINEF_SOURCE & pmxl->fdwLine))
    {
        switch (pmxl->dwComponentType)
        {
            case MIXERLINE_COMPONENTTYPE_DST_UNDEFINED:
                strComponent = "Undefined";
                break;

            case MIXERLINE_COMPONENTTYPE_DST_DIGITAL:
                strComponent = "Digital";
                break;

            case MIXERLINE_COMPONENTTYPE_DST_LINE:
                strComponent = "Line Level";
                break;

            case MIXERLINE_COMPONENTTYPE_DST_MONITOR:
                strComponent = "Monitor";
                break;

            case MIXERLINE_COMPONENTTYPE_DST_SPEAKERS:
                strComponent = "Speakers";
                break;

            case MIXERLINE_COMPONENTTYPE_DST_HEADPHONES:
                strComponent = "Headphones";
                break;

            case MIXERLINE_COMPONENTTYPE_DST_TELEPHONE:
                strComponent = "Telephone";
                break;

            case MIXERLINE_COMPONENTTYPE_DST_WAVEIN:
                strComponent = "Wave Input";
                break;

            case MIXERLINE_COMPONENTTYPE_DST_VOICEIN:
                strComponent = "Voice Recognition";
                break;

            default:
                strComponent = "NOT VALID";
                break;
        }
    }
    else
    {
        switch (pmxl->dwComponentType)
        {
            case MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED:
                strComponent = "Undefined";
                break;

            case MIXERLINE_COMPONENTTYPE_SRC_DIGITAL:
                strComponent = "Digital";
                break;

            case MIXERLINE_COMPONENTTYPE_SRC_LINE:
                strComponent = "Line Level";
                break;

            case MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE:
                strComponent = "Microphone";
                break;

            case MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER:
                strComponent = "Synthesizer";
                break;

            case MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC:
                strComponent = "Compact Disc";
                break;

            case MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE:
                strComponent = "Telephone";
                break;

            case MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER:
                strComponent = "PC Speaker";
                break;

            case MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT:
                strComponent = "Wave Out";
                break;

            case MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY:
                strComponent = "Auxiliary";
                break;

            case MIXERLINE_COMPONENTTYPE_SRC_ANALOG:
                strComponent = "Analog";
                break;

            default:
                strComponent = "NOT VALID";
                break;
        }
    }

    return (TRUE);
} // MixAppGetComponentName()

BOOL Mixer::GetControlTypeName
(
    LPMIXERCONTROL          pmxctrl,
    string    &            strTypeName
)
{
    switch (pmxctrl->dwControlType)
    {
        case MIXERCONTROL_CONTROLTYPE_CUSTOM:
            strTypeName = "Custom!";
            break;

        case MIXERCONTROL_CONTROLTYPE_BOOLEANMETER:
            strTypeName = "Boolean Meter";
            break;

        case MIXERCONTROL_CONTROLTYPE_SIGNEDMETER:
            strTypeName = "Signed Meter";
            break;

        case MIXERCONTROL_CONTROLTYPE_PEAKMETER:
            strTypeName = "Peak Meter";
            break;

        case MIXERCONTROL_CONTROLTYPE_UNSIGNEDMETER:
            strTypeName = "Unsigned Meter";
            break;

        case MIXERCONTROL_CONTROLTYPE_BOOLEAN:
            strTypeName = "Boolean Switch";
            break;

        case MIXERCONTROL_CONTROLTYPE_ONOFF:
            strTypeName = "On/Off Switch";
            break;

        case MIXERCONTROL_CONTROLTYPE_MUTE:
            strTypeName = "Mute Switch";
            break;

        case MIXERCONTROL_CONTROLTYPE_MONO:
            strTypeName = "Mono Switch";
            break;

        case MIXERCONTROL_CONTROLTYPE_LOUDNESS:
            strTypeName = "Loudness Switch";
            break;

        case MIXERCONTROL_CONTROLTYPE_STEREOENH:
            strTypeName = "Stereo Enh Switch";
            break;

        case MIXERCONTROL_CONTROLTYPE_BUTTON:
            strTypeName = "button";
            break;

        case MIXERCONTROL_CONTROLTYPE_DECIBELS:
            strTypeName = "Decibels Number";
            break;

        case MIXERCONTROL_CONTROLTYPE_SIGNED:
            strTypeName = "Signed Number";
            break;

        case MIXERCONTROL_CONTROLTYPE_PERCENT:
            strTypeName = "Percent Number";
            break;

        case MIXERCONTROL_CONTROLTYPE_UNSIGNED:
            strTypeName = "Unsigned Number";
            break;

        case MIXERCONTROL_CONTROLTYPE_SLIDER:
            strTypeName = "slider";
            break;

        case MIXERCONTROL_CONTROLTYPE_PAN:
            strTypeName = "Pan slider";
            break;

        case MIXERCONTROL_CONTROLTYPE_QSOUNDPAN:
            strTypeName = "Q-Sound Pan slider";
            break;

        case MIXERCONTROL_CONTROLTYPE_FADER:
            strTypeName = "Fader";
            break;

        case MIXERCONTROL_CONTROLTYPE_VOLUME:
            strTypeName = "Volume Fader";
            break;

        case MIXERCONTROL_CONTROLTYPE_BASS:
            strTypeName = "Bass Fader";
            break;

        case MIXERCONTROL_CONTROLTYPE_TREBLE:
            strTypeName = "Treble Fader";
            break;

        case MIXERCONTROL_CONTROLTYPE_EQUALIZER:
            strTypeName = "Equalizer Fader";
            break;

        case MIXERCONTROL_CONTROLTYPE_SINGLESELECT:
            strTypeName = "Single-Sel List";
            break;

        case MIXERCONTROL_CONTROLTYPE_MUX:
            strTypeName = "MUX List";
            break;

        case MIXERCONTROL_CONTROLTYPE_MULTIPLESELECT:
            strTypeName = "Multi-Sel List";
            break;

        case MIXERCONTROL_CONTROLTYPE_MIXER:
            strTypeName = "Mixer List";
            break;

        case MIXERCONTROL_CONTROLTYPE_MICROTIME:
            strTypeName = "Microsecond time";
            break;

        case MIXERCONTROL_CONTROLTYPE_MILLITIME:
            strTypeName = "Millisecond time";
            break;

        default:
            ASSERT(FALSE);
//            DPF(0, "!MixAppGetControlTypeName: invalid control type %.08lXh!", pmxctrl->dwControlType);
            strTypeName = "** NOT VALID **";
            return (FALSE);
    }

    return (TRUE);
} // MixAppGetControlTypeName()

void Mixer::OnMixerLineChange(HMIXER hMixer, DWORD dwLineID)
{
    if(hMixer == m_pdevice->m_hMixer)
    {
        m_pdevice->OnMixerLineChange(dwLineID);
    }
    else
    {
        ASSERT(FALSE);
    }
}

void Mixer::OnMixerControlChange(HMIXER hMixer, DWORD dwControlID)
{
    if(hMixer == m_pdevice->m_hMixer)
    {
        m_pdevice->OnMixerControlChange(dwControlID);
    }
    else
    {
        ASSERT(FALSE);
    }

}

bool Mixer::OnCommand(WPARAM wparam, LPARAM lparam)
{
   if(m_pdevice != NULL
      &&   m_pdevice->OnCommand(wparam, lparam))
      return TRUE;

   return FALSE;
}


mixer::MixerCallback * Mixer::GetCallback()
{
   return m_pcallback;
}

void Mixer::SetCallback(mixer::MixerCallback * pcallback)
{
   m_pcallback = pcallback;
}