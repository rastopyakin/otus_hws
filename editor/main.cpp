#include "core.hpp"
#include "controller.hpp"
#include "view.hpp"

void menuNewDoc() {}

void menuSaveDoc() {}

void menuOpenDoc() {}

void addFig() {}

void removeFig() {}

int main(int argc, char *argv[]) {
    EditorCore core;
    View *view = new WorkSheet(&core);

    core.addFig(std::make_unique<Triangle>(0));
    core.addFig(std::make_unique<Circle>(1));

    view->render();

    core.removeFig(0);

    view->render();

    return 0;
}
