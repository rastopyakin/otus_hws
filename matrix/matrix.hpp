#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <array>
#include <map>
#include <vector>

template<class T, T def_val>
class Cell {
public:
    Cell & operator=(T val) {
        if (val != def_val) {
            m_val = val;
        }

        return *this;
    }
    operator T () {
        return m_val;
    }
private:
    T m_val = def_val;
};


using ind_t = std::size_t;

template<class T, T def_val, ind_t n_dim>
class MatrixNdim {
public:
    std::size_t size() const {
        return 0;
    }
    auto operator[] (ind_t ind) {
        return 0;
    }

private:
    std::vector<MatrixNdim<T, def_val, n_dim-1>> m;
};

template<class T, T def_val>
class MatrixNdim<T, def_val, 1> {
public:
    T operator[] (ind_t ind) {
        return 0;
    }
};


template<class T, T def_val>
using Matrix = MatrixNdim<T, def_val, 2>;

#endif /* MATRIX_HPP */
