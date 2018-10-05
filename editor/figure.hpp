#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <iostream>

class Figure {
public:
    using position_t = int;
    Figure(int pos) : position(pos) {}
    virtual void render() const  = 0;

    position_t getPos() const {
        return position;
    }
private:
    position_t position;
};

class Triangle : public Figure {
public:
    void render() const override {
        std::cout << "\tTriangle: " << getPos() << std::endl;
    }
};

class Circle : public Figure {
public:
    void render() const override {
        std::cout << "\t Circle:" << getPos() << std::endl;
    }
};
#endif /* FIGURE_HPP */
