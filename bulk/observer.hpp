#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>

class Observer {
public:
    virtual void notify() const = 0;
};

class Observable {
public:
    Observable() {}
    void subscribe(Observer* observer) {
        observers.push_back(observer);
    }
protected:
    void notify_all() {
        for (const auto o : observers) {
            o->notify();
        }
    }
private:
    std::vector<Observer*> observers;
};

#endif /* OBSERVER_HPP */
