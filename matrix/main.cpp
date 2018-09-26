#include <iostream>
#include <cassert>
#include <array>
#include <map>
#include <tuple>

#include "matrix.hpp"

void test_cube() {
    Cube<int, 0> cube;
    std::cout << cube.size() << std::endl;

    // std::cout << cube[2][3][4] << std::endl;
    cube[2][3][4] = 77;
    // std::cout << cube[2][3][4] << std::endl;

    // std::cout << cube[1][2][0] << std::endl;
    cube[1][2][0] = 44;
    // std::cout << cube[1][2][0] << std::endl;

    cube[0][1][50] = -13;
    cube[23][3][1] = 111;
    cube[23][3][2] = 7;

    std::cout << "cube size: " << cube.size() << std::endl;

    int i, j, k, v;
    for (auto c : cube) {
        std::tie(i, j, k, v) = c;
        std::cout << i << ", " << j << ", " << k << ", " << v << std::endl;
    }
    std::cout << std::endl;
    cube[23][3][2] = 0;
    std::cout << cube[23][3][2] << std::endl;
    for (auto c : cube) {
        std::tie(i, j, k, v) = c;
        std::cout << i << ", " << j << ", " << k << ", " << v << std::endl;
    }

    std::cout << "cube size: " << cube.size() << std::endl;
}

void test_matrix() {
    Matrix<int, 0> matrix;

    // std::cout << matrix[1][4] << std::endl;
    matrix[1][4] = 100500;
    std::cout << "----\n";
    matrix[2][1] = 111;
    std::cout << "----\n";
    std::cout << matrix[1][4] << std::endl;
    std::cout << matrix[2][1] << std::endl;
    std::cout << "----\n";
    matrix[2][1] = 0;
    matrix[2][7] = -111;
    matrix[7][7] = 11;
    std::cout << "matrix size: " << matrix.size() << std::endl;

    int i, j, v;
    for (auto c : matrix) {
        std::tie(i, j, v) = c;
        std::cout << i << ", " << j << ", " << v << std::endl;
    }
    std::cout << "-----\n";
}

void test_vector() {
    Vector<int, 0> vec;
    vec[3] = 333;

    vec[537] = 7777;
    vec[17] = 34;
    std::cout << "---\n";
    vec[3] = 0;

    std::cout << "vec[3] = " <<  vec[3] << std::endl;

    std::cout << "---\n";
    for (auto c : vec) {
        ind_t ind;
        int v;
        std::tie(ind, v) = c;
        std::cout << ind << " " << v << std::endl;
    }
    std::cout << "size: " << vec.size() << std::endl;
}

class log {
public:
    log(int val) : m_val(val) {std::cout << m_val << ": new\n";}
    log(const log &other) : m_val(other.m_val) {std::cout << m_val << ": copied\n";}
    ~log() {std::cout << m_val << ": died\n";}
    operator int() const {return m_val;}
private:
    int m_val;
};

log make_log(int i) {
    return log{i};
}

const log & log_returner(const std::map<int, log>& m) {
    std::cout << "call m->second\n";
    return m.begin()->second;
}
int main(int argc, char *argv[]) {

    // std::cout << make_log(11) << std::endl;

    test_vector();
    std::cout << "----------\n";

    test_matrix();
    std::cout << "----------\n";

    test_cube();
    return 0;
}
