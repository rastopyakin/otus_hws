#include <iostream>

int main(int argc, char *argv[]) {
    int N;
    std::cin >> N;

    int prev, next;
    int count  = 1;
    std::cin >> prev;
    for (int i = 0; i < N-1; i++) {
        std::cin >> next;
        if (prev == next) {
            count++;
        }
        else {
            std::cout << count << ' ' << prev << ' ';
            count = 1;
        }
        prev = next;
    }
    std::cout << count << ' ' << prev << std::endl;
    return 0;
}
