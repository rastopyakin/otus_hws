#ifndef COLLECTOR_HPP
#define COLLECTOR_HPP

#include <vector>
#include <memory>
#include <string>
#include <list>

#include "subscriber.hpp"
#include "helpers.hpp"

class CommandCollector {
public:
    using command_t = std::string;
    using command_block_t = std::list<command_t>;
    using time_stamp_t = std::chrono::time_point<std::chrono::steady_clock>;

    CommandCollector(std::size_t N) : block_size(N) {}

    void gather(const command_t &cmd) {
        if (cmd_block.empty())
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
            cmd_block.push_back(cmd);

        // submit fixed size block if it's ready
        if (cmd_block.size()==block_size and dynamic_size_block_depth==0) {
            flush();
        }
    }

    void subscribe(std::shared_ptr<Subscriber> p) {
        subscribers.push_back(p);
    }
    void flush() {
        if (dynamic_size_block_depth == 0 and !cmd_block.empty()) {
            stat.blocks_num++;
            stat.cmd_num += cmd_block.size();
            for (auto &subscriber : subscribers)
                subscriber->notify();
        }

        cmd_block.clear();
        dynamic_size_block_depth = 0;
    }

    const auto& getTimeStamp() const {
        return time_stamp;
    }

    Stat getStat() const {
        return stat;
    }
    command_block_t getCmdBlock() const {
        return cmd_block;
    }

private:
    std::vector<std::shared_ptr<Subscriber>> subscribers;
    int dynamic_size_block_depth = 0;
    time_stamp_t time_stamp;
    std::size_t block_size;
    command_block_t cmd_block;
    Stat stat;
};

#endif /* COLLECTOR_HPP */
