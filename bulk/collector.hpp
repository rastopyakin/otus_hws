#ifndef COLLECTOR_HPP
#define COLLECTOR_HPP

#include <list>
#include <string>
#include <chrono>

#include "observer.hpp"

class CommandCollector : public Observable {
public:
    using command_t = std::string;
    CommandCollector(std::size_t N) : block_size(N) {}
    void gather(const command_t &cmd) {
        if (cmd_list.empty())
            time_stamp = std::chrono::steady_clock::now();

        if (cmd == "{") {
            if (dynamic_size_block_depth==0)
                flush();        // forced block interruption before dynamic block
            dynamic_size_block_depth++;
        }
        else if (cmd == "}") {
            dynamic_size_block_depth--;
            if (dynamic_size_block_depth==0)
                flush();        // dynamic block is ready here
        }
        else
            cmd_list.push_back(cmd);

        // submit fixed size block if it's ready
        if (cmd_list.size()==block_size and dynamic_size_block_depth==0) {
            flush();
        }
    }

    const auto& getTimeStamp() const {
        return time_stamp;
    }

    const auto& getCmdList() const {
        return cmd_list;
    }

    void flush() {
        if (dynamic_size_block_depth == 0 and !cmd_list.empty())
            notify_all();
        cmd_list.clear();
        dynamic_size_block_depth = 0;
    }
private:
    int dynamic_size_block_depth = 0;
    std::chrono::time_point<std::chrono::steady_clock> time_stamp;
    std::size_t block_size;
    std::list<command_t> cmd_list;
};

#endif /* COLLECTOR_HPP */
