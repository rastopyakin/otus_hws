#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

int main(int argc, char *argv[])
{
    int N = 0;
    std::cin >> N;
    std::vector<std::string> dictionary;
    dictionary.reserve(N);
    dictionary.resize(N);
    for (auto & sign : dictionary)
	std::cin >> sign;

    std::string entered_sign;
    std::cin >> entered_sign;

    std::sort(dictionary.begin(), dictionary.end());

    auto p = std::equal_range(
	dictionary.begin(), dictionary.end(), entered_sign,
	[] (auto s1, auto s2) {
	    return s1 < s2.substr(0, s1.length());
	});

    std::copy(p.first, p.second,
	      std::ostream_iterator<std::string>(std::cout, "\n"));
    return 0;
}
