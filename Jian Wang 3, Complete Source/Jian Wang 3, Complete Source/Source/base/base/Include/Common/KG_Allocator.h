//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG_Allocator.h
//  Version     :   1.0
//  Creater     :   Chen Jie, Freeway Chen
//  Date        :   2006-8-2 11:34:19
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KG_ALLOCATOR_H_
#define _KG_ALLOCATOR_H_    1

#include <new>
#include "KGPublic.h"
#include "KG_Memory.h"


template<typename _Tp, unsigned _uSizeArrayCount, unsigned _uSizeArray[]>
class KG_allocator
{
private:
    static KG_Memory<_uSizeArrayCount, _uSizeArray> s_Alloc;

public:
    typedef size_t     size_type;
    typedef ptrdiff_t  difference_type;
    typedef _Tp*       pointer;
    typedef const _Tp* const_pointer;
    typedef _Tp&       reference;
    typedef const _Tp& const_reference;
    typedef _Tp        value_type;

    template<typename _Tp1>
        struct rebind
        { typedef KG_allocator<_Tp1, _uSizeArrayCount, _uSizeArray> other; };

    KG_allocator() throw() { }

    KG_allocator(const KG_allocator& Copy_allocator) throw() { }

    template<typename _Tp1, unsigned _uSizeArrayCount, unsigned _uSizeArray[]>
        KG_allocator(const KG_allocator<_Tp1, _uSizeArrayCount, _uSizeArray>& Related_allocator) throw() { }

    ~KG_allocator() throw() { }

    pointer
    address(reference __x) const { return &__x; }

    const_pointer
    address(const_reference __x) const { return &__x; }

    // NB: __n is permitted to be 0.  The C++ standard says nothing
    // about what the return value is when __n == 0.
    pointer
    allocate(size_type __n, const void* = 0)
    { 
        //if (__builtin_expect(__n > this->max_size(), false))
        //  std::__throw_bad_alloc();
        if (__n > max_size())
        {
            throw(std::bad_alloc());
        }

        // allocate storage for _Count elements of type _Ty
        return static_cast<_Tp *>(s_Alloc.Alloc((UINT)__n * sizeof(_Tp)));
    }

    // __p is not permitted to be a null pointer.
    void
    deallocate(pointer __p, size_type)
    {
        if (!__p)
            return;

        s_Alloc.Free(__p);
    }

    size_type
    max_size() const throw() 
    { return size_t(-1) / sizeof(_Tp); }

    // _GLIBCXX_RESOLVE_LIB_DEFECTS
    // 402. wrong new expression in [some_] allocator::construct
    void 
    construct(pointer __p, const _Tp& __val) 
    { ::new(__p) _Tp(__val); }

    void 
    destroy(pointer __p) { __p->~_Tp(); }
};

template<typename _Tp, unsigned _uSizeArrayCount, unsigned _uSizeArray[]>
    KG_Memory<_uSizeArrayCount, _uSizeArray> KG_allocator<_Tp, _uSizeArrayCount, _uSizeArray>::s_Alloc;

template<typename _Tp, unsigned _uSizeArrayCount, unsigned _uSizeArray[]>
inline bool operator==(
    const KG_allocator<_Tp, _uSizeArrayCount, _uSizeArray>&, 
    const KG_allocator<_Tp, _uSizeArrayCount, _uSizeArray>&
)
{
    return true;
}

template<typename _Tp, unsigned _uSizeArrayCount, unsigned _uSizeArray[]>
inline bool operator!=(
    const KG_allocator<_Tp, _uSizeArrayCount, _uSizeArray>&, 
    const KG_allocator<_Tp, _uSizeArrayCount, _uSizeArray>&
)
{
    return false;
}
#endif
