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

    std::cout << std::endl;
    std::vector<Log> logs_v;
    // logs_v.emplace_back(Log{"x: "});
    for (int i = 0; i < 3; i++)
        logs_v.emplace_back(std::to_string(i) + "_v: ");
    for (const auto &p : logs_v)
        p.show();

    std::cout << std::endl;

    tsk::list<Log, reserving_allocator<Log, 3>> lc;
    for (int i = 0; i < N; i++)
        lc.emplace_back(std::to_string(i) + ": ");

    for (const auto &p: lc)
        p.show();

    std::cout << "\nthe end\n";
    return 0;
}
