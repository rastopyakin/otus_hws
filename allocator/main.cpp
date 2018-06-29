#include <iostream>
#include <map>
#include <cassert>

#include "list.hpp"
#include "allocator.hpp"

template <class T>
constexpr T factorial(T i) {
    assert(i >= 0);
    return i == 0 ? 1 : i*factorial(i - 1);
}

int main(int argc, char *argv[])
{
    const int N = 10;
    std::printf("standart allocator map\n");
    std::map<int, int> m;
    for (int i = 0; i < N; i++)
	m.insert(std::make_pair(i, factorial(i)));

    std::printf("reserving allocator map\n");
    std::map<int, int, std::less<int>, reserving_allocator<std::pair<int, int>, N>> mc;
    for (int i = 0; i < N; i++)
	mc.insert(std::make_pair(i, factorial(i)));
    for (const auto &p : mc) {
      std::printf("%d %d\n", p.first, p.second);
    }

    std::printf("standart allocator list\n");
    tsk::list<int> l;
    for (int i = 0; i < N; i++)
	l.push_front(i);

    std::printf("reserving allocator list\n");
    tsk::list<int, reserving_allocator<int, N>> lc;
    for (int i = 0; i < N; i++)
	lc.push_front(i);

    for (const auto &p: lc)
	std::printf("%d\n", p);

    std::printf("the end!\n");
    return 0;
}
