#include <iostream>
#include <cassert>
#include <array>
#include <map>
#include <tuple>

#include "matrix.hpp"

int main(int argc, char *argv[]) {

    Matrix<int, 3> matrix;
    assert(matrix.size() == 0);
    std::cout << matrix.size() << std::endl;

    Cell<int, 3> cell;
    // cell = 10;
    int m;
    m = cell;
    std::cout << "m = " << m << std::endl;
    return 0;
}
