#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <vector>
#include <array>
#include <iostream>

template <class T, int capacity>
struct pool {
    std::array<unsigned char, capacity*sizeof(T)> chunk;
    auto & operator[](std::size_t ind) {
        return chunk[ind*sizeof(T)];
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
        if ((n_elem + n) > capacity*pools.size()) {
            pools.emplace_back();
            std::printf("new pool\n");
        }

        std::printf("allocate(%lu)\n", n);
        int pool_num = n_elem/capacity;
        int ind = n_elem%capacity;
        n_elem += n;

        return reinterpret_cast<T*>(&pools[pool_num][ind]);
        std::printf("pool_num = %d, ind = %d, n_elem = %d\n", pool_num, ind, n_elem);
    }
    void deallocate(T* p, std::size_t n) {}
    template <class U, class ... Args>
    void construct(U* p, Args&& ... args) {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
        new(p) U(std::forward<Args>(args) ...);
    }
    void destroy(T* p) {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
        p->~T();
    }
private:
    int n_elem = 0;
    std::vector<pool<T, capacity>> pools;
};


#endif /* ALLOCATOR_HPP */
