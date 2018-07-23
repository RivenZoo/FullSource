#ifndef _KMEMORY_H_
#define _KMEMORY_H_

#include <string>
#include <wchar.h>

// 1. 不要在全局对象构造中调用到这些函数(此时可能内存管理器尚未构造)
// 2. 这个内存分配器是线程安全的

namespace KMemory
{

ENGINE_API BOOL Initialize(const char cszFileName[]);
ENGINE_API void Finalize();

// Alloc, Free会在用户空间前保留一块空间用来保存size等信息,类似于C库的做法
ENGINE_API void* Alloc(size_t uSize);
ENGINE_API void  Free(void* pvAddr);

// RawAlloc, RawFree不会为内存块记住大小,用户要自己记住size
ENGINE_API void* RawAlloc(size_t uSize);
ENGINE_API void  RawFree(void* pvBlock, size_t uSize);

// 取得已经分配给用户的内存总量size
ENGINE_API size_t GetUsedSize();

template <typename T>
T* New()
{
    void* pvBlock = Alloc(sizeof(T));
    return new(pvBlock) T;
}

template <typename T>
void Delete(T* pObj)
{
    pObj->~T();
    Free(pObj);
}

template <typename T>
T* RawNew()
{
    void* pvBlock = RawAlloc(sizeof(T));
    return new(pvBlock) T;
}

// 小心: 用一个基类指针删除一个派生类对象会导致里面的sizeof不对,所以此时要转为真正的基类指针再删除
template <typename T>
void RawDelete(T* pObj)
{
    pObj->~T();
    RawFree(pObj, sizeof(T));
}

template<class T>
class KAllocator
{
public:
    typedef T                 value_type;
    typedef value_type*       pointer;
    typedef const value_type* const_pointer;
    typedef value_type&       reference;
    typedef const value_type& const_reference;
    typedef std::size_t       size_type;
    typedef std::ptrdiff_t    difference_type;

    template <class U> 
    struct rebind 
    { 
        typedef KAllocator<U> other;
    };

    KAllocator() {}

    KAllocator(const KAllocator&) {}

    template <class U>
    KAllocator(const KAllocator<U>&) {}

    ~KAllocator() {}

    pointer address(reference x) const { return &x; }

    const_pointer address(const_reference x) const { return &x; }

    pointer allocate(size_type Count, const_pointer = 0) 
    {
        return (pointer)KMemory::RawAlloc(sizeof(value_type) * Count);
    }

    void deallocate(pointer p, size_type Count)
    { 
        KMemory::RawFree(p, sizeof(value_type) * Count);
    }

    size_type max_size() const
    {
        return (size_type)(-1) / sizeof(value_type);
    }

    void construct(pointer p, const value_type& x)
    {
        new(p) value_type(x);
    }

    void destroy(pointer p)
    {
        p->~value_type();
    }

private:
    void operator=(const KAllocator&);
};

template<>
class KAllocator<void>
{
public:
    typedef void            value_type;
    typedef void*           pointer;
    typedef const void*     const_pointer;

    template <class U>
    struct rebind
    {
        typedef KAllocator<U> other;
    };

    KAllocator()
    {
        // construct default allocator (do nothing)
    }

    KAllocator(const KAllocator<value_type>&)
    {
        // construct by copying (do nothing)
    }

    template<class U>
    KAllocator(const KAllocator<U>&)
    {
        // construct from related allocator (do nothing)
    }

    template<class U>
    KAllocator<value_type>& operator=(const KAllocator<U>&)
    {
        // assign from a related allocator (do nothing)
        return (*this);
    }
};

template <class T>
inline bool operator==(const KAllocator<T>&, const KAllocator<T>&)
{
    return true;
}

template <class T>
inline bool operator!=(const KAllocator<T>&, const KAllocator<T>&)
{
    return false;
}

} // <-- namespace KMemory

typedef std::basic_string<char, std::char_traits<char>, KMemory::KAllocator<char> > kstring;
typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, KMemory::KAllocator<wchar_t> > kwstring;

// 为Map指定分配器示例:
// typedef KMemory::KAllocator<std::pair<DWORD, time_t> > KMAP_ALLOCATOR;
// typedef std::map<DWORD, time_t, less<DWORD>,  KMAP_ALLOCATOR> KSOME_MAP;

#endif

