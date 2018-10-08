#ifndef CONTROLLERS_HPP
#define CONTROLLERS_HPP

#include "core.hpp"

class Controller {};

void newFile(EditorCore* core);

void openFile(EditorCore* core);

void saveFile(EditorCore* core);

void closeFile(EditorCore* core);

void addFigure(EditorCore* core);

void removeFigure(EditorCore* core);

#endif /* CONTROLLERS_HPP */
