#ifndef VIEW_HPP
#define VIEW_HPP

#include <iostream>

#include "core.hpp"

class View {
public:
    View(EditorCore *p) : core(p) {}
    virtual void render() const = 0;
protected:
    EditorCore* core;
};

class WorkSheet : public View {
public:
    WorkSheet(EditorCore* p) : View(p) {}
    void render() const override {
        std::cout << "worksheet:\n";
        for (const auto& fig : core->getFigures())
            fig->render();
    }
};
#endif /* VIEW_HPP */
