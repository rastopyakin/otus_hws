#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>
#include <algorithm>

class Observer {
public:
    virtual void notify() = 0;
    virtual ~Observer() = default;
};

class Observable {
public:
    Observable() {}
    void subscribe(Observer* observer) {
        observers.push_back(observer);
    }
    void unsubscribe(const Observer* observer) {
        auto result = std::find(observers.begin(), observers.end(), observer);
        if (result != observers.end())
            observers.erase(result);
    }
    virtual ~Observable() = default;
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
