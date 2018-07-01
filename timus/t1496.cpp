#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

int main(int argc, char *argv[])
{
    int N = 0;
    std::cin >> N;

    std::set<std::string> unique_names;
    std::vector<std::string> doubled_names;

    std::string name;
    for (int i = 0; i < N; i++) {
	std::cin >> name;
	auto is_unique = unique_names.insert(name);
	if (!is_unique.second)
	    doubled_names.push_back(name);
    }
    std::sort(doubled_names.begin(), doubled_names.end());

    doubled_names.erase(
	std::unique(doubled_names.begin(), doubled_names.end()),
	doubled_names.end());
    for (const auto &name : doubled_names)
	std::cout << name << std::endl;
    return 0;
}
