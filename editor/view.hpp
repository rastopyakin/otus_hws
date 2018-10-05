#ifndef VIEW_HPP
#define VIEW_HPP

#include <iostream>
#include <vector>
#include <memory>

#include "core.hpp"

class View {
public:
    virtual void render() const = 0;
};

class WorkSheet : public View {
public:
    WorkSheet(EditorCore* p) : core(p) {}
    void render() const override {
        std::cout << "worksheet:\n";
        for (const auto& fig : core->getFigures())
            fig->render();
    }
private:
    EditorCore* core;
};

class EditorView : public View {
public:
    EditorView(EditorCore* p) {
        views.push_back(std::make_unique<WorkSheet>(p));
    }
    void render() const override {
        for (const auto& v : views)
            v->render();
    }
private:
    std::vector<std::unique_ptr<View>> views;
};
#endif /* VIEW_HPP */
