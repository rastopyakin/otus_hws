#include <iostream>
#include <string>
#include <forward_list>
#include <vector>

#include "list.hpp"
#include "allocator.hpp"
#include "log.hpp"

template <class T>
constexpr T factorial(T i) {
    assert(i >= 0);
    return i == 0 ? 1 : i*factorial(i - 1);
}

int main(int argc, char *argv[])
{
    const int N = 5;
    std::cout << "Test everything!\n";

    reserving_allocator<Log, 3> a;
    auto p1 = a.allocate(2);
    std::printf("p1 = %p\n", p1);
    new(&p1[0]) Log{"p1[0]: "};
    new(&p1[1]) Log{"p1[1]: "};
    p1[0].show(); p1[1].show();

    auto p2 = a.allocate(2);
    std::printf("p2 = %p\n", p2);
    new(&p2[0]) Log{"p2[0]: "};
    new(&p2[1]) Log{"p2[1]: "};
    p2[0].show(); p2[1].show();

    auto p3 = a.allocate(5);
    std::printf("p3 = %p\n", p3);
    new(&p3[0]) Log{"p3[0]: "};
    p3->show();
    std::cout << std::endl;

    tsk::list<Log, reserving_allocator<Log, 3>> lc;
    for (int i = 0; i < N; i++)
        lc.emplace_back(std::to_string(i) + ": ");

    for (const auto &p: lc)
        p.show();

    std::cout << "\nthe end\n";
    return 0;
}
