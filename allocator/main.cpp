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
    const int N = 3;
    std::map<int, int> m;
    for (int i = 0; i < N; i++)
	m.insert(std::make_pair(i, factorial(i)));

    for (const auto &p : m) {
      std::printf("%d %d\n", p.first, p.second);
    }

    tsk::list<int> l;
    for (int i = 0; i < N; i++)
	l.push_front(i);

    for (const auto &p: l)
	std::printf("%d\n", p);

    std::printf("the end!\n");
    return 0;
}
