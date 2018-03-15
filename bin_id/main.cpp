#include <iostream>

constexpr int bin_id(int n) {
    if (n == 0) return 0;
    int steps = 0;
    bool isPowOf2 = true;
    while (n) {
	if (n%2 != 0)
	    if (n != 1)
		isPowOf2  = false;
	n /= 2;
	steps++;
    }
    return isPowOf2 ? (steps - 1) : steps;
}

static_assert(bin_id(0) == 0, "");
static_assert(bin_id(1) == 0, "");
static_assert(bin_id(2) == 1, "");
static_assert(bin_id(4) == 2, "");
static_assert(bin_id(7) == 3, "");
static_assert(bin_id(8) == 3, "");
static_assert(bin_id(9) == 4, "");
static_assert(bin_id(1023) == 10, "");
static_assert(bin_id(1024) == 10, "");
static_assert(bin_id(1025) == 11, "");
static_assert(bin_id(1024*1024-33) == 20, "");
static_assert(bin_id(1024*1024) == 20, "");
static_assert(bin_id(1024*1024+33) == 21, "");
static_assert(bin_id(1024*1024*1024-127) == 30, "");
static_assert(bin_id(1024*1024*1024) == 30, "");
static_assert(bin_id(1024*1024*1024+127) == 31, "");

int main(int argc, char *argv[])
{
    int n = 0;
    while (std::cin >> n) {
	std::printf("bin_id(%d) = %d\n", n, bin_id(n));
    }
    return 0;
}
