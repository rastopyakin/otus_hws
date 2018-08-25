#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <string>

int main(int argc, char *argv[])
{
    std::vector<std::string> boxes = {"AOPR", "BMS", "DGJKTW"};

    int n_names;
    std::cin >> n_names;
    auto current_pos = boxes.begin();
    std::string name;
    int distance = 0;
    for (int i = 0;  i < n_names; ++ i) {
	std::cin >> name;
	for (auto pos = boxes.begin(); pos != boxes.end(); ++pos) {
	    if (pos->find(name.at(0)) != std::string::npos) {
		distance += std::abs(std::distance(pos, current_pos));
		current_pos = pos;
	    }
	}
    }
    std::printf("%d\n", distance);
    return 0;
}
