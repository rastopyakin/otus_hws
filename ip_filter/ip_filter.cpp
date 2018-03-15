#include "ip_filter.hpp"

ip_pool_t filter_any(const ip_pool_t &pool, int val) {
    ip_pool_t r {};

    for (const auto &ip: pool) {
	if (std::find(ip.begin(), ip.end(), val) != ip.end())
	    r.push_back(ip);
    }
    return r;
}

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string>  r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
	r.push_back(str.substr(start, stop - start));
	start = stop + 1;
	stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));
    return r;
}

ip_t str2ip(const std::string &s) {
    ip_t r;
    auto v = split(s, '.');
    int ind = 0;
    for (const auto &ip_part : v)
	r[ind++] = std::stoi(ip_part);
    return r;
}
