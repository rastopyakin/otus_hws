#include <iostream>
#include <cmath>

int main(int argc, char *argv[])
{
    int N;
    std::cin >> N;
    double K;
    double guess;
    double n;
    for (int i = 0;  i < N; ++ i) {
	std::cin >> K;
	guess = 0.5*(std::sqrt(1 + 8*(K - 1)) - 1);
	n = std::nearbyint(guess);
	if (2*(K - 1) == n*(n + 1))
	    std::printf("1 ");
	else
	    std::printf("0 ");
    }
    std::cout << std::endl;
    return 0;
}
