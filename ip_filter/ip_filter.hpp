#ifndef IP_FILTER_HPP
#define IP_FILTER_HPP

#include <vector>
#include <array>
#include <string>
#include <algorithm>

const int ip_length = 4;
using ip_t = std::array<int, ip_length>;
using ip_pool_t =  std::vector<ip_t>;

template <int P>
bool match(const ip_t &ip) {
    static_assert(P <= ip_length, "too many arguments");
    return true;
}

template <int P = 0, typename T, typename... Remained>
bool match(const ip_t &ip, T val, Remained... vals) {
    if (ip[P] == val)
	return match<P+1>(ip, vals...);
    else
	return false;
}

template <typename... Vals>
ip_pool_t filter(const ip_pool_t &pool, Vals... vals) {
    ip_pool_t r {};
    for (const auto &ip : pool)
	if (match(ip, vals...))
	    r.push_back(ip);
    return r;
}

ip_pool_t filter_any(const ip_pool_t &pool, int val);

std::vector<std::string> split(const std::string &str, char d);

ip_t str2ip(const std::string &s);

#endif /* IP_FILTER_HPP */
