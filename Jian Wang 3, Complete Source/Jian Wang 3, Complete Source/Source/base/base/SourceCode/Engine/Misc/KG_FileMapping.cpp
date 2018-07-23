#include "Precompile.h"
#include "KG_FileMapping.h"
#include "KGPublic.h"
#include "KG_InterlockedVariable.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

// Create KG_FileMapping
int KG_CreateFileMapping(const char cszFileName[], unsigned uMapFlag, IKG_FileMapping **ppRetFileMapping)
{
    int nResult = false;
    int nRetCode = false;
    int nOpenFlag = 0;
    int nFile = -1;

    KGHANDLE hFileMapping = NULL;
    KG_FileMapping *pFileMapping = NULL;

    KG_PROCESS_ERROR(cszFileName);
    KG_PROCESS_ERROR(ppRetFileMapping);

#ifdef WIN32
    nOpenFlag |= O_BINARY;
#endif // WIN32

    switch(uMapFlag & (KG_MAP_READ | KG_MAP_WRITE))
    {
    case KG_MAP_READ:
        nOpenFlag |= O_RDONLY;
    	break;
    case KG_MAP_WRITE:
        goto Exit0;
    case (KG_MAP_READ | KG_MAP_WRITE):
        nOpenFlag |= O_RDWR;
        break;
    default:
        goto Exit0;
    }

    nFile = open(cszFileName, nOpenFlag);
    KG_PROCESS_ERROR(nFile != -1);

#ifdef WIN32
    unsigned uProtectFlag = 0;
    switch(uMapFlag & (KG_MAP_READ | KG_MAP_WRITE))
    {
    case KG_MAP_READ:
        uProtectFlag |= PAGE_READONLY;
    	break;
    case KG_MAP_WRITE:
        goto Exit0;
    case (KG_MAP_READ | KG_MAP_WRITE):
        uProtectFlag |= PAGE_READWRITE;
        break;
    default:
        goto Exit0;
    }
    HANDLE hFile = (HANDLE)_get_osfhandle(nFile);
    hFileMapping = CreateFileMapping(hFile, NULL, uProtectFlag, 0, 0, NULL);
    KG_PROCESS_ERROR(hFileMapping);
#endif // WIN32

    pFileMapping = new KG_FileMapping(nFile, hFileMapping, uMapFlag);
    KG_PROCESS_ERROR(pFileMapping);
    nFile = -1;
    hFileMapping = NULL;

    *ppRetFileMapping = pFileMapping;
    pFileMapping = NULL;

    nResult = true;
Exit0:
    KG_DELETE(pFileMapping);

    if (nFile != -1)
    {
        close(nFile);
        nFile = -1;
    }

    if (!nResult)
    {
        if (ppRetFileMapping)
        {
            KG_COM_RELEASE(*ppRetFileMapping);
        }
    }
    return nResult;
}

KG_FileMappingBuffer::KG_FileMappingBuffer(
    IKG_FileMapping *piParentFileMapping,         
    size_t uSize,
    void *pvData,
    size_t uAlignedSize,
    void *pvAlignedData
)
{
    m_lRefCount = 1;
    ASSERT(piParentFileMapping);
    m_piFileMapping = piParentFileMapping;
    piParentFileMapping->AddRef();

    ASSERT(uSize <= uAlignedSize);
    ASSERT(pvData >= pvAlignedData);

    ASSERT(uSize);
    m_uSize = uSize;

    ASSERT(pvData);
    m_pvData = pvData;

    ASSERT(uAlignedSize);
    m_uAlignedSize = uAlignedSize;

    ASSERT(pvAlignedData);
    m_pvAlignedData = pvAlignedData;
}

KG_FileMappingBuffer::~KG_FileMappingBuffer()
{
    int nRetCode = false;
    m_uSize = 0;
    m_pvData = NULL;
#ifdef WIN32
    nRetCode = UnmapViewOfFile(m_pvAlignedData);
    ASSERT(nRetCode);
#else
    nRetCode = munmap(m_pvAlignedData, m_uAlignedSize);
    ASSERT(nRetCode == 0);
#endif
    m_uAlignedSize = 0;
    m_pvAlignedData = NULL;

    KG_COM_RELEASE(m_piFileMapping);
}

ULONG KG_FileMappingBuffer::AddRef()
{
    return KG_InterlockedIncrement((long *)&m_lRefCount);
}

ULONG KG_FileMappingBuffer::Release()
{
    long lRefCount = 0;

    lRefCount = KG_InterlockedDecrement((long *)&m_lRefCount);
    if (lRefCount == 0)
    {
        delete this;
        return 0;
    }

    return lRefCount;
}

//////////////////////////////////////////////////////////////////////////

KG_FileMapping::KG_FileMapping(int nFile, KGHANDLE hFileMapping, unsigned uMapFlag)
{
    m_lRefCount = 1;

    ASSERT(nFile > -1);
    m_nFile = nFile;

    m_hFileMapping = NULL;
#ifdef WIN32
    ASSERT(hFileMapping);
    m_hFileMapping = hFileMapping;
#endif // WIN32

    m_uMapFlag = uMapFlag;
}

KG_FileMapping::~KG_FileMapping()
{
    m_uMapFlag = 0;

#ifdef WIN32
    if (m_hFileMapping)
    {
        CloseHandle(m_hFileMapping);
        m_hFileMapping = NULL;
    }
#endif // WIN32
    
    if (m_nFile != -1)
    {
        close(m_nFile);
        m_nFile = -1;
    }
}

int KG_FileMapping::MapView(size_t uOffset, size_t uSize, IKG_FileMappingBuffer **ppRetBuffer)
{
    int         nResult             = false;
    int         nRetCode            = false;
    void       *pvMapView           = NULL;
    void       *pvData              = NULL;
    unsigned    uSystemPageSize     = 0;
    size_t      uAlignedSize        = 0;
    size_t      uAlignedOffset      = 0;
    KG_FileMappingBuffer *pFileMappingBuffer = NULL;
    

    KG_PROCESS_ERROR(ppRetBuffer);

    if (uSize == 0)
    {
        size_t uFileSize = 0;
        nRetCode = GetFileSize(&uFileSize);
        KG_PROCESS_ERROR(nRetCode);
        KG_PROCESS_ERROR(uOffset < uFileSize);

        uSize = uFileSize - uOffset;
        ASSERT(uSize != 0);
    }
    
    // 获取系统页大小
#ifdef WIN32
    SYSTEM_INFO sysInfo;

    GetSystemInfo(&sysInfo);
    uSystemPageSize = sysInfo.dwAllocationGranularity;
#else
    uSystemPageSize = (unsigned)getpagesize();
#endif 

    // 根据系统分页调整offset和size, windows下按系统的分配粒度对齐，否则按分页大小对齐
    uAlignedOffset = uOffset & ~(uSystemPageSize - 1);
    uAlignedSize = uSize + (uOffset - uAlignedOffset);

    // 映射内存
#ifdef WIN32
    pvMapView = MapViewOfFile(
        m_hFileMapping, 
        m_uMapFlag, 
        (unsigned)((unsigned long long)uAlignedOffset >> 32),
        (unsigned)(uAlignedOffset & 0xffffffff),
        uAlignedSize
    );
    KG_PROCESS_ERROR(pvMapView);
#else
    pvMapView = mmap(NULL, uAlignedSize, uMapFlag, MAP_SHARED, m_nFile, uAlignedOffset);
    KG_PROCESS_ERROR(pvMapView);
#endif 

    // 创建KG_FileMappingBuffer并返回接口
    pvData = (void *)((unsigned char *)pvMapView + (uOffset - uAlignedOffset));

    pFileMappingBuffer = new KG_FileMappingBuffer(this, uSize, pvData, uAlignedSize, pvMapView);
    KG_PROCESS_ERROR(pFileMappingBuffer);
    uSize = 0;
    pvData = NULL;
    uAlignedSize = 0;
    pvMapView = NULL;

    *ppRetBuffer = pFileMappingBuffer;
    pFileMappingBuffer = NULL;

    nResult = true;
Exit0:
    KG_DELETE(pFileMappingBuffer);

    if (pvMapView)
    {
#ifdef WIN32
        UnmapViewOfFile(pvMapView);
#else
        munmap(pvMapView, uAlignedSize);
#endif 
        pvMapView = NULL;
    }

    if (!nResult)
    {
        if (ppRetBuffer)
        {
            KG_COM_RELEASE(*ppRetBuffer);
        }
    }

    return nResult;
}

int KG_FileMapping::GetFileSize(size_t *puRetFileSize)
{
    int nResult = false;
    int nRetCode = false;

#ifdef WIN32
    struct _stat64 statInfo;
    
    KG_PROCESS_ERROR(puRetFileSize);

    nRetCode = _fstat64(m_nFile, &statInfo);
    KG_PROCESS_ERROR(nRetCode == 0);

    *puRetFileSize = (size_t)statInfo.st_size;
#else
    struct stat statInfo;

    KG_PROCESS_ERROR(puRetFileSize);

    nRetCode = fstat(m_nFile, &statInfo);
    KG_PROCESS_ERROR(nRetCode == 0);

    *puRetFileSize = statInfo.st_size;
#endif

    nResult = true;
Exit0:
    return nResult;
}

ULONG KG_FileMapping::AddRef()
{
    return KG_InterlockedIncrement((long *)&m_lRefCount);
}

ULONG KG_FileMapping::Release()
{
    long lRefCount = 0;

    lRefCount = KG_InterlockedDecrement((long *)&m_lRefCount);
    if (lRefCount == 0)
    {
        delete this;
        return 0;
    }

    return lRefCount;
}
