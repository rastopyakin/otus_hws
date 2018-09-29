#include <iostream>
#include <cmath>

int pos2number(int i, int j, int N) {
    int diag_number = i - j;
    int number = 0;
    for (int k = 1 - N; k <= diag_number; k++) {
        number += N - std::abs(k);
    }

    return number - (N - 1) + std::max(i, j);
}

int main(int argc, char *argv[]) {
    int N;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << pos2number(i, j, N);
            if (j < N-1)
                std::cout << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}
