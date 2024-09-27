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

// - Опционально реализовать расширяемость аллокатора. При попытке выделить число элементов, которое превышает текущее зарезервированное количество, аллокатор расширяет зарезервированную память.
    T* allocate(std::size_t n)
    {
        static size_t alocated = 0;

        if ((n + alocated) > PoolSize)
            throw std::bad_alloc();

        alocated += n;
        return static_cast<T*>(pool) + (alocated - n);
    }

// - Опционально реализовать поэлементное освобождение.
    void deallocate(T* , std::size_t) noexcept
    {
        static size_t size = PoolSize;
        --size;
        if (!size)
            ::operator delete(pool);
    }

    template <class U, class ...Args>
    void
    construct(U* p, Args&& ...args)
    {
        ::new(p) U(std::forward<Args>(args)...);
    }

    template< class U >
    struct rebind
    {
        typedef alloc<U> other;
    };
};
} // namespace otus
