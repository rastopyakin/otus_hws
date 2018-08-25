#include <iostream>

int main(int argc, char *argv[])
{
    int n, m;
    std::cin >> n >> m;

    if (n*m % 2 == 0)
	std::printf("[:=[first]\n");
    else
	std::printf("[second]=:]\n");
    return 0;
}
