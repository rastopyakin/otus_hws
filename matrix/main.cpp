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

    Cell<int, 3> cell {nullptr};
    // cell = 10;
    int m;
    m = cell;
    std::cout << "m = " << m << std::endl;

    Vector<int, 4> vec;
    std::cout << "vec[4] = " <<  vec[4] << std::endl;

    vec[3] = 333;

    std::cout << "vec[4] = " <<  vec[4] << std::endl;
    std::cout << "vec[7000] = " <<  vec[7000] << std::endl;
    vec[537] = 7777;
    vec[17] = 34;
    std::cout << "vec[17] = " << vec[17] << std::endl;
    std::cout << "vec[11] = " << vec[11] << std::endl;
    vec[19] = -3;
    std::cout << "vec[3] = " << vec[3] << std::endl;

    for (auto c : vec) {
        ind_t ind;
        int v;
        std::tie(ind, v) = c;
        std::cout << ind << " " << v << std::endl;
    }
    std::cout << vec.size() << std::endl;
    return 0;
}
