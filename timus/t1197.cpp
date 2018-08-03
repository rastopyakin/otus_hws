#include <iostream>
#include <string>
#include <vector>
#include <cmath>

struct position_t {
    int x = 0, y = 0;
    bool available() {
	return 0 <= x && x <= 7 && 0 <= y && y <= 7;
    }
    position_t moved(int dx, int dy) {
	return position_t{x + dx, y + dy};
    }
};
int main(int argc, char *argv[])
{
    int n_tests = 0;
    std::cin >> n_tests;
    std::vector<std::string> tests;
    tests.reserve(n_tests);
    tests.resize(n_tests);

    for (auto & test : tests)
	std::cin >> test;
    position_t pos;
    int moves_num = 0;
    for (const auto & test : tests) {
	pos = {test.at(0) - 'a', test.at(1) - '1'};
	moves_num = 0;
	for (auto dx : {-2, -1, 2, 1})
	    for (auto dy : {-2, -1, 2, 1})
		if (std::abs(dx) != std::abs(dy))
		    moves_num += pos.moved(dx, dy).available();
	std::printf("%d\n", moves_num);
    }

    return 0;
}
