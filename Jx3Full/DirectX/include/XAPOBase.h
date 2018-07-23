/*-========================================================================-_
 |                                 - XAPO -                                 |
 |        Copyright (c) Microsoft Corporation.  All rights reserved.        |
 |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
 |PROJECT: XAPO                         MODEL:   Unmanaged User-mode        |
 |VERSION: 0.1                          EXCEPT:  No Exceptions              |
 |CLASS:   N / A                        MINREQ:  Win2000, Xbox360           |
 |BASE:    N / A                        DIALECT: MSC++ 13.10, 14.00         |
 |>------------------------------------------------------------------------<|
 | DUTY: XAPO base class                                                    |
 ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^
  NOTES: NONE                                                               */

#pragma once
//--------------<D-E-F-I-N-I-T-I-O-N-S>-------------------------------------//
#include <XAPO.h>

// default audio format ranges supported, used with CXAPOBase.IsInputFormatSupported/IsOutputFormatSupported
#define XAPOBASE_DEFAULT_FORMAT_TAG           WAVE_FORMAT_IEEE_FLOAT // format tag, , applies to WAVEFORMATEX.wFormatTag or WAVEFORMATEXTENSIBLE.SubFormat when used
#define XAPOBASE_DEFAULT_FORMAT_MIN_CHANNELS  XAPO_MIN_CHANNELS      // minimum channel count, applies to WAVEFORMATEX.nChannels
#define XAPOBASE_DEFAULT_FORMAT_MAX_CHANNELS  XAPO_MAX_CHANNELS      // maximum channel count, applies to WAVEFORMATEX.nChannels
#define XAPOBASE_DEFAULT_FORMAT_MIN_FRAMERATE XAPO_MIN_FRAMERATE     // minimum framerate, applies to WAVEFORMATEX.nSamplesPerSec
#define XAPOBASE_DEFAULT_FORMAT_MAX_FRAMERATE XAPO_MAX_FRAMERATE     // maximum framerate, applies to WAVEFORMATEX.nSamplesPerSec
#define XAPOBASE_DEFAULT_FORMAT_BITSPERSAMPLE 32

// default number of input and output buffers supported, applies to CXAPOBase::LockForProcess
#define XAPOBASE_DEFAULT_BUFFER_COUNT 1


//--------------<D-A-T-A---T-Y-P-E-S>---------------------------------------//
#pragma pack(push, 1) // set packing alignment to ensure consistency across arbitrary build environments

  ////
  // DESCRIPTION:
  //  Default implementation of the IXAPO interface.
  //  Provides overridable implementations for all methods save IXAPO::Process.
  ////
class __declspec(novtable) CXAPOBase: public IXAPO {
private:
    const XAPO_REGISTRATION_PROPERTIES* m_pRegistrationProperties; // pointer to registration properties of the XAPO, set via constructor

    void*    m_pfnMatrixMixFunction;    // optimal matrix function pointer, used for thru processing
    FLOAT32* m_pfl32MatrixCoefficients; // matrix coefficient table, used for thru processing
    UINT32   m_nSrcFormatType;          // input format type, used for thru processing
    BOOL     m_fIsScalarMatrix;         // TRUE if m_pfl32MatrixCoefficients is diagonal matrix with all main diagonal entries equal, i.e. m_pfnMatrixMixFunction only used for format conversion and overall volume

    BOOL m_fIsLocked;  // TRUE if XAPO locked via CXAPOBase.LockForProcess
    BOOL m_fIsEnabled; // TRUE if XAPO enabled via CXAPOBase.Enable


protected:
    // Thru processing:
    // This function may be called by an IXAPO::Process implementation when
    // disabled for thru processing.  It copies/mixes data from source to
    // destination, making as few changes as possible to the audio data.
    // However, it is capable of channel upmix/downmix and uses the same
    // matrix coefficient table used by windows Vista to do so.
    //
    // This function may be called if:
    //  1) XAPO locked and disabled
    //  2) number of source frames == number of destination frames
    //  4) output format is FLOAT32
    //  5) input format is INT8, INT16, INT20 (contained in 24 or 32 bits)
    //     INT24 (contained in 24 or 32 bits), INT32, or FLOAT32.
    //     Note: INT16 and FLOAT32 are the most optimized audio formats.
    // For in-place processing (input buffer == output buffer)
    // this function does nothing.
    void ProcessThru (void* pInputBuffer, FLOAT32* pOutputBuffer, UINT32 FrameCount, WORD InputChannelCount, WORD OutputChannelCount, BOOL MixWithDestination);

    // accessors
    const XAPO_REGISTRATION_PROPERTIES* GetRegistrationPropertiesInternal () { return m_pRegistrationProperties; }
    BOOL IsLocked  () { return (InterlockedCompareExchange((LONG*)&m_fIsLocked, 0, 0) == TRUE); }
    BOOL IsEnabled () { return (InterlockedCompareExchange((LONG*)&m_fIsEnabled, 0, 0) == TRUE); }


public:
    CXAPOBase (const XAPO_REGISTRATION_PROPERTIES* pRegistrationProperties);
    virtual ~CXAPOBase ();

    // IXAPO methods:
    // Returns the registration properties of the XAPO.
    // This default implementation returns a copy of the registration
    // properties given to the constructor, allocated via XAPOAlloc.
    STDMETHOD(GetRegistrationProperties) (XAPO_REGISTRATION_PROPERTIES** ppRegistrationProperties);

    // Queries if a specific input format is supported for a given output format.
    // This default implementation assumes only the format described by the
    // XAPOBASE_DEFAULT_FORMAT values are supported for both input and output.
    STDMETHOD(IsInputFormatSupported) (const WAVEFORMATEX* pOutputFormat, const WAVEFORMATEX* pRequestedInputFormat, WAVEFORMATEX** ppSupportedInputFormat);

    // Queries if a specific output format is supported for a given input format.
    // This default implementation assumes only the format described by the
    // XAPOBASE_DEFAULT_FORMAT values are supported for both input and output.
    STDMETHOD(IsOutputFormatSupported) (const WAVEFORMATEX* pInputFormat, const WAVEFORMATEX* pRequestedOutputFormat, WAVEFORMATEX** ppSupportedOutputFormat);

    // Performs any effect-specific initialization.
    // This default implementation is a no-op and only returns S_OK.
    STDMETHOD(Initialize) (void*, UINT32) { return S_OK; }

    // Resets all dynamic parameters and associated state to their initial state.
    // This default implementation is a no-op: this base class contains no
    // relevant state to reset.
    STDMETHOD_(void, Reset) () { return; }

    // Notifies XAPO of stream formats Process() will be given.
    // This default implementation performs basic input/output format
    // validation against the XAPO's registration properties.
    // Derived XAPOs should call the base implementation first.
    STDMETHOD(LockForProcess) (UINT32 InputLockedParameterCount, XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS** ppInputLockedParameters, UINT32 OutputLockedParameterCount, XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS** ppOutputLockedParameters);

    // Opposite of LockForProcess.
    // Derived XAPOs should call the base implementation first.
    STDMETHOD_(void, UnlockForProcess) ();

    // Returns the number of input frames required to generate the given number of output frames.
    // By default, this function returns the same number of frames it was passed.
    STDMETHOD_(UINT32, CalcInputFrames) (UINT32 OutputFrameCount) { return OutputFrameCount; }

    // Returns the number of output frames required to generate the given number of input frames.
    // By default, this function returns the same number of frames it was passed.
    STDMETHOD_(UINT32, CalcOutputFrames) (UINT32 InputFrameCount) { return InputFrameCount; }

    // Enables an XAPO to process normally.
    // Derived XAPOs should call the base implementation first.
    STDMETHOD_(void, Enable) ();

    // Disables an XAPO, putting it in "thru" mode.
    // The default implementation supplies matrix/mix functionality via
    // ProcessThru to implement thru processing.
    // Derived XAPOs should call the base implementation first.
    STDMETHOD_(void, Disable) ();
};



template<int InterfaceCount> class CXAPORegistrationProperties
{
public:
    XAPO_REGISTRATION_PROPERTIES m_RegistrationProperties; // registration properties of an XAPO
    #pragma warning(push)
    #pragma warning(disable: 4200) // disable "zero-sized array in struct/union" compile warning
    IID m_AdditionalInterfaceArray[InterfaceCount-1];      // Set up the array of interface IDs this APO supports
    #pragma warning(pop)


    CXAPORegistrationProperties(REFCLSID clsid,
                                LPCWSTR FriendlyName, LPCWSTR CopyrightInfo,
                                UINT32 Flags,
                                UINT32 MajorVersion, UINT32 MinorVersion,
                                UINT32 MinInputBufferCount = 1,
                                UINT32 MaxInputBufferCount = 1,
                                UINT32 MinOutputBufferCount = 1,
                                UINT32 MaxOutputBufferCount = 1,
                                ...)
    {
        m_RegistrationProperties.clsid = clsid;
        CopyMemory(m_RegistrationProperties.FriendlyName, FriendlyName, sizeof(m_RegistrationProperties.FriendlyName));
        m_RegistrationProperties.FriendlyName[XAPO_REGISTRATION_STRING_LENGTH-1] = '\0';
        CopyMemory(m_RegistrationProperties.CopyrightInfo, CopyrightInfo, sizeof(m_RegistrationProperties.CopyrightInfo));
        m_RegistrationProperties.CopyrightInfo[XAPO_REGISTRATION_STRING_LENGTH-1] = '\0';
        m_RegistrationProperties.Flags = Flags;
        m_RegistrationProperties.MajorVersion = MajorVersion;
        m_RegistrationProperties.MinorVersion = MinorVersion;
        m_RegistrationProperties.MinInputBufferCount = MinInputBufferCount;
        m_RegistrationProperties.MaxInputBufferCount = MaxInputBufferCount;
        m_RegistrationProperties.MinOutputBufferCount = MinOutputBufferCount;
        m_RegistrationProperties.MaxOutputBufferCount = MaxOutputBufferCount;
        m_RegistrationProperties.InterfaceCount = InterfaceCount;
        m_RegistrationProperties.InterfaceArray[0] = __uuidof(IXAPO);

        va_list vargs;
        va_start(vargs, MaxOutputBufferCount);
        UINT_PTR u = 0;
        while (u < InterfaceCount-1) {
            m_AdditionalInterfaceArray[u++] = va_arg(vargs, IID);
        }
        va_end(vargs);
    }

    // dereferencing: returns a reference to the XAPO registration properties
    operator XAPO_REGISTRATION_PROPERTIES&() const
    {
        return m_RegistrationProperties;
    }
    operator const XAPO_REGISTRATION_PROPERTIES*() const
    {
        return &m_RegistrationProperties;
    }
};


#pragma pack(pop) // revert packing alignment
//---------------------------------<-EOF->----------------------------------//
