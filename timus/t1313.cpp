#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    int N;
    std::cin >> N;
    std::vector<int> pixels;
    pixels.reserve(N*N);
    pixels.resize(N*N);

    for (int &p : pixels)
        std::cin >> p;

    for (int S = 0; S <= 2*(N - 1); S++)
        if (S < N)
            for (int i = S; i >= 0; i--) {
                int j = S - i;
                std::cout << pixels[i*N + j] << ' ';
            }
        else
            for (int j = S - N + 1; j < N; j++) {
                int i = S - j;
                std::cout << pixels[i*N + j] << ' ';
            }

    std::cout << std::endl;
    return 0;
}
