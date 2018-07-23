/*-========================================================================-_
 |                                 - XAPO -                                 |
 |        Copyright (c) Microsoft Corporation.  All rights reserved.        |
 |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
 |PROJECT: XAPO                         MODEL:   Unmanaged User-mode        |
 |VERSION: 0.1                          EXCEPT:  No Exceptions              |
 |CLASS:   N / A                        MINREQ:  Win2000, Xbox360           |
 |BASE:    N / A                        DIALECT: MSC++ 13.10, 14.00         |
 |>------------------------------------------------------------------------<|
 | DUTY: Cross-platform Audio Processing Object interfaces                  |
 ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^
  NOTES:
    1.  Definition of terms:
            DSP: Digital signal processing.

            CBR: Constant bit rate.  DSP that consumes a constant number of
                 input samples to produce an output sample.
                 For example, a 22kHz to 44kHz resampler is CBR DSP.
                 Even though the number of input and output samples differ,
                 the ratio between input to output rate remains constant.
                 XAudio2 only allows CBR DSP to be added to an effect chain.

            XAPO: Cross-platform Audio Processing Object.
                  A thin wrapper that manages DSP code, allowing it
                  to be easily plugged into an XAudio2 effect chain.

            Frame: A collection of samples, one per channel,
                   to be played simultaneously.

    2.  XAPO member variables are divided into three classifications:
            Immutable: Set once during IXAPO::Initialize and remain
                       constant for the lifespan of the XAPO.

            Locked: May change before IXAPO::LockForProcess is called
                    but must remain constant afterward until
                    IXAPO::UnlockForProcess is called.

            Dynamic: May change from one processing pass to the next,
                     usually via IXAPOParameters::SetParameters.  XAPOs
                     should strive to assign reasonable defaults for such
                     parameters during IXAPO::Initialize/LockForProcess such
                     that calling IXAPOParameters::SetParameters is not
                     required before processing begins.

        When implementing an XAPO, determine the type of each variable and
        initialize them in the appropriate method.  In general, immutable
        parameters are preferable over locked which are preferable over
        dynamic.  That is, one should strive to minimize XAPO state changes
        for best performance and ease of use.

    3.  To minimize glitches, the realtime XAudio2 thread should not block.
        Thus, certain XAPO methods called by the realtime thread are commented
        as non-blocking and should not use blocking synchronization,
        allocate memory, or access the disk etc.  The XAPO interface has been
        designed to allow an effect implementer to move such opertaions into
        other methods called on an application controlled thread.

    4.  Extending functionality is accomplished through the addition of new
        COM interfaces.  For example, if a new member is added to a parameter
        structure, a new interface using the new structure should be added,
        leaving the original interface unchanged.
        This ensures consistent communication between future versions of
        XAudio2 and various versions of XAPOs that may exist in an application.

    5.  All audio data is interleaved in XAudio2.
        The default audio format for an effect chain is WAVE_FORMAT_IEEE_FLOAT.

    6.  See XAPOBase.h for an XAPO base class which provides default
        implementation for most of the interface methods defined below.     */

#pragma once
//--------------<D-E-F-I-N-I-T-I-O-N-S>-------------------------------------//
#include <comdecl.h> // for DEFINE_IID

// XAPO interface IDs
DEFINE_IID(IXAPO,           A90BC001, E897, E897, 55, E4, 9E, 47, 00, 00, 00, 00);
DEFINE_IID(IXAPOParameters, A90BC001, E897, E897, 55, E4, 9E, 47, 00, 00, 00, 01);


#if !defined(GUID_DEFS_ONLY) // ignore rest if only GUID definitions requested
    #if defined(_XBOX)       // general windows and COM declarations
        #include <xtl.h>
        #include <xobjbase.h>
    #else
        #include <windows.h>
        #include <objbase.h>
    #endif
    #include <audiodefs.h>   // for WAVEFORMATEX etc.

    // XAPO error codes
    #define FACILITY_XAPO 0x897
    #define XAPO_E_FORMAT_UNSUPPORTED MAKE_HRESULT(SEVERITY_ERROR, FACILITY_XAPO, 0x01) // given audio format unsupported

    // supported number of channels (samples per frame) range, applies to WAVEFORMATEX.nChannels
    #define XAPO_MIN_CHANNELS 1
    #define XAPO_MAX_CHANNELS 64

    // supported framerate range, applies to WAVEFORMATEX.nSamplesPerSec
    #define XAPO_MIN_FRAMERATE 1000
    #define XAPO_MAX_FRAMERATE 200000

    // unicode string length, used with XAPO_REGISTRATION_PROPERTIES
    #define XAPO_REGISTRATION_STRING_LENGTH 256

    // XAPO property flags, describes general DSP behaviour, used with XAPO_REGISTRATION_PROPERTIES
    #define XAPO_FLAG_INPLACE_SUPPORTED        0x00000001 // XAPO supports in-place processing (input buffer == output buffer)
    #define XAPO_FLAG_INPLACE_REQUIRED         0x00000003 // XAPO requires in-place processing (input buffer == output buffer)
    #define XAPO_FLAG_CHANNELS_MUST_MATCH      0x00000004 // channel count of input and output buffers must match, applies to WAVEFORMATEX.nChannels
    #define XAPO_FLAG_FRAMERATE_MUST_MATCH     0x00000008 // framerate of input and output buffers must match, applies to WAVEFORMATEX.nSamplesPerSec
    #define XAPO_FLAG_BITSPERSAMPLE_MUST_MATCH 0x00000010 // bit depth AND container size of input and output buffers must match, applies to WAVEFORMAT.wBitsPerSample, and WAVEFORMATEXTENSIBLE.wValidBitsPerSample when used
    #define XAPO_FLAG_DEFAULT (XAPO_FLAG_INPLACE_SUPPORTED | XAPO_FLAG_CHANNELS_MUST_MATCH | XAPO_FLAG_FRAMERATE_MUST_MATCH | XAPO_FLAG_BITSPERSAMPLE_MUST_MATCH)


//--------------<D-A-T-A---T-Y-P-E-S>---------------------------------------//
    #pragma pack(push, 1) // set packing alignment to ensure consistency across arbitrary build environments

    // primitive types
    typedef float FLOAT32; // 32-bit IEEE float

    // XAPO registration properties, describes general XAPO behaviour, used with IXAPO::GetRegistrationProperties
    typedef struct XAPO_REGISTRATION_PROPERTIES {
        CLSID  clsid;                                          // COM class ID, used with CoCreate
        WCHAR  FriendlyName[XAPO_REGISTRATION_STRING_LENGTH];  // friendly name unicode string
        WCHAR  CopyrightInfo[XAPO_REGISTRATION_STRING_LENGTH]; // copyright information unicode string
        UINT32 Flags;                                          // XAPO property flags, describes general DSP behaviour
        UINT32 MajorVersion;                                   // major version
        UINT32 MinorVersion;                                   // minor version
        UINT32 MinInputBufferCount;                            // minimum number of input buffers required for processing, can be 0
        UINT32 MaxInputBufferCount;                            // maximum number of input buffers supported for processing, must be >= MinInputBufferCount
        UINT32 MinOutputBufferCount;                           // minimum number of output buffers required for processing, can be 0
        UINT32 MaxOutputBufferCount;                           // maximum number of output buffers supported for processing, must be >= MinOutputBufferCount
        UINT32 InterfaceCount;                                 // number of COM interface IDs in InterfaceArray
        IID InterfaceArray[1];                                 // supported COM interface ID array, must have InterfaceCount elements
    } XAPO_REGISTRATION_PROPERTIES;

    // LockForProcess buffer parameters:
    // Defines buffer parameters that remain constant while an XAPO is locked.
    // Used with IXAPO::LockForProcess.
    //
    // For CBR XAPOs, MaxFrameCount is the only frame count
    // IXAPO::Process would ever have to handle for the respective buffer.
    typedef struct XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS {
        const WAVEFORMATEX* pFormat;       // buffer audio format
        UINT32              MaxFrameCount; // maximum number of frames in the respective buffer that IXAPO::Process would ever have to handle, irrespective of dynamic parameter settings
    } XAPO_LOCKFORPROCESS_PARAMETERS;

    // Buffer flags:
    // Describes content of the respective buffer.
    // Used with XAPO_PROCESS_BUFFER_PARAMETERS.
    //
    // This meta-data can be used to implement optimizations that require
    // knowledge of a buffer's content.  For example, XAPOs that always
    // produce silent output from silent input can check the flag on the
    // input buffer to determine if any signal processing is necessary.
    // If silent, the XAPO may simply set the flag on the output buffer
    // to silent and return, optimizing out the work of processing silent data:
    // XAPOs that generate silence for any reason may set the buffer's
    // flag accordingly rather than writing out silent samples to memory.
    typedef enum XAPO_BUFFER_FLAGS {
        XAPO_BUFFER_SILENT, // buffer contains only silent samples
        XAPO_BUFFER_VALID,  // buffer contains arbitrary data; unknown if silent or otherwise
    } XAPO_BUFFER_FLAGS;

    // Process buffer parameters:
    // Defines buffer parameters that may change from one
    // processing pass to the next.  Used with IXAPO::Process.
    //
    // Note the byte size of the respective buffer must be at least:
    //      XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS.MaxFrameCount * XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS.pFormat->nBlockAlign
    //
    // Although the audio format and maximum size of the respective
    // buffer is locked (defined by XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS),
    // the actual memory address of the buffer given is permitted to change
    // from one processing pass to the next.
    //
    // For CBR XAPOs, ValidFrameCount is constant while locked and equals
    // the respective XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS.MaxFrameCount.
    typedef struct XAPO_PROCESS_BUFFER_PARAMETERS {
        void*             pBuffer;         // audio data buffer, must be non-NULL, frame-aligned, and XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS.MaxFrameCount frames in size
        XAPO_BUFFER_FLAGS BufferFlags;     // describes content of the buffer, does not affect ValidFrameCount
        UINT32            ValidFrameCount; // number of frames to process, must be within [0, XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS.MaxFrameCount], does not affect BufferFlags
    } XAPO_PROCESS_BUFFER_PARAMETERS;


//--------------<M-A-C-R-O-S>-----------------------------------------------//
// Memory allocation macros that allow one module to allocate memory and
// another to free it, by guaranteeing that the same heap manager is used
// regardless of differences between build environments of the two modules.
//
// Used by IXAPO methods that must allocate arbitrary sized structures
// such as WAVEFORMATEX that are subsequently returned to the application.
#if defined(_XBOX)
    #define XAPO_ALLOC_ATTRIBUTES MAKE_XALLOC_ATTRIBUTES (      \
        0,                           /* ObjectType */           \
        FALSE,                       /* HeapTracksAttributes */ \
        FALSE,                       /* MustSucceed */          \
        FALSE,                       /* FixedSize */            \
        eXALLOCAllocatorId_XAUDIO2,  /* AllocatorId */          \
        XALLOC_ALIGNMENT_DEFAULT,    /* Alignment */            \
        XALLOC_MEMPROTECT_READWRITE, /* MemoryProtect */        \
        FALSE,                       /* ZeroInitialize */       \
        XALLOC_MEMTYPE_HEAP          /* MemoryType */           \
    )
    #define XAPOAlloc(size) XMemAlloc(size, XAPO_ALLOC_ATTRIBUTES)
    #define XAPOFree(p)     XMemFree(p, XAPO_ALLOC_ATTRIBUTES)
#else
    #define XAPOAlloc(size) CoTaskMemAlloc(size)
    #define XAPOFree(p)     CoTaskMemFree(p)
#endif


//--------------<I-N-T-E-R-F-A-C-E-S>---------------------------------------//
    // forward declarations
    #if defined(__cplusplus)
        #define FORWARD_DECLARE(x) interface x
    #else
        #define FORWARD_DECLARE(x) typedef interface x x
    #endif
    FORWARD_DECLARE(IXAPO);
    FORWARD_DECLARE(IXAPOParameters);

    // IXAPO:
    // The only mandatory XAPO COM interface.  A thin wrapper that manages
    // DSP code, allowing it to be easily plugged into an XAudio2 effect chain.
    #undef INTERFACE
    #define INTERFACE IXAPO
    DECLARE_INTERFACE_(IXAPO, IUnknown)
    {
          ////
          // DESCRIPTION:
          //  Returns the registration properties of the XAPO.
          //
          // PARAMETERS:
          //  ppRegistrationProperties - [out] receives pointer to registration properties, use XAPOFree to free the structure, left untouched on failure
          //
          // RETURN VALUE:
          //  COM error code
          ////
        STDMETHOD(GetRegistrationProperties) (THIS_ XAPO_REGISTRATION_PROPERTIES** ppRegistrationProperties) PURE;

          ////
          // DESCRIPTION:
          //  Queries if a specific input format is supported for a given output format.
          //
          // REMARKS:
          //  Quering against an input/output format pair allows for effects
          //  whose supported input formats depend on the given output format.
          //
          //  If the requested input format is not supported with respect to
          //  the given output format, the XAPO should suggest the 'nearest'
          //  input format supported.  'nearest' meaning similar framerate,
          //  bit depth, channel count, in that order of importance.
          //
          //  The behaviour of this method may change with respect to an
          //  XAPO's internal state, but should remain constant once the XAPO
          //  is locked for processing via LockForProcess.
          //
          // PARAMETERS:
          //  pOutputFormat          - [in]  output format, may be NULL if pRequestedInputFormat is also NULL and ppSupportedInputFormat is not NULL
          //  pRequestedInputFormat  - [in]  input format to query if supported for given output format, may be NULL if pOutputFormat is also NULL and ppSupportedInputFormat is not NULL
          //  ppSupportedInputFormat - [out] if not NULL and pRequestedInputFormat not supported with respect to pOutputFormat, receives pointer to nearest input format supported with respect to pOutputFormat, use XAPOFree to free the structure
          //
          // RETURN VALUE:
          //  COM error code, including:
          //    S_OK                      - format pair supported, ppSupportedInputFormat left untouched if pOutputFormat/pRequestedInputFormat not NULL
          //    XAPO_E_FORMAT_UNSUPPORTED - pRequestedInputFormat not supported for given pOutputFormat, ppSupportedInputFormat set if not NULL
          ////
        STDMETHOD(IsInputFormatSupported) (THIS_ const WAVEFORMATEX* pOutputFormat, const WAVEFORMATEX* pRequestedInputFormat, WAVEFORMATEX** ppSupportedInputFormat) PURE;

          ////
          // DESCRIPTION:
          //  Queries if a specific output format is supported for a given input format.
          //
          // REMARKS:
          //  Quering against an input/output format pair allows for effects
          //  whose supported output formats depend on the given input format.
          //
          //  If the requested output format is not supported with respect to
          //  the given input format, the XAPO should suggest the 'nearest'
          //  output format supported.  'nearest' meaning similar framerate,
          //  bit depth, channel count, in that order of importance.
          //
          //  The behaviour of this method may change with respect to an
          //  XAPO's internal state, but should remain constant once the XAPO
          //  is locked for processing via LockForProcess.
          //
          // PARAMETERS:
          //  pInputFormat            - [in]  input format, may be NULL if pOutputInputFormat is also NULL and ppSupportedInputFormat is not NULL
          //  pRequestedOutputFormat  - [in]  ouput format to query if supported for given input format, may be NULL if pInputFormat is also NULL and ppSupportedOutputFormat is not NULL
          //  ppSupportedOutputFormat - [out] if not NULL and pRequestedOutputFormat not supported with respect to pInputFormat, receives pointer to nearest output format supported with respect to pInputFormat, use XAPOFree to free the structure
          //
          // RETURN VALUE:
          //  COM error code, including:
          //    S_OK                      - format pair supported, ppSupportedOutputFormat left untouched if pInputFormat/pRequestedOutputFormat not NULL
          //    XAPO_E_FORMAT_UNSUPPORTED - pRequestedOutputFormat not supported for given pInputFormat, ppSupportedOutputFormat set if not NULL
          ////
        STDMETHOD(IsOutputFormatSupported) (THIS_ const WAVEFORMATEX* pInputFormat, const WAVEFORMATEX* pRequestedOutputFormat, WAVEFORMATEX** ppSupportedOutputFormat) PURE;

          ////
          // DESCRIPTION:
          //  Performs any effect-specific initialization.
          //
          // REMARKS:
          //  The contents of pData are defined by a given XAPO.
          //  Immutable parameters (constant for the lifetime of the XAPO)
          //  should be set in this method.
          //  Once initialized, an XAPO cannot be initialized again.
          //  An XAPO should be initialized before passing it to XAudio2
          //  as part of an effect chain.  XAudio2 will not call this method,
          //  it exists for future content-driven initialization by XACT.
          //
          // PARAMETERS:
          //  pData        - [in] effect-specific initialization parameters, may be NULL if DataByteSize is 0
          //  DataByteSize - [in] size of pData in bytes, may be 0 if DataByteSize is NULL
          //
          // RETURN VALUE:
          //  COM error code
          ////
        STDMETHOD(Initialize) (THIS_ void* pData, UINT32 DataByteSize) PURE;

          ////
          // DESCRIPTION:
          //  Resets all dynamic parameters and associated state to their
          //  initial state, returning the object to the state it was in
          //  just after LockForProcess was first called.
          //
          // REMARKS:
          //  Immutable and locked parameters such as the input and output
          //  formats remain unchanged.
          //
          //  For example, an XAPO with a delay line would zero out the delay
          //  line during reset, but need not reallocate the delay line since
          //  the object remains locked with constant input and output formats.
          //
          // PARAMETERS:
          //  void
          //
          // RETURN VALUE:
          //  void
          ////
        STDMETHOD_(void, Reset) (THIS) PURE;

          ////
          // DESCRIPTION:
          //  Notifies XAPO of stream formats Process will be given.
          //
          // REMARKS:
          //  The XAPO may assert the given formats are supported.
          //  IsInputFormatSupported/IsOutputFormatSupported are supplied
          //  for format support queries.
          //
          //  All internal memory buffers required for Process should be
          //  allocated by the time this method returns since Process is
          //  a non-blocking method which should not allocate memory.
          //  Once locked, an XAPO cannot be locked again until UnLockForProcess is called.
          //
          // PARAMETERS:
          //  InputLockedParameterCount  - [in] number of elements in ppInputLockedStreamParameters
          //  ppInputLockedParameters    - [in] array of input locked parameter structures
          //  OutputLockedParameterCount - [in] number of elements in ppOutputLockedStreamParameters
          //  ppOutputLockedParameters   - [in] array of output locked parameter structures
          //
          // RETURN VALUE:
          //  HResult error code
          ////
        STDMETHOD(LockForProcess) (THIS_ UINT32 InputLockedParameterCount, XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS** ppInputLockedParameters, UINT32 OutputLockedParameterCount, XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS** ppOutputLockedParameters) PURE;

          ////
          // DESCRIPTION:
          //  Opposite of LockForProcess: variables allocated during LockForProcess
          //  should be deallocated in this method.
          //
          // REMARKS:
          //  Unlocking an XAPO allows an XAPO instance to be reused with
          //  different input/output formats.
          //
          // PARAMETERS:
          //  void
          //
          // RETURN VALUE:
          //  void
          ////
        STDMETHOD_(void, UnlockForProcess) (THIS) PURE;

          ////
          // DESCRIPTION:
          //  Runs the XAPO's DSP code on the given input/output buffers.
          //
          // REMARKS:
          //  This method should not block as it is called from the realtime
          //  audio processing thread.
          //
          // PARAMETERS:
          //  InputProcessParameterCount  - [in]     number of elements in ppInputProcessParameters
          //  ppInputProcessParameters    - [in]     array of input process parameter structures
          //  OutputProcessParameterCount - [in]     number of elements in ppOutputProcessParameters
          //  ppOutputProcessParameters   - [in/out] array of output process parameter structures
          //
          // RETURN VALUE:
          //  void
          ////
        STDMETHOD_(void, Process) (THIS_ UINT32 InputProcessParameterCount, XAPO_PROCESS_BUFFER_PARAMETERS** ppInputProcessParameters, UINT32 OutputProcessParameterCount, XAPO_PROCESS_BUFFER_PARAMETERS** ppOutputProcessParameters) PURE;

          ////
          // DESCRIPTION:
          //  Returns the number of input frames required to generate the
          //  given number of output frames.
          //
          // REMARKS:
          //  XAudio2 calls this method to determine how many input frames
          //  an XAPO requies.  This number is constant for CBR XAPOs and so
          //  this method need only be called once while an XAPO is locked.
          //
          //  Apart from writing to the output buffer as appropriate, an
          //  XAPO is responsible for setting the output stream's buffer flags
          //  and valid frame count.
          //
          //  This method should not block as it may be called from the
          //  realtime audio processing thread.
          //
          // PARAMETERS:
          //  OutputFrameCount - [in] number of output frames desired
          //
          // RETURN VALUE:
          //  UINT32 - number of input frames requried
          ////
        STDMETHOD_(UINT32, CalcInputFrames) (THIS_ UINT32 OutputFrameCount) PURE;

          ////
          // DESCRIPTION:
          //  Returns the number of output frames required to generate the
          //  given number of input frames.
          //
          // REMARKS:
          //  XAudio2 calls this method to determine how many output frames
          //  an XAPO requies.  This number is constant for CBR XAPOs and so
          //  this method need only be called once while an XAPO is locked.
          //
          //  This method should not block as it may be called from the
          //  realtime audio processing thread.
          //
          // PARAMETERS:
          //  InputFrameCount - [in] number of input frames desired
          //
          // RETURN VALUE:
          //  UINT32 - number of input frames requried
          ////
        STDMETHOD_(UINT32, CalcOutputFrames) (THIS_ UINT32 InputFrameCount) PURE;

          ////
          // DESCRIPTION:
          //  Enables an XAPO to process normally.
          //
          // REMARKS:
          //  XAPOs are initially considered enabled.
          //
          // PARAMETERS:
          //  void
          //
          // RETURN VALUE:
          //  void
          ////
        STDMETHOD_(void, Enable) (THIS) PURE;

          ////
          // DESCRIPTION:
          //  Disables an XAPO, putting it in thru mode.
          //
          // REMARKS:
          //  When in thru mode, an XAPO should not apply its regular
          //  DSP processing to the given streams during Process.  Rather
          //  it should pass data from input to output with as little
          //  modification as possible.
          //
          //  Effects that perform format conversion should continue to so.
          //  For example, a stereo to 5.1 upmixer should continue to upmix
          //  when in thru mode yet not perform dynamic effects such
          //  as arbitrary panning.
          //
          // PARAMETERS:
          //  void
          //
          // RETURN VALUE:
          //  void
          ////
        STDMETHOD_(void, Disable) (THIS) PURE;
    };



    // IXAPO:
    // An optional interface that allows an XAPO to use effect-specific
    // parameters.
    #undef INTERFACE
    #define INTERFACE IXAPOParameters
    DECLARE_INTERFACE_(IXAPOParameters, IUnknown)
    {
          ////
          // DESCRIPTION:
          //  Sets effect-specific parameters.
          //
          // REMARKS:
          //  An XAPO may assume the SetParameters call occurs on the
          //  realtime audio processing thread; no synchronization between it
          //  and XAPO::Process is necessary.
          //
          // PARAMETERS:
          //  pParameters        - [in] effect-specific parameter block
          //  pParameterByteSize - [in] size of pParameters in bytes
          //
          // RETURN VALUE:
          //  void
          ////
        STDMETHOD_(void, SetParameters) (THIS_ const void* pParameters, UINT32 ParameterByteSize) PURE;

          ////
          // DESCRIPTION:
          //  Gets effect-specific parameters.
          //
          // REMARKS:
          //  An XAPO may assume the GetParameters call occurs on the
          //  realtime audio processing thread; no synchronization between it
          //  and XAPO::Process is necessary.
          //
          // PARAMETERS:
          //  pParameters        - [in/out] receives effect-specific parameter block
          //  pParameterByteSize - [in] size of pParameters in bytes
          //
          // RETURN VALUE:
          //  void
          ////
        STDMETHOD_(void, GetParameters) (THIS_ void* pParameters, UINT32 ParameterByteSize) PURE;
    };


//--------------<M-A-C-R-O-S>-----------------------------------------------//
    // macros to allow XAPO interfaces to be used in C code
    #if !defined(__cplusplus)
        // IXAPO
        #define IXAPO_(This, riid, ppvObject) \
            ( (This)->lpVtbl->QueryInterface(This, riid, ppvObject) )

        #define IXAPO_AddRef(This) \
            ( (This)->lpVtbl->AddRef(This) )

        #define IXAPO_Release(This) \
            ( (This)->lpVtbl->Release(This) )

        #define IXAPO_GetRegistrationProperties(This, ppRegProps)   \
            ( (This)->lpVtbl->GetRegistrationProperties(This,ppRegProps) )

        #define IXAPO_IsInputFormatSupported(This, pOppositeFormat, pRequestedInputFormat, ppSupportedInputFormat)    \
            ( (This)->lpVtbl->IsInputFormatSupported(This, pOppositeFormat, pRequestedInputFormat, ppSupportedInputFormat) )

        #define IXAPO_IsOutputFormatSupported(This, pOppositeFormat, pRequestedOutputFormat, ppSupportedOutputFormat) \
            ( (This)->lpVtbl->IsOutputFormatSupported(This, pOppositeFormat, pRequestedOutputFormat, ppSupportedOutputFormat) )

        #define IXAPO_Initialize(This, cbDataSize, pbyData)  \
            ( (This)->lpVtbl->Initialize(This, cbDataSize, pbyData) )

        #define IXAPO_Reset(This)  \
            ( (This)->lpVtbl->Reset(This) )

        #define IXAPO_LockForProcess(This, NumInputConnections, ppInputConnections, NumOutputConnections, ppOutputConnections)  \
            ( (This)->lpVtbl->LockForProcess(This, NumInputConnections, ppInputConnections, NumOutputConnections, ppOutputConnections) )

        #define IXAPO_UnlockForProcess(This)  \
            ( (This)->lpVtbl->UnlockForProcess(This) )

        #define IXAPO_Process(This, NumInputConnections, ppInputConnections, NumOutputConnections, ppOutputConnections) \
            ( (This)->lpVtbl->APOProcess(This, NumInputConnections, ppInputConnections, NumOutputConnections, ppOutputConnections) )

        #define IXAPO_CalcInputFrames(This, OutputFrameCount)  \
            ( (This)->lpVtbl->CalcInputFrames(This, OutputFrameCount) )

        #define IXAPOParameters_Enable(This) \
            ( (This)->lpVtbl->Enable(This) )

        #define IXAPOParameters_Disable(This) \
            ( (This)->lpVtbl->Disable(This) )


        // IXAPOParameters
        #define IXAPOParameters_QueryInterface(This, riid, ppvObject) \
            ( (This)->lpVtbl->QueryInterface(This, riid, ppvObject) )

        #define IXAPOParameters_AddRef(This) \
            ( (This)->lpVtbl->AddRef(This) )

        #define IXAPOParameters_Release(This) \
            ( (This)->lpVtbl->Release(This) )

        #define IXAPOParameters_SetParameters(This, pParameters, uParametersByteSize) \
            ( (This)->lpVtbl->SetParameters(This, pParameters, uParametersByteSize) )

        #define IXAPOParameters_GetParameters(This, pParameters, uParametersByteSize)  \
            ( (This)->lpVtbl->GetParameters(This, pParameters, uParametersByteSize) )
    #endif // __cplusplus


    #pragma pack(pop) // revert packing alignment
#endif // GUID_DEFS_ONLY
//---------------------------------<-EOF->----------------------------------//
