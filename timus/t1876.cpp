#include <iostream>

int main(int argc, char *argv[])
{
    int a, b;
    std::cin >> a >> b;
    int t1 = 2*a + 39;
    int t2 = 2*b + 40;
    std::cout << (t1 > t2 ? t1:t2) << std::endl;
    return 0;
}
