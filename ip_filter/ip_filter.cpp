#include "ip_filter.hpp"

ip_pool_t filter_any(const ip_pool_t &pool, std::string val) {
    ip_pool_t r {};

    for (const auto &ip: pool) {
	if (std::find(ip.begin(), ip.end(), val) != ip.end())
	    r.push_back(ip);
    }
    return r;
}

ip_t split(const std::string &str, char d)
{
    ip_t r;

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
