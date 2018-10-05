#include "core.hpp"
#include "controller.hpp"
#include "consoleView.hpp"

void menuNewDoc() {}

void menuSaveDoc() {}

void menuOpenDoc() {}

void addFig() {}

void removeFig() {}

int main(int argc, char *argv[]) {
    EditorCore core;
    ConsoleView view {&core};
    core.setView(&view);

    core.addFig(std::make_unique<Triangle>(0));
    core.addFig(std::make_unique<Circle>(1));

    core.removeFig(0);

    return 0;
}
