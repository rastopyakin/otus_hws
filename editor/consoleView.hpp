#ifndef CONSOLEVIEW_HPP
#define CONSOLEVIEW_HPP

#include <iostream>
#include <string>
#include <functional>

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

class FileNameView : public View {
public:
    FileNameView(EditorCore* p) : core(p) {}
    void render() const override {
        std::cout << "current file: " << core->getFileName() << std::endl;
    }
private:
    EditorCore* core;
};

class ActiveView {
public:
    using isActiveCallBack_t = std::function<bool()>;
    using callback_t = std::function<void()>;
    ActiveView(std::string name, isActiveCallBack_t f = []() {return true;})
        : m_name(name), isActive(f) {}
    void render() const {
        if (isActive())
            std::cout << m_name;
    }
    void clicked() const {
        for (const auto& slot : slots)
            slot();
    }
private:
    std::string m_name;
    isActiveCallBack_t isActive;
    std::vector<callback_t> slots;
};

class ToolBar : public View {
public:
    ToolBar(EditorCore *core) {
        auto isFileOpened = [core]() {return core->getFileName().size();};
        buttons.emplace_back("newFile");
        buttons.emplace_back("openFile");
        buttons.emplace_back("saveFile", isFileOpened);
        buttons.emplace_back("addFigure", isFileOpened);
        buttons.emplace_back("removeFigure", isFileOpened);
    }
    void render() const override {
        std::cout << "Toolbar: ";
        for (const auto& b : buttons) {
            b.render();
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
private:
    // EditorCore* core;
    std::vector<ActiveView> buttons;
};

class ConsoleView : public View {
public:
    ConsoleView(EditorCore* p) {
        views.push_back(std::make_unique<FileNameView>(p));
        views.push_back(std::make_unique<ToolBar>(p));
        views.push_back(std::make_unique<WorkSheet>(p));
    }
    void render() const override {
        for (const auto& v : views)
            v->render();
        std::cout << std::endl;
    }
private:
    std::vector<std::unique_ptr<View>> views;
};

#endif /* CONSOLEVIEW_HPP */
