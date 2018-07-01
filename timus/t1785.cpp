#include <iostream>
#include <string>
#include <vector>

struct range
{
    range(int min_, int max_, const std::string & term_) :
	min(min_), max(max_), term(term_) {}
    bool match(int value) const {
	return (min <= value) & (value <= max);
    }
    int min, max;
    std::string term;
};

int main(int argc, char *argv[])
{
    std::vector<range> ranges;
    ranges.reserve(9);
    int amount = 0;
    std::cin >> amount;

    ranges.emplace_back(1, 4, "few");
    ranges.emplace_back(5, 9, "several");
    ranges.emplace_back(10, 19, "pack");
    ranges.emplace_back(20, 49, "lots");
    ranges.emplace_back(50, 99, "horde");
    ranges.emplace_back(100, 249, "throng");
    ranges.emplace_back(250, 499, "swarm");
    ranges.emplace_back(500, 999, "zounds");
    ranges.emplace_back(1000, 2000, "legion");

    for (const auto &v : ranges) {
	if (v.match(amount))
	{
	    std::cout << v.term << std::endl;
	}
    }
    return 0;
}
