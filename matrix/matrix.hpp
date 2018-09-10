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
    using child_type = MatrixNdim<T, def_val, n_dim-1>;
    using parent_type = MatrixNdim<T, def_val, n_dim+1>;

    MatrixNdim(parent_type * parent=nullptr) : m_parent(parent) {}
    std::size_t size() const {
        return 0;
    }
    child_type operator[] (ind_t ind) {
        auto result = childs.find(ind);
        if (result != childs.end())
            return result->second;
        index_candidate = ind;
        return child_type {this};
    }
    void store(child_type * child) {
        childs.insert(std::make_pair(index_candidate, *child));
        if (m_parent != nullptr)
            m_parent->store(this);
        std::cout << index_candidate << ",";
    }
private:
    std::map<ind_t, child_type> childs;
    ind_t index_candidate;
    parent_type * m_parent;
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
    using parent_type = MatrixNdim<T, def_val, 2>;
    using cell_type = Cell<T, def_val>;
    MatrixNdim(parent_type *parent=nullptr) : m_parent(parent) {}
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
        if (m_parent != nullptr)
            m_parent->store(this);
        std::cout << index_candidate << ": " << *cell << " is stored\n";
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
    parent_type * m_parent;
};

// inifinite instantiation ceiling
template<class T, T def_val>
class MatrixNdim<T, def_val, 5> {
public:
    using child_type = MatrixNdim<T, def_val, 4>;
    void store(child_type *) {}
};

template<class T, T def_val>
using Vector = MatrixNdim<T, def_val, 1>;


template<class T, T def_val>
using Matrix = MatrixNdim<T, def_val, 2>;

template<class T, T def_val>
using Cube = MatrixNdim<T, def_val, 3>;

#endif /* MATRIX_HPP */
