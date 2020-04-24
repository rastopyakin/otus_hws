#include <iostream>

int main(int argc, char *argv[])
{
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;

    int k = (c - a)/(b + d);
    if (a >= c) {
	std::cout << a << std::endl;
	return 0;
    }
    if (c - d*k >= a + b*(k + 1))
	std::cout << a + b*(k + 1) << std::endl;
    else
	std::cout << c - d*k << std::endl;
    return 0;
}
