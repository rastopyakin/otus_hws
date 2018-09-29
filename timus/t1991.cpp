#include <iostream>
#include <cmath>

int main(int argc, char *argv[]) {
    int n, k;
    std::cin >> n >> k;
    int survived = 0;
    int unused = 0;
    int n_booms;
    for (int i = 0; i < n; i++) {
        std::cin >> n_booms;
        survived += std::max(k - n_booms, 0);
        unused += std::max(0, n_booms - k);
    }
    std::cout << unused << ' ' << survived << std::endl;
    return 0;
}
