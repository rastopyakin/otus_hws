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
    big_num(const big_num&) = default;
    big_num(big_num&& other)
	: num(std::move(other.num)) {}
    big_num & operator=(const big_num&) = default;
    // big_num & operator=(big_num&& other) {
    // 	num = std::move(other.num);
    // 	return *this;
    // }

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
	bool carry_flag = false;
	int index = 0;
	for (auto it = other.num.begin(); it != other.num.end() || carry_flag; index++) {
	    if (num.size() < index + 1)
		num.push_back(0);
	    if (it != other.num.end()) {
		num[index] += *it;
		it++;
	    }
	    if (carry_flag) {
		num[index]++;
		carry_flag = false;
	    }
	    if (num[index] >= base) {
		num[index] -= base;
		carry_flag = true;
	    }

	}
	return *this;
    }
    big_num & operator*=(const big_num& other) {
	base_t carry_value = 0;
	auto old_val = std::move(num);
	big_num tmp{};
	tmp.reserve(23);
	this->reserve(23);
	for (int i = 0; i < old_val.size(); i++) {
	    tmp.num.assign(i, 0);
	    carry_value = 0;
	    for (int j = 0; j < other.num.size(); j++) {
		auto prod = old_val[i]*other.num[j];
		auto candidate = prod%base + carry_value;
		tmp.num.push_back(candidate%base);
		carry_value = prod/base + candidate/base;
	    }
	    if (carry_value != 0)
		tmp.num.push_back(carry_value);
	    *this += tmp;
	}
	return *this;
    }
    friend big_num operator*(big_num lhs, const big_num& rhs) {
	lhs *= rhs;
	return lhs;
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

auto pow_b(const big_num& num, std::size_t n) {
    big_num seed {"1"};
    for (int i = 0; i < n; i++)
	seed *= num;
    return seed;
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
    // unity.reserve(23);
    // big_num a{"3"}, b{"4"}, c{"5"};
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

    // std::vector<int> v1, v2;
    // v1.reserve(10);
    // v1.push_back(10);
    // v2 = std::move(v1);
    // // v2 = v1;
    // std::cout << v2.capacity() << "\n";
    // return 0;
}
