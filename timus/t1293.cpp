#include <iostream>

int main(int argc, char *argv[])
{
    int vals[] = {0, 0, 0};
    for (int i = 0; i < 3; ++i) {
	std::cin >> vals[i];
    }
    std::printf("%d\n", 2*vals[0]*vals[1]*vals[2]);
    return 0;
}
