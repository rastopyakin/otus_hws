#include "controllers.hpp"
#include "figure.hpp"

#include <iostream>
#include <string>
#include <fstream>

void newFile(EditorCore* core) {
    // ask for a file name here
    std::string name = "file_1";
    core->newDoc(name);
}

void openFile(EditorCore* core) {
    // ask for a filename here
    std::string name = "file_1";
    core->newDoc(name);
    std::fstream file;
    file.open(name, std::ios::in);
    std::string figure; Figure::position_t pos;
    while ((file >> figure >> pos)) {
        if (figure.find("Circle"))
            core->addFig(std::make_unique<Circle>(pos));
        else if (figure.find("Triangle"))
            core->addFig(std::make_unique<Triangle>(pos));
    }
    file.close();
}


void saveFile(EditorCore* core) {
    std::fstream file;
    file.open(core->getFileName(), std::ios::out);
    for (const auto& fig : core->getFigures())
        fig->render(file);
    file.close();
}
