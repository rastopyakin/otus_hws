#include <iostream>
#include <tuple>

#include "matrix.hpp"

int main(int argc, char *argv[]) {
    Matrix<int, 0> matrix;

    const int N = 9;

    for (int i = 0; i <= N; i++) {
        matrix[i][i] = i;
        matrix[i][N-i] = N - i;
    }

    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << matrix.size() << std::endl;

    int i, j, val;
    for (auto m : matrix) {
        std::tie(i, j, val) = m;
        std::printf("%d %d %d\n", i, j, val);
    }
    return 0;
}
