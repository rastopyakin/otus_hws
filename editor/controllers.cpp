#include "controllers.hpp"
#include "figure.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <random>

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

void closeFile(EditorCore* core) {
    saveFile(core);
    core->newDoc("");
}

void addFigure(EditorCore* core) {
    // ask for a figure here
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> figChooser{0, 1};
    std::uniform_int_distribution<> figPosChooser{0, 10};

    switch (figChooser(gen)) {
    case 0:
        core->addFig(std::make_unique<Circle>(figPosChooser(gen)));
        break;
    case 1:
        core->addFig(std::make_unique<Triangle>(figPosChooser(gen)));
    }
}

void removeFigure(EditorCore* core) {
    core->removeFig(core->getFigures().front()->getPos());
}
