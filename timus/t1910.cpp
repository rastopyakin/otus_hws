#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    int n = 0;
    std::cin >> n;
    std::vector<int> a;
    a.reserve(n);
    a.resize(n);
    for (int & v : a)
	std::cin >> v;

    int strength = 0;
    int temp, current_i = 1;
    for (int i = 1; i < n - 1; ++i) {
	temp = a[i - 1] + a[i] + a[i + 1];
	if (temp > strength) {
	    strength = temp;
	    current_i  = i;
	}

    }
    std::printf("%d %d\n", strength, current_i + 1);
    return 0;
}
