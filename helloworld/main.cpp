#include <iostream>
#include "hw.hpp"

int main(int argc, char *argv[])
{
	if (argc == 1)
		std::printf("Hello, world!\n");
	else if (std::string{argv[1]} == "--version")
		std::printf("Version %s\n", version().c_str());
	else
		std::printf("Usage: helloworld [--version]\n");
	return 0;
}
