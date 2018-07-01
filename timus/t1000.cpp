#include <iostream>
#include <string>
#include <exception>
#include <algorithm>

bool isnumber(const std::string &s) {
  return std::find_if(s.begin(), s.end(),
		      [] (char c) {
			return !std::isdigit(c);}
		      ) == s.end();
}

int main(int argc, char *argv[]) {

  try {
    if (argc == 3) {
      if (!isnumber(argv[1]) || !isnumber(argv[2]))
	throw std::runtime_error("Only integer numbers allowed");
      int a = std::stoi(argv[1]);
      int b = std::stoi(argv[2]);
      std::printf("%d\n", a + b);
    }
    else
      std::printf("Usage: a_plus_b a b\n");
  }
  catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
