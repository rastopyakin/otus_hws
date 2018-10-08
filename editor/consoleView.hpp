#ifndef CONSOLEVIEW_HPP
#define CONSOLEVIEW_HPP

#include <iostream>
#include <string>
#include <functional>
#include <algorithm>

#include "view.hpp"
#include "core.hpp"
#include "controllers.hpp"

class WorkSheet : public View {
public:
    WorkSheet(EditorCore* p) : core(p) {}
    void render() const override {
        std::cout << "worksheet:\n";
        for (const auto& fig : core->getFigures())
            fig->render(std::cout);
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
    void addSlot(const callback_t &slot) {
        slots.push_back(slot);
    }
    void clicked() const {
        for (const auto& slot : slots)
            slot();
    }
    const auto& getName() const {
        return m_name;
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
        buttons.back().addSlot(std::bind(newFile, core));
        buttons.emplace_back("openFile");
        buttons.back().addSlot(std::bind(openFile, core));
        buttons.emplace_back("saveFile", isFileOpened);
        buttons.back().addSlot(std::bind(saveFile, core));
        buttons.emplace_back("closeFile", isFileOpened);
        buttons.back().addSlot(std::bind(closeFile, core));
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
    auto getButton(const std::string& name) const {
        auto result = std::find_if(buttons.begin(), buttons.end(),
                                   [&name](const auto& b) {
                                       return b.getName() == name;});
        return result;
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
        toolBar_p = reinterpret_cast<ToolBar*>(views.back().get());

        views.push_back(std::make_unique<WorkSheet>(p));

    }
    void render() const override {
        for (const auto& v : views)
            v->render();
        std::cout << std::endl;
    }
    const ToolBar* getToolBar() const {
        return toolBar_p;
    }
private:
    std::vector<std::unique_ptr<View>> views;
    ToolBar* toolBar_p;
};

#endif /* CONSOLEVIEW_HPP */
