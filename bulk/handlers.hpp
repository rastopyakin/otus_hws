#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "observer.hpp"
#include "collector.hpp"

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

class ConsoleHandler : public Observer {
public:
    ConsoleHandler(CommandCollector* p) : collector(p) {
        collector->subscribe(this);
    }
    void notify() final {
        std::cout << "bulk: ";
        CommaPlacer cp;
        for (const auto& cmd : collector->getCmdList())
            std::cout << cp << cmd;
        std::cout << std::endl;
    }
private:
    CommandCollector* collector;
};

class FileHandler : public Observer {
public:
    FileHandler(CommandCollector* p) : collector(p) {
        collector->subscribe(this);
    };
    void notify() final {
        auto time_stamp{
            std::to_string(collector->getTimeStamp().time_since_epoch().count())
        };
        std::string file_name {"bulk" + time_stamp + ".log"};
        file.open(file_name, std::ios::out | std::ios::app);
        file << "bulk: ";
        CommaPlacer cp;
        for (const auto& cmd : collector->getCmdList())
            file << cp << cmd;
        file << std::endl;
        file.close();
    }
private:
    std::fstream file;
    CommandCollector* collector;
};
#endif /* HANDLERS_HPP */
