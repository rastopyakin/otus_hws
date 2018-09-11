#include <iostream>

#include "matrix.hpp"

int main(int argc, char *argv[]) {
    Matrix<int, 0> matrix;

    const int N = 9;

    for (int i = 0; i <= N; i++) {
        matrix[i][i] = i;
        matrix[i][N-i] = N - i;
    }

    std::cout << matrix.size() << std::endl;
    return 0;
}
