#ifndef _KG_FILE_MAPPING_H_
#define _KG_FILE_MAPPING_H_

#include "KGPublic.h"
#include <Unknwn.h>

#ifdef WIN32
#define KG_MAP_READ     FILE_MAP_READ
#define KG_MAP_WRITE    FILE_MAP_WRITE
#else
#define 
#define KG_MAP_READ     PROT_READ
#define KG_MAP_WRITE    PROT_WRITE
#endif


struct IKG_FileMappingBuffer : IUnknown
{
    virtual size_t GetSize() = 0;
    virtual void *GetData() = 0;
};

struct IKG_FileMapping : IUnknown
{
    virtual int MapView(size_t uOffset, size_t uSize, IKG_FileMappingBuffer **ppRetBuffer) = 0;
    virtual int GetFileSize(size_t *puRetFileSize) = 0;
};

class KG_FileMappingBuffer : public IKG_FileMappingBuffer
{
public:
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject) { return E_FAIL; }
    virtual ULONG STDMETHODCALLTYPE AddRef();
    virtual ULONG STDMETHODCALLTYPE Release();

    virtual size_t GetSize() { return m_uSize; }
    virtual void *GetData() { return m_pvData; }
public:
    KG_FileMappingBuffer(
        IKG_FileMapping *piParentFileMapping,         
        size_t uSize,
        void *pvData,
        size_t uAlignedSize,
        void *pvAlignedData
    );
    virtual ~KG_FileMappingBuffer();
private:
    volatile long m_lRefCount;
    
    IKG_FileMapping *m_piFileMapping;
    void *m_pvData;
    size_t m_uSize;
    void *m_pvAlignedData;
    size_t m_uAlignedSize;
};

class KG_FileMapping : public IKG_FileMapping
{
public:
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject) { return E_FAIL; }
    virtual ULONG STDMETHODCALLTYPE AddRef();
    virtual ULONG STDMETHODCALLTYPE Release();

    virtual int MapView(size_t uOffset, size_t uSize, IKG_FileMappingBuffer **ppRetBuffer);
    virtual int GetFileSize(size_t *puRetFileSize);
public:
    KG_FileMapping(int nFile, KGHANDLE hFileMapping, unsigned uMapFlag);
    virtual ~KG_FileMapping();
private:
    volatile long m_lRefCount;

    int m_nFile;
    KGHANDLE m_hFileMapping;
    unsigned m_uMapFlag;
};

extern int KG_CreateFileMapping(const char cszFileName[], unsigned uMapFlag, IKG_FileMapping **ppRetFileMapping);

#endif //_KG_FILE_MAPPING_H_
