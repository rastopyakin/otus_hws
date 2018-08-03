#include <iostream>
#include <algorithm>

int main(int argc, char *argv[])
{
    int a, b, c;
    std::cin >> a >> b >> c;
    std::printf("%d\n", std::min(a - b*c, a - b - c));
    return 0;
}
