#include <iostream>
#include <string>
#include <memory>

#include "collector.hpp"
#include "handlers.hpp"

int main(int argc, char *argv[]) {

    std::size_t block_size = 0;

    if (argc == 2)
        block_size = std::stoi(argv[1]);
    else {
        std::cout << "Usage: bulk <number of commands in block>\n";
        return 1;
    }
    auto collector = std::make_shared<CommandCollector>(block_size);
    auto to_console = std::make_shared<ConsoleHandler>(collector);
    collector->subscribe(to_console);
    auto to_file = std::make_shared<FileHandler>(collector);
    collector->subscribe(to_file);

    CommandCollector::command_t cmd;
    while (std::getline(std::cin, cmd)) {
        collector->gather(cmd);
    }

    collector->flush();
    return 0;
}
