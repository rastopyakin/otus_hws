#include <iostream>
#include <array>

unsigned int count(int N) {
    // N-th Fibonacci number multiplied by 2
    int b = 1;
    int result = b;
    for (int i = 2; i < N; i++) {
        result = b + result;
        b = result - b;
    }
    return result;
}

int main(int argc, char *argv[]) {
    int N;
    std::cin >> N;
    std::cout << 2*count(N) << std::endl;
    return 0;
}
