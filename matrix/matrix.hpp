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
    using iterator_type = typename std::map<ind_t, child_type>::iterator;

    MatrixNdim(parent_type * parent=nullptr) : m_parent(parent) {}

    class iterator {
    public:
        using child_iterator_type = typename child_type::iterator;
        iterator(iterator_type it, child_iterator_type ch_it)
            : m_internal(it), child(ch_it) {}
        auto& operator++() {
            ++child;
            if (not (child != m_internal->second.end())) {
                m_internal++;
                child = m_internal->second.begin();
            }
            return *this;
        }
        auto operator*() const {
            ind_t ind = m_internal->first;
            return std::tuple_cat(std::make_tuple(ind), *child);
        }
        bool operator!=(const iterator &other) const {
            return m_internal != other.m_internal;
        }
    private:
        iterator_type m_internal;
        child_iterator_type child;
    };

    auto begin() {
        return iterator{childs.begin(), childs.begin()->second.begin()};
    }
    auto end() {
        return iterator{childs.end(), childs.begin()->second.end()};
    }

    std::size_t size() const {
        std::size_t result = 0;
        for (const auto& child : childs)
            result += child.second.size();
        return result;
    }
    child_type operator[] (ind_t ind) {
        index_candidate = ind;
        auto result = childs.find(ind);
        if (result != childs.end())
            return result->second;
        return child_type {this};
    }
    void store(child_type * child) {
        childs.insert_or_assign(index_candidate, *child);
        if (m_parent != nullptr)
            m_parent->store(this);
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
    using iterator_type = typename std::map<ind_t, cell_type>::iterator;

    MatrixNdim(parent_type *parent=nullptr) : m_parent(parent) {}

    cell_type operator[] (ind_t ind) {
        index_candidate = ind;
        auto result = cells.find(ind);
        if (result != cells.end())
            return result->second;
        return Cell<T, def_val> {this};
    }
    auto size() const {
        return cells.size();
    }
    void store(cell_type * cell) {
        cells.insert_or_assign(index_candidate, *cell);
        if (m_parent != nullptr)
            m_parent->store(this);
    }

    class iterator {
    public:
        iterator(iterator_type it) : m_internal(it) {}
        iterator& operator++() {
            m_internal++;

            return *this;
        }
        auto& operator*() const {
            return *m_internal;
        }
        bool operator!=(const iterator &other) const {
            return m_internal != other.m_internal;
        }
    private:
        iterator_type m_internal;
    };
    auto begin() {
        return iterator{cells.begin()};
    }
    auto end() {
        return iterator{cells.end()};
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
