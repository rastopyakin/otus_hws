#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include <iostream>
#include <thread>

#include "subscriber.hpp"
#include "collector.hpp"
#include "buffer.hpp"

class CommaPlacer {
public:
    friend auto& operator<<(std::ostream &os, CommaPlacer &cp) {
        if (!cp.is_first)
            os << ", ";
        else
            cp.is_first = false;
        return os;
    }
private:
    bool is_first = true;
};

class ConsoleLogger : public Subscriber {
public:
    ConsoleLogger(std::shared_ptr<CommandCollector> p) : collector{p} {
        worker_thread = std::thread{&ConsoleLogger::worker, this};
    }
    void notify() final {
        buffer.push(collector.lock()->getCmdBlock());
    }
    ~ConsoleLogger() {
        buffer.disable_waiting();
        worker_thread.join();
    }
private:
    void worker() {
        while (true) {
            auto block = buffer.pop_or_wait();
            if (!block)
                break;
            process(*block);
        }
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
};

#endif /* HANDLERS_HPP */
