#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <forward_list>
#include <array>
#include <cassert>

template <class T, int capacity>
class pool {
    std::array<unsigned char, capacity*sizeof(T)> chunk;
    std::size_t n_elem = 0;
public:
    T* allocate(std::size_t n) {
        assert(n <= capacity);
        std::size_t ind = n_elem;
        n_elem += n;
        return reinterpret_cast<T*>(&chunk[ind*sizeof(T)]);
    }
    std::size_t elems_available() {
        return capacity - n_elem;
    }
};

template <class T, int capacity = 10>
class reserving_allocator {
public:
    using value_type = T;

    template <class U>
    struct rebind {
        using other  = reserving_allocator<U, capacity>;
    };

    reserving_allocator() = default;

    template <class U, int N>
    reserving_allocator(const reserving_allocator<U, N> &a) {}

    T* allocate(std::size_t n) {
        if (pools.empty() or pools.front().elems_available() < n) {
            pools.emplace_front();
        }

        return pools.front().allocate(n);
    }
    void deallocate(T* p, std::size_t n) {}
    template <class U, class ... Args>
    void construct(U* p, Args&& ... args) {
        new(p) U(std::forward<Args>(args) ...);
    }
    void destroy(T* p) {
        p->~T();
    }
private:
    std::forward_list<pool<T, capacity>> pools;
};


#endif /* ALLOCATOR_HPP */
