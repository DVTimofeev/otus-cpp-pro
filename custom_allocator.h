#pragma once
#include <iostream>
#include <memory>

namespace otus
{

template <class T>
struct alloc 
{
    using value_type = T;

    void* pool;
    static constexpr std::size_t PoolSize = 10;

    alloc () noexcept
        : pool(::operator new (sizeof(T) * PoolSize))
    {
    }

    template <class U> alloc(const alloc <U>& a) noexcept 
    {
        pool = a.pool;
    }

    T* allocate(std::size_t n)
    {
        static size_t alocated = 0;

        if ((n + alocated) > 10)
            throw std::bad_alloc();

        alocated += n;
        return static_cast<T*>(pool) + (alocated - n);
    }

    void deallocate(T* , std::size_t) noexcept
    {
        static size_t size = PoolSize;
        --size;
        if (!size)
            ::operator delete(pool);
    }

    template< class U >
    struct rebind
    {
        typedef alloc<U> other;
    };
};
} // namespace otus
