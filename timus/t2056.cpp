#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    int n = 0;
    std::vector<int> m;
    std::cin >> n;
    m.reserve(n);
    m.resize(n);
    for (auto &grade : m)
	std::cin >> grade;
    double avg = 0.0;
    for (const auto &grade : m) {
	if (grade == 3) {
	    std::cout << "None\n";
	    return 0;
	}
	avg += grade;
    }
     avg /= n;
    if (avg == 5.0)
	std::cout << "Named\n";
    else if (avg >= 4.5)
	std::cout << "High\n";
    else
	std::cout << "Common\n";
    return 0;
}
