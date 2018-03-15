#ifndef IP_FILTER_HPP
#define IP_FILTER_HPP

#include <vector>
#include <string>
#include <algorithm>

using ip_t = std::vector<int>;
using ip_pool_t =  std::vector<ip_t>;

inline bool match(const ip_t &ip) {
    return true;
}

template <typename T, typename... Args>
bool match(const ip_t &ip, T val, Args... args) {
    if (ip[0] == val)
	return match(ip_t{ip.begin() + 1, ip.end()}, args...);
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
