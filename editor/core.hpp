#ifndef CORE_HPP
#define CORE_HPP

#include "figure.hpp"
#include "view.hpp"

#include <list>
#include <string>
#include <memory>
#include <algorithm>

class EditorCore {
public:
    using figure_p_t = std::unique_ptr<Figure>;
    using figures_t = std::list<figure_p_t>;
    void addFig(figure_p_t fig) {
        figures.push_back(std::move(fig));
        view->render();
    }
    void removeFig(Figure::position_t pos) {
        auto result = std::find_if(figures.begin(), figures.end(),
                                   [pos](const auto& fig) -> bool {
                                       return pos == fig->getPos();
                                   });
        if (result != figures.end())
            figures.erase(result);
        view->render();
    }
    void newDoc(std::string name) {
        figures.clear();
        file_name = name;
        view->render();
    }

    const figures_t& getFigures() const {
        return figures;
    }
    auto getFileName() const {
        return file_name;
    }

    void setView(View *p) {
        view = p;
    }
private:
    figures_t figures;
    std::string file_name;
    View *view;
};

#endif /* CORE_HPP */
