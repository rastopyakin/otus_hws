#include <iostream>
int main(int argc, char *argv[])
{
    int f = 0;
    std::cin >> f;
    if ((12 - f)*45 <= 240)
	std::printf("YES\n");
    else
	std::printf("NO\n");
    return 0;
}
