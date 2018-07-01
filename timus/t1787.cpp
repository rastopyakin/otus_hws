#include <iostream>

int main(int argc, char *argv[])
{
    int k, n;
    std::cin >> k >> n;
    int a = 0;
    int current = 0;
    for (int i = 0; i < n; i++) {
	std::cin >> a;
	current = current  + a - k;
	current = current>0 ? current:0;
    }

    std::printf("%d\n", current);
    return 0;
}
