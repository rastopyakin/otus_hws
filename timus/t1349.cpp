#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

class big_num {
public:
    big_num() {}
    big_num(std::string num_str) {
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

    }

    void reserve(std::size_t n_elem) {
	num.reserve(n_elem);
    }

    bool operator==(const big_num& other) const {
	return num == other.num;
    }
    bool operator<(int val) const {
	return num[0] < val;
    }
    big_num& operator+=(const big_num& other) {
	base_t carry_value = 0;
	int index = 0;
	for (int j = 0; j < other.num.size() || carry_value; index++) {
	    if (num.size() < index + 1)
	    	num.push_back(0);
	    if (j != other.num.size()) {
		num[index] += other.num[j];
		j++;
	    }
	    num[index] += carry_value;
	    carry_value = num[index]/base;
	    num[index] %= base;
	}
	return *this;
    }

    friend big_num operator*(const big_num & a, const big_num& b) {
	base_t carry_value = 0;
	big_num retval {};
	retval.reserve(a.num.size() + b.num.size());
	big_num tmp{};
	tmp.reserve(a.num.size() + b.num.size());
	for (int i = 0; i < a.num.size(); i++) {
	    tmp.num.assign(i, 0);
	    carry_value = 0;
	    for (int j = 0; j < b.num.size(); j++) {
		auto prod = a.num[i]*b.num[j];
		auto candidate = prod%base + carry_value;
		tmp.num.push_back(candidate%base);
		carry_value = prod/base + candidate/base;
	    }
	    if (carry_value)
		tmp.num.push_back(carry_value);
	    retval += tmp;
	}
	return retval;
    }
    friend big_num operator+(big_num lhs, const big_num& rhs) {
	lhs += rhs;
	return lhs;
    }
    friend std::ostream & operator<<(std::ostream &os, const big_num &num);
private:
    using base_t = unsigned long;
    static const int P = 9;
    static const base_t base = std::pow(10, P);
    using num_t = std::vector<base_t>;
private:
    num_t num;
};

std::ostream & operator<<(std::ostream &os, const big_num &num) {
    std::string tmp = std::to_string(num.num.back());
    os << tmp;
    for (auto it = num.num.crbegin() + 1; it != num.num.crend(); it++) {
	tmp = std::to_string(*it);
	os << std::string(big_num::P - tmp.length(), '0');
	os << tmp;
    }
    return os;
}

auto pow_b_2(const big_num& num, std::size_t n) {
    // if (n == 1) return 1;
    if (n == 1) return num;
    if (n%2 == 1)
	return pow_b_2(num, n - 1)*num;
    else {
	auto half_powered = pow_b_2(num, n/2);
	return half_powered*half_powered;
    }
}

int main(int argc, char *argv[])
{
    int n = 0;
    std::cin >> n;
    big_num unity {"1"};
    big_num a, b, c;
    // a.reserve(23);
    // b.reserve(23);
    // c.reserve(23);
    bool found = false;
    for (a = unity; !found && a < 100; a += unity) {
    	for (b = a + unity; !found && b < 100; b += unity) {
    	    for (c = b + unity; !found && c < 100; c += unity)
    		if (pow_b_2(a, n) + pow_b_2(b, n) == pow_b_2(c, n)) {
    		    found = true;
    		    break;
    		}
    	    if (found) break;
    	}
    	if (found) break;
    }
    if (found)
    	std::cout << a << ' ' << b << ' ' << c << '\n';
    else
    	std::cout << -1 << "\n";

    // std::string str;
    // std::cin >> str;
    // big_num a {str};
    // std::cin >> str;
    // big_num b {str};
    // a.reserve(23);
    // std::cout << a + b << "\n";
    // std::vector<int> v1, v2;
    // v1.reserve(10);
    // v1.push_back(10);
    // // v2 = std::move(v1);
    // // v2 = v1;
    // v1.assign(5, 0);
    // std::cout << v1.capacity() << "\n";
    // return 0;
}
