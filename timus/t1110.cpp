#include <iostream>
#include <limits>
#include <vector>
#include <numeric>

int X_N_mod_M(int X, int N, int M) {
    int seed = 1;
    for (int n = 0; n < N; n++) {
	seed = seed*X % M;
    }
    return seed;
}

int X_N_mod_M_v2(int X, int N, int M) {
    int seed = 1;
    for (int n = 0; n < N; n++) {
	seed = seed*X % M;
    }
    return seed;
}

int main(int argc, char *argv[])
{
    unsigned int N, M, Y;
    std::cin >> N >> M >> Y;
    std::vector<int> found;
    found.reserve(M);

    // std::cout << X_N_mod_M(Y, N, M) << std::endl;

    for (int y = 0; y < M; y++) {
    	if (X_N_mod_M(y, N, M) == Y)
    	    found.push_back(y);
    }
    if (found.size() == 0)
    	std::cout << "-1";
    else
    	for (const int y : found)
    	    std::cout << y << ' ';
    // std::cout  << std::endl;
    // std::cout  << std::endl;
    // std::adjacent_difference(found.begin(), found.end(), found.begin());
    // for (const int y : found)
    	    // std::cout << y << ' ';
    std::cout  << std::endl;
    return 0;
}
