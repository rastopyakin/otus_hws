#include "core.hpp"
#include "consoleView.hpp"

void menuNewDoc() {}

void menuSaveDoc() {}

void menuOpenDoc() {}

void addFig() {}

void removeFig() {}

int main(int argc, char *argv[]) {

    std::string s = "";
    std::cout << s.size() << std::endl;

    EditorCore core;
    ConsoleView view {&core};
    core.setView(&view);

    view.render();

    view.getToolBar()->getButton("newFile")->clicked();

    core.addFig(std::make_unique<Triangle>(0));
    core.addFig(std::make_unique<Circle>(1));

    core.removeFig(0);

    view.getToolBar()->getButton("saveFile")->clicked();

    std::cout << "closing file...\n";
    view.getToolBar()->getButton("closeFile")->clicked();

    view.getToolBar()->getButton("openFile")->clicked();
    return 0;
}
