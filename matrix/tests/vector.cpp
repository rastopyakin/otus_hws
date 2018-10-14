#include "matrix.hpp"

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE matrix_vector

#include <vector>
#include <tuple>

BOOST_AUTO_TEST_CASE(vector) {
    Vector<int, 0> vec;
    std::vector<std::tuple<ind_t, int>> elems;

    elems.emplace_back(5, 10);
    elems.emplace_back(13, 100500);
    elems.emplace_back(100, 2);
    elems.emplace_back(100500, -200);

    for (const auto& [ind, val] : elems)
        vec[ind] = val;
    BOOST_CHECK_EQUAL(vec.size(), elems.size());

    int val = 3;
    ind_t ind = 111;
    vec[ind] = val;
    BOOST_CHECK_EQUAL(vec.size(), elems.size() + 1);
    BOOST_CHECK_EQUAL(vec[ind], val);
    vec[ind] = 0;
    BOOST_CHECK_EQUAL(vec[ind], 0);
    BOOST_CHECK_EQUAL(vec.size(), elems.size());

    for (auto p  = std::make_pair(vec.begin(), elems.begin());
         p.first != vec.end(); ++p.first, ++p.second) {
        auto [ind_vec, val_vec] = *p.first;
        auto [ind_elems, val_elems] = *p.second;
        BOOST_CHECK_EQUAL(ind_vec, ind_elems);
        BOOST_CHECK_EQUAL(val_vec, val_elems);
    }
}
