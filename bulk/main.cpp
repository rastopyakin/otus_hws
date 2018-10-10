#include <iostream>
#include <string>

#include "collector.hpp"
#include "handlers.hpp"

int main(int argc, char *argv[]) {

    std::size_t block_size = 0;

    if (argc == 2)
        block_size = std::stoi(argv[1]);
    else std::cout << "Usage: bulk <number of commands in block>\n";

    CommandCollector collector {block_size};
    ConsoleHandler to_console {&collector};
    FileHandler to_file {&collector};
    CommandCollector::command_t cmd;
    while (std::getline(std::cin, cmd)) {
        collector.gather(cmd);
    }
    return 0;
}
