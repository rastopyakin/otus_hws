#include <iostream>

int main(int argc, char *argv[])
{
    int k, n;
    std::cin >> n >> k;

    if (n < k)
	std::printf("%d\n", 2);
    else if ((2*n)%k == 0)
	std::printf("%d\n", (2*n)/k);
    else
	std::printf("%d\n", (2*n)/k + 1);
    return 0;
}
