#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include <iostream>
#include <fstream>
#include <thread>
#include <future>
#include <chrono>
#include <utility>
#include <string>
#include <algorithm>
#include <iterator>

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
    void process(const CommandCollector::command_block_t &block) const {
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

class FileLogger : public Subscriber {
public:
    using cmd_block_descriptor = std::pair<CommandCollector::command_block_t, CommandCollector::time_stamp_t>;
    FileLogger(std::shared_ptr<CommandCollector> p, std::size_t thread_num = 2)
        : collector(p) {

        workers.reserve(thread_num);
        stat_promises.reserve(thread_num);
        for (std::size_t id = 0; id < thread_num; id++) {
            stat_promises.emplace_back();
            workers.emplace_back(&FileLogger::worker, this, id);
        }
    }
    void notify() final {
        auto ts = collector.lock()->getTimeStamp();
        buffer.push(std::make_pair(collector.lock()->getCmdBlock(), ts));
    }
    ~FileLogger() {
        buffer.disable_waiting();
        for (auto& worker : workers)
            worker.join();
    }

    auto getStat() {
        std::vector<std::future<Stat>> results;
        std::transform(stat_promises.begin(), stat_promises.end(), std::back_inserter(results), [](auto &p) {return p.get_future();});
        return results;
    }
private:
    void worker(std::size_t id) {
        Stat stat;
        while (true) {
            auto block = buffer.pop_or_wait();
            if (!block)
                break;
            stat.blocks_num++;
            stat.cmd_num += block->first.size();
            process(*block, id);
        }
        std::lock_guard<std::mutex> lk{promises_lock};
        stat_promises[id].set_value(stat);
    }
    void process(const cmd_block_descriptor &d, std::size_t id) const {
        std::fstream file;
        auto time_stamp = std::to_string(d.second.time_since_epoch().count());
        std::string file_name {"bulk" + time_stamp + ".log"};
        file.open(file_name, std::ios::out | std::ios::app);
        file << "bulk: ";
        CommaPlacer cp;
        for (const auto& cmd : d.first)
            file << cp << cmd;
        file << std::endl;
        file.close();
    }
private:
    Buffer<cmd_block_descriptor> buffer;
    std::weak_ptr<CommandCollector> collector;
    std::vector<std::thread> workers;
    std::mutex promises_lock;
    std::vector<std::promise<Stat>> stat_promises;
};

#endif /* HANDLERS_HPP */
