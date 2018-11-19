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
    std::future<Stat> console_stat, file_stat;
    Stat main_stat;
    std::size_t str_num = 0;
    {
        auto collector  = std::make_shared<CommandCollector>(block_size);
        auto console_logger = std::make_shared<ConsoleLogger>(collector);

        collector->subscribe(console_logger);

        CommandCollector::command_t cmd_or_bracket;

        while (std::getline(std::cin, cmd_or_bracket)) {
            collector->gather(cmd_or_bracket);
            str_num++;
        }
        collector->flush();

        main_stat = collector->getStat();
        console_stat = console_logger->getStat();
    }

    std::cout << "main thread: "
              << str_num << " strings, "
              << main_stat.blocks_num << " blocks, "
              << main_stat.cmd_num << " commands\n";
    auto stat = console_stat.get();
    std::cout << "log thread: "
              << stat.blocks_num << " blocks, "
              << stat.cmd_num << " commands\n";

    return 0;
}
