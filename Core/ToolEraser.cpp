/*
** ProtoPaint
** File description:
** Core
*/

#include "ToolEraser.hpp"
#include "../Gui/EraserWin.hpp"
#include "BrushCircle.hpp"
#include "BrushSquare.hpp"

ProtoPaint::ToolEraser::ToolEraser()
{
    this->_gui = std::make_unique<GUI::EraserWin>();

    this->_values["size"] = 4;

    this->_brushes.push_back(std::make_unique<ProtoPaint::BrushCircle>());
    this->_brushes.push_back(std::make_unique<ProtoPaint::BrushSquare>());
}

void ProtoPaint::ToolEraser::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    int index = this->_values["brush"];
    if (win->isLeftMouseJustReleased() && this->_used) {
        GlobalData.setAddState(true);
        this->_used = false;
    }

    if (!win->isLeftMousePressed()
        || !zone->isInZone(win->getMousePosition())) {
        return;
    }
    this->_used = true;

    sf::Vector2f pos = win->getMousePosition();
    pos = zone->getRelatedPosition(pos);
    sf::Color brushColor = GlobalData.getSecondColor();

    this->_brushes[index]->setColor(brushColor);

    sf::Vector2f lastPos = pos - win->getMouseTranslation();

    this->drawLine(zone, lastPos, pos);
}

void ProtoPaint::ToolEraser::drawPreview(std::shared_ptr<Graphic::Window> win)
{
    int index = this->_values["brush"];
    this->_brushes[index]->setSize(this->_values["size"]);
    this->_brushes[index]->drawPreview(win, win->getMousePosition());
}

void ProtoPaint::ToolEraser::drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end)
{
    int index = this->_values["brush"];
    sf::Vector2f delta = end - start;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    const int numSteps = std::max((int)(distance / this->_values["size"]), 1) * 3; // At least one circle
    for (int i = 0; i <= numSteps; ++i) {
        float t = static_cast<float>(i) / numSteps;
        sf::Vector2f interpolatedPos = start + t * delta;

        this->_brushes[index]->draw(zone, interpolatedPos, false);
    }
}
