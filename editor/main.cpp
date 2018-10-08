#include "core.hpp"
#include "consoleView.hpp"

int main(int argc, char *argv[]) {

    EditorCore core;
    ConsoleView view {&core};
    core.setView(&view);

    view.render();

    view.getToolBar()->getButton("newFile")->clicked();

    view.getToolBar()->getButton("addFigure")->clicked();
    view.getToolBar()->getButton("addFigure")->clicked();

    view.getToolBar()->getButton("removeFigure")->clicked();

    view.getToolBar()->getButton("saveFile")->clicked();

    std::cout << "closing file...\n";
    view.getToolBar()->getButton("closeFile")->clicked();

    view.getToolBar()->getButton("openFile")->clicked();
    return 0;
}
