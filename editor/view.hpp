#ifndef VIEW_HPP
#define VIEW_HPP

#include <iostream>
#include <vector>
#include <memory>

class View {
public:
    virtual void render() const = 0;
};

#endif /* VIEW_HPP */
