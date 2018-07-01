#include <cmath>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    long number = 0;
    std::vector<double> roots;

    while (std::cin >> number) {
	roots.push_back(std::sqrt(number));
    }
    std::cout.precision(4);
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    for (auto it = roots.rbegin(); it != roots.rend(); ++it) {
	std::cout << *it << std::endl;
    }
    return 0;
}
