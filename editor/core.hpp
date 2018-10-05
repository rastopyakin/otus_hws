#ifndef CORE_HPP
#define CORE_HPP

#include "figure.hpp"

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
    }
    void removeFig(Figure::position_t pos) {
        auto result = std::find_if(figures.begin(), figures.end(),
                                   [pos](const auto& fig) -> bool {
                                       return pos == fig->getPos();
                                   });
        if (result != figures.end())
            figures.erase(result);
    }
    void newDoc() {}
    void saveDoc() {}
    void openDoc() {}

    const figures_t& getFigures() const {
        return figures;
    }
private:
    figures_t figures;
    std::string file_name;
};

#endif /* CORE_HPP */
