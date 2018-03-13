#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

typedef std::vector<std::string> ip_t;
typedef std::vector<ip_t> ip_pool_t;

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

bool compare(const ip_t &ip1, const ip_t &ip2) {
	return std::lexicographical_compare(
		ip1.begin(), ip1.end(), ip2.begin(), ip2.end(),
		[](const auto &s1, const auto &s2) {
			return std::stoi(s1) > std::stoi(s2);}); // we need inverse order
}

ip_pool_t filter_any(const ip_pool_t &pool, std::string val) {
	ip_pool_t r {};

	for (const auto &ip: pool) {
		if (std::find(ip.begin(), ip.end(), val) != ip.end())
			r.push_back(ip);
	}
	return r;
}

bool match(const ip_t &ip) {
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

void show_ips(const ip_pool_t &pool) {
	for(const auto &ip : pool) {
		for(auto ip_part_it = ip.cbegin(); ip_part_it != ip.cend(); ++ip_part_it)
		{
			if (ip_part_it != ip.cbegin())
				std::cout << ".";
			std::cout << *ip_part_it;
		}
		std::cout << std::endl;
	}
}

int main(int argc, char const *argv[])
{
	try {
		ip_pool_t ip_pool;

		for(std::string line; std::getline(std::cin, line);)
		{
			std::vector<std::string> v = split(line, '\t');
			ip_pool.push_back(split(v.at(0), '.'));
		}

		std::sort(ip_pool.begin(), ip_pool.end(), compare);

		show_ips(ip_pool);
		show_ips(filter(ip_pool, "1"));
		show_ips(filter(ip_pool, "46", "70"));
		show_ips(filter_any(ip_pool, "46"));

		// 222.173.235.246
		// 222.130.177.64
		// 222.82.198.61
		// ...
		// 1.70.44.170
		// 1.29.168.152
		// 1.1.234.8

		// 1.231.69.33
		// 1.87.203.225
		// 1.70.44.170
		// 1.29.168.152
		// 1.1.234.8

		// 46.70.225.39
		// 46.70.147.26
		// 46.70.113.73
		// 46.70.29.76

		// 186.204.34.46
		// 186.46.222.194
		// 185.46.87.231
		// 185.46.86.132
		// 185.46.86.131
		// 185.46.86.131
		// 185.46.86.22
		// 185.46.85.204
		// 185.46.85.78
		// 68.46.218.208
		// 46.251.197.23
		// 46.223.254.56
		// 46.223.254.56
		// 46.182.19.219
		// 46.161.63.66
		// 46.161.61.51
		// 46.161.60.92
		// 46.161.60.35
		// 46.161.58.202
		// 46.161.56.241
		// 46.161.56.203
		// 46.161.56.174
		// 46.161.56.106
		// 46.161.56.106
		// 46.101.163.119
		// 46.101.127.145
		// 46.70.225.39
		// 46.70.147.26
		// 46.70.113.73
		// 46.70.29.76
		// 46.55.46.98
		// 46.49.43.85
		// 39.46.86.85
		// 5.189.203.46
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
