#include <iostream>


int main(int argc, char *argv[])
{
    int key1, key2;
    std::cin >> key1 >> key2;
    if (key1%2 == 0 || key2%2 != 0)
	std::printf("yes\n");
    else
	std::printf("no\n");
    return 0;
}
