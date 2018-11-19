#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include <iostream>
#include <thread>
#include <future>

#include "subscriber.hpp"
#include "collector.hpp"
#include "buffer.hpp"
#include "helpers.hpp"

class ConsoleLogger : public Subscriber {
public:
    ConsoleLogger(std::shared_ptr<CommandCollector> p) : collector{p} {
        worker_thread = std::thread{&ConsoleLogger::worker, this};
    }
    void notify() final {
        buffer.push(collector.lock()->getCmdBlock());
    }
    std::future<Stat> getStat() {
        return stat_promise.get_future();
    }
    ~ConsoleLogger() {
        buffer.disable_waiting();
        worker_thread.join();
    }
private:
    void worker() {
        Stat stat;
        while (true) {
            auto block = buffer.pop_or_wait();
            if (!block)
                break;
            stat.blocks_num++;
            stat.cmd_num += block->size();
            process(*block);
        }
        stat_promise.set_value(stat);
    }
    void process(const CommandCollector::command_block_t &block) {
        std::cout << "bulk: ";
        CommaPlacer cp;
        for (const auto &cmd : block)
            std::cout << cp << cmd;
        std::cout << std::endl;
    }
private:
    Buffer<CommandCollector::command_block_t> buffer;
    std::weak_ptr<CommandCollector> collector;
    std::thread worker_thread;
    std::promise<Stat> stat_promise;
};

#endif /* HANDLERS_HPP */
