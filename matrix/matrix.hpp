#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <array>
#include <map>
#include <vector>

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
class Cell {
public:
    using parent_type = MatrixNdim<T, def_val, 1>;
    Cell(parent_type *parent) : m_parent(parent) {}

    Cell & operator=(T val) {
        if (val != def_val) {
            m_val = val;
            m_parent->store(this);
        }
        return *this;
    }
    operator T () const {
        return m_val;
    }
private:
    T m_val = def_val;
    parent_type * m_parent;
};

template<class T, T def_val>
class MatrixNdim<T, def_val, 1> {
public:
    using cell_type = Cell<T, def_val>;
    cell_type operator[] (ind_t ind) {
        auto result = cells.find(ind);
        if (result != cells.end())
            return result->second;
        index_candidate = ind;
        return Cell<T, def_val> {this};
    }
    auto size() {
        return cells.size();
    }
    void store(cell_type * cell) {
        cells.insert(std::make_pair(index_candidate, *cell));
        std::cout << "vec[" << index_candidate << "] = " << *cell << " is stored\n";
    }
    auto begin() {
        return cells.begin();
    }
    auto end() {
        return cells.end();
    }
private:
    std::map<ind_t, cell_type> cells;
    ind_t index_candidate;
};

template<class T, T def_val>
using Vector = MatrixNdim<T, def_val, 1>;


template<class T, T def_val>
using Matrix = MatrixNdim<T, def_val, 2>;

#endif /* MATRIX_HPP */
