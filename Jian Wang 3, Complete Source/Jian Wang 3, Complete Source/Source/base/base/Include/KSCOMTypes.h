#ifndef _KSCOMTYPES_H_
#define _KSCOMTYPES_H_ 1

#ifdef __cplusplus
extern "C"{
#endif

/* header files for imported files */
//#include "KSTypes.h"
#include "Ksdef.h"

#define __RPC_FAR


/* [local] */ 

#if (defined(_MSC_VER) || defined(__ICL))
#define MIDL_INTERFACE(x)   struct __declspec(uuid(x)) __declspec(novtable)
#else
#define MIDL_INTERFACE(x)   struct
#endif

#ifndef BEGIN_INTERFACE
    #define BEGIN_INTERFACE
#endif

#ifndef END_INTERFACE
    #define END_INTERFACE 
#endif

#ifndef interface
#define interface struct
#endif // interface

typedef long HRESULT;

#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct  _GUID
    {
    KSDWORD Data1;
    KSWORD  Data2;
    KSWORD  Data3;
    KSBYTE  Data4[ 8 ];
    }	GUID;

#define REFGUID const GUID &
#endif // GUID_DEFINED

#ifndef __IID_DEFINED__
#define __IID_DEFINED__
typedef GUID IID;

#define REFIID const IID &
#endif  // __IID_DEFINED__

#ifndef UUID_DEFINED
#define UUID_DEFINED
typedef GUID UUID;

#endif

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef GUID CLSID;

#define REFCLSID const CLSID &
#endif  // CLSID_DEFINED

#if 0
typedef GUID __RPC_FAR *REFGUID;

typedef IID __RPC_FAR *REFIID;

typedef CLSID __RPC_FAR *REFCLSID;

#endif


#ifndef _SYS_GUID_OPERATORS_
#define _SYS_GUID_OPERATORS_    1

inline int IsEqualGUID(const GUID &RGuid1, const GUID &RGuid2)
{
   return (
      ((unsigned long *) &RGuid1)[0] == ((unsigned long *) &RGuid2)[0] &&
      ((unsigned long *) &RGuid1)[1] == ((unsigned long *) &RGuid2)[1] &&
      ((unsigned long *) &RGuid1)[2] == ((unsigned long *) &RGuid2)[2] &&
      ((unsigned long *) &RGuid1)[3] == ((unsigned long *) &RGuid2)[3]);
}

inline int operator==(const GUID &GuidOne, const GUID &GuidOther)
{
    return IsEqualGUID(GuidOne, GuidOther);
}

inline int operator!=(const GUID &GuidOne, const GUID &GuidOther)
{
    return !(GuidOne == GuidOther);
}

#endif  // _SYS_GUID_OPERATORS_

#ifdef __cplusplus
}
#endif

#endif // _KSCOMTYPES_H_
