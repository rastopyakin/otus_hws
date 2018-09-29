#include <iostream>
#include <cmath>

int main(int argc, char *argv[]) {
    int N;
    std::cin >> N;
    std::cout << (1 + N)*(1 + std::abs(1 - N))/2 << std::endl;
    return 0;
}
