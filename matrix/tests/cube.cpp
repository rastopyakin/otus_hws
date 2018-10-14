#include "matrix.hpp"

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE matrix_cube

#include <vector>
#include <tuple>

BOOST_AUTO_TEST_CASE(cube) {
    Cube<int, 0> cube;
    std::vector<std::tuple<ind_t, ind_t, ind_t, int>> elems;

    elems.emplace_back(1, 2, 0, 2);
    elems.emplace_back(2, 3, 13, 100500);
    elems.emplace_back(10, 34, 5, 10);
    elems.emplace_back(23, 3, 2, -200);

    for (const auto& [i1, i2, i3, val] : elems)
        cube[i1][i2][i3] = val;
    BOOST_CHECK_EQUAL(cube.size(), elems.size());



    for (auto p  = std::make_pair(cube.begin(), elems.begin());
         p.first != cube.end();
         ++p.first, ++p.second) {
        auto [i1_v, i2_v, i3_v, val_v] = *p.first;
        auto [i1_e, i2_e, i3_e, val_e] = *p.second;
        BOOST_CHECK_EQUAL(i1_v, i1_e);
        BOOST_CHECK_EQUAL(i2_v, i2_e);
        BOOST_CHECK_EQUAL(i3_v, i3_e);

        BOOST_CHECK_EQUAL(val_v, val_e);
    }

    auto [i1, i2, i3, val] = elems.back();
    cube[i1][i2][i3] = 0;
    BOOST_CHECK_EQUAL(cube.size(), elems.size() - 1);
    BOOST_CHECK_EQUAL(cube[i1][i2][i3], 0);

}
