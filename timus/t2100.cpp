#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    int n;
    std::cin >> n;

    int guests_num = 0;
    std::string response;

    for (int i = 0;  i < n; ++ i) {
	std::cin >> response;
	if (response.find("+one") != std::string::npos)
	    guests_num += 2;
	else
	    guests_num += 1;
    }
    if (guests_num + 2 != 13)
	std::printf("%d\n", 100*(guests_num + 2));
    else
	std::printf("%d\n", 100*(guests_num + 3));
    return 0;
}
