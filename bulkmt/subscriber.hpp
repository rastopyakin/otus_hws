#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

class Subscriber {
public:
    virtual void notify() = 0;
    virtual ~Subscriber() = default;
};

#endif /* SUBSCRIBER_HPP */
