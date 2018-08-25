#include <iostream>

int main(int argc, char *argv[])
{
    int n = 0;
    std::cin >> n;
    if (n*(n + 1)/2 % 2 == 0)
	std::printf("black\n");
    else
	std::printf("grimy\n");
    return 0;
}
