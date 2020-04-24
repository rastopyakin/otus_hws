#include <iostream>

int main(int argc, char *argv[])
{
    int A = 0;
    int B = 0;
    std::cin >> A >> B;
    int count = 0;

    for (int i = A; i <= B; ++i) {
	if (i%2 == 1)
	    count++;
    }
    std::cout << count << std::endl;
    return 0;
}
