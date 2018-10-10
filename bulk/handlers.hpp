#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include "observer.hpp"

class CommaPlacer {
public:
    friend std::ostream& operator<<(std::ostream &os, CommaPlacer &cp) {
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
    void notify() const override {
        std::cout << "bulk: ";
        CommaPlacer cp;
        for (const auto& cmd : collector->getCmdList())
            std::cout << cp << cmd;
        std::cout << std::endl;
    }
private:
    CommandCollector* collector;
};

#endif /* HANDLERS_HPP */
