#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using base_t = unsigned long;
static const int P = 8;
using num_t = std::vector<base_t>;
static const base_t base = std::pow(10, P);
static const base_t denominator = 7;
static const base_t m0 = base%denominator;

int main(int argc, char *argv[])
{
    std::string num_str;
    std::cin >> num_str;
    num_t num;
    std::string tmp;
    tmp.reserve(P);
    std::reverse(num_str.begin(), num_str.end());
    for (const auto ch : num_str) {
	tmp = ch + tmp;
	if (tmp.length() == P) {
	    num.push_back(std::stoul(tmp));
	    tmp.clear();
	}
    }
    if (!tmp.empty())
	num.push_back(std::stoul(tmp));

    base_t m_ord = 1;
    base_t m = 0;
    for (auto a : num) {
	base_t m1 = a % denominator;
	base_t m2 = m_ord % denominator;
	m += m1*m2 % denominator;
	m_ord *= m0;
    }

    m %= denominator;

    std::cout << m << std::endl;
    return 0;
}
