#include <iostream>
#include <cassert>
#include <array>
#include <map>
#include <tuple>

#include "matrix.hpp"

int main(int argc, char *argv[]) {


    Cube<int, 11> cube;
    std::cout << cube.size() << std::endl;

    std::cout << cube[2][3][4] << std::endl;
    cube[2][3][4] = 77;
    std::cout << cube[2][3][4] << std::endl;

    std::cout << cube[1][0][0] << std::endl;
    cube[1][0][0] = 44;
    std::cout << cube[1][0][0] << std::endl;
    std::cout << "cube size: " << cube.size() << std::endl;

    std::cout << "----------\n";
    Matrix<int, 3> matrix;
    std::cout << matrix.size() << std::endl;

    std::cout << matrix[2][4] << std::endl;
    matrix[2][4] = 100500;
    std::cout << matrix[2][4] << std::endl;

    matrix[11][17] = 23;

    std::cout << "matrix size: " << matrix.size() << std::endl;

    std::cout << "----------\n";
    Vector<int, 4> vec;
    std::cout << "vec[4] = " <<  vec[4] << std::endl;

    vec[3] = 333;

    std::cout << "vec[4] = " <<  vec[4] << std::endl;
    std::cout << "vec[7000] = " <<  vec[7000] << std::endl;
    vec[537] = 7777;
    vec[17] = 34;
    vec[17] = 50;
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
