#include <iostream>
#include <cassert>
#include <array>
#include <map>
#include <tuple>

#include "matrix.hpp"

void test_cube() {
    Cube<int, 11> cube;
    std::cout << cube.size() << std::endl;

    std::cout << cube[2][3][4] << std::endl;
    cube[2][3][4] = 77;
    std::cout << cube[2][3][4] << std::endl;

    std::cout << cube[2][3][0] << std::endl;
    cube[2][2][0] = 44;
    std::cout << cube[2][3][0] << std::endl;
    std::cout << "cube size: " << cube.size() << std::endl;
    auto ic = cube.begin();
    // std::cout << "begin->second " << ic->second << std::endl;
    // ic++;
    // std::cout << "is_end: " << (ic == cube.end())<< "\n";
    // std::cout << "begin->second " << ic->second << std::endl;
}

void test_matrix() {
    Matrix<int, 3> matrix;

    std::cout << matrix.size() << std::endl;

    std::cout << matrix[2][4] << std::endl;
    matrix[2][4] = 100500;
    std::cout << matrix[2][4] << std::endl;

    matrix[2][17] = 23;

    std::cout << "matrix size: " << matrix.size() << std::endl;

    auto it = matrix.begin();
    // std::cout << "begin->second " << it->second << std::endl;
    // it++;
    // std::cout << "is_end: " << (it == matrix.end())<< "\n";
    // std::cout << "begin->second " << it->second << std::endl;
}

void test_vector() {
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
}

int main(int argc, char *argv[]) {

    test_vector();
    std::cout << "----------\n";

    // test_matrix();
    // std::cout << "----------\n";

    // test_cube();
    return 0;
}
