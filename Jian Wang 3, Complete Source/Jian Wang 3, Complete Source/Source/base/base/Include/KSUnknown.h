#ifndef _KSUNKNOWN_H_
#define _KSUNKNOWN_H_ 1

#ifdef _WIN32

#include <Unknwn.h>

#else   // POSIX

#ifdef __cplusplus
extern "C"{
#endif

/* header files for imported files */
#include "KSCOMTypes.h"

extern const IID IID_IUnknown;

    MIDL_INTERFACE("00000000-0000-0000-C000-000000000046")
    IUnknown
    {
    public:
        BEGIN_INTERFACE
        virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject) = 0;
        
        virtual ULONG STDMETHODCALLTYPE AddRef( void) = 0;
        
        virtual ULONG STDMETHODCALLTYPE Release( void) = 0;
        
        END_INTERFACE
    };

/* [local] */ 

typedef /* [unique] */ IUnknown __RPC_FAR *LPUNKNOWN;



extern const IID IID_IClassFactory;

    MIDL_INTERFACE("00000001-0000-0000-C000-000000000046")
    IClassFactory : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateInstance( 
            /* [unique][in] */ IUnknown *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE LockServer( 
            /* [in] */ int fLock) = 0;
        
    };

/* [local] */ 

typedef /* [unique] */ IClassFactory __RPC_FAR *LPCLASSFACTORY;




#ifdef __cplusplus
}
#endif

#endif  // _WIN32

#endif // _KSUNKNOWN_H_
