#ifndef COLLECTOR_HPP
#define COLLECTOR_HPP

#include <list>
#include <chrono>

#include "observer.hpp"

class CommandCollector : public Observable {
public:
    using command_t = std::string;
    CommandCollector(std::size_t N) : block_size(N) {}
    void gather(const command_t &cmd) {
        if (getCurrentBlockSize() == 0)
            time_stamp = std::chrono::steady_clock::now();
        cmd_list.push_back(cmd);
        if (getCurrentBlockSize() == block_size) {
            notify_all();
            cmd_list.clear();
        }
    }
    std::size_t getCurrentBlockSize() {
        return cmd_list.size();
    }

    const auto& getTimeStamp() const {
        return time_stamp;
    }

    const auto& getCmdList() const {
        return cmd_list;
    }
private:
    std::chrono::time_point<std::chrono::steady_clock> time_stamp;
    std::size_t block_size;
    std::list<command_t> cmd_list;
};

#endif /* COLLECTOR_HPP */
