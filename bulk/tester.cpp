#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <thread>

int main(int argc, char *argv[]) {
    std::string cmd;
    std::fstream test_file;
    test_file.open(argv[1], std::ios::in);
    while (std::getline(test_file, cmd)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << cmd << std::endl;
    }
    test_file.close();
    return 0;
}
