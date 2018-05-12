#include <iostream>
#include <map>
#include <cassert>

template <class T>
constexpr T factorial(T i) {
    assert(i >= 0);
    return i == 0 ? 1 : i*factorial(i - 1);
}

int main(int argc, char *argv[])
{
    const int N = 10;
    std::map<int, int> m;
    for (int i = 0; i < N; i++)
	m.insert(std::make_pair(i, factorial(i)));

    for (const auto &p : m) {
      std::printf("%d %d\n", p.first, p.second);
    }


    std::printf("the end!\n");
    return 0;
}
