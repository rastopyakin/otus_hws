#include <iostream>

int main(int argc, char *argv[])
{
    const int N = 3;
    int a[N], b[N];

    for (int i = 0; i < N; ++i) {
	std::cin >> a[i] >> b[i];
    }
    std::printf("%d %d\n", a[0] - a[2], b[0] - b[1]);
    return 0;
}
