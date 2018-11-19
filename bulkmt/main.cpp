#include <iostream>
#include <memory>
#include <thread>

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

    auto collector  = std::make_shared<CommandCollector>(block_size);
    auto console_logger = std::make_shared<ConsoleLogger>(collector);

    collector->subscribe(console_logger);

    CommandCollector::command_t cmd;

    while (std::getline(std::cin, cmd)) {
        collector->gather(cmd);
    }

    collector->flush();

    return 0;
}
