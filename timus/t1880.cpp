#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[])
{
    int n1 = 0;
    std::cin >> n1;
    std::vector<int> numbers1;
    numbers1.reserve(n1);
    numbers1.resize(n1);
    for (int & v : numbers1)
	std::cin >> v;

    int n2 = 0;
    std::cin >> n2;
    std::vector<int> numbers2;
    numbers2.reserve(n2);
    numbers2.resize(n2);
    for (int & v : numbers2)
	std::cin >> v;

    int n3 = 0;
    std::cin >> n3;
    std::vector<int> numbers3;
    numbers3.reserve(n3);
    numbers3.resize(n3);
    for (int & v : numbers3)
	std::cin >> v;
    int count  = 0;
    for (const int &v : numbers1)
	if (std::binary_search(numbers2.begin(), numbers2.end(), v))
	    if (std::binary_search(numbers3.begin(), numbers3.end(), v))
		count++;
    std::printf("%d\n", count);


    return 0;
}
