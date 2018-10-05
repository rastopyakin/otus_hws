#ifndef CONSOLEVIEW_HPP
#define CONSOLEVIEW_HPP

#include "view.hpp"
#include "core.hpp"

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

class ConsoleView : public View {
public:
    ConsoleView(EditorCore* p) {
        views.push_back(std::make_unique<WorkSheet>(p));
    }
    void render() const override {
        for (const auto& v : views)
            v->render();
    }
private:
    std::vector<std::unique_ptr<View>> views;
};

#endif /* CONSOLEVIEW_HPP */
