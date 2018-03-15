#include <iostream>
#include <functional>

#include "ip_filter.hpp"


void show_ips(const ip_pool_t &pool) {
    for(const auto &ip : pool) {
	std::printf("%d.%d.%d.%d\n",
		    ip[0], ip[1], ip[2], ip[3]);
    }
}

int main(int argc, char const *argv[])
{
    try {
	ip_pool_t ip_pool;

	for(std::string line; std::getline(std::cin, line);) {
	    auto v = split(line, '\t');
	    ip_pool.push_back(str2ip(v.at(0)));
	}

	std::sort(ip_pool.begin(), ip_pool.end(), std::greater<ip_t>());

	show_ips(ip_pool);
	show_ips(filter(ip_pool, 1));
	show_ips(filter(ip_pool, 46, 70));
	show_ips(filter_any(ip_pool, 46));
    }
    catch(const std::exception &e)
    {
	std::cerr << e.what() << std::endl;
    }

    return 0;
}
