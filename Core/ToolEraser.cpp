/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "ToolEraser.hpp"
#include "../Gui/EraserWin.hpp"
#include "BrushCircle.hpp"

EpiGimp::ToolEraser::ToolEraser()
{
    this->_gui = std::make_unique<GUI::EraserWin>();

    this->_values["size"] = 4;

    this->_brushes = std::make_unique<EpiGimp::BrushCircle>();
}

void EpiGimp::ToolEraser::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    if (win->isLeftMouseJustReleased() && this->_used) {
        GlobalData.setAddState(true);
        this->_used = false;
    }

    if (!win->isLeftMousePressed()
        || !zone->getSprite().getGlobalBounds().contains(win->getMousePosition())) {
        return;
    }
    this->_used = true;

    sf::Vector2f pos = win->getMousePosition();
    pos = zone->getSprite().getInverseTransform().transformPoint(pos);
    sf::Color brushColor = GlobalData.getSecondColor();

    this->_brushes->setColor(brushColor);

    sf::Vector2f lastPos = pos - win->getMouseTranslation();

    this->drawLine(zone, lastPos, pos);
}

void EpiGimp::ToolEraser::drawPreview(std::shared_ptr<Graphic::Window> win)
{
    this->_brushes->setSize(this->_values["size"]);
    this->_brushes->drawPreview(win, win->getMousePosition());
}

void EpiGimp::ToolEraser::drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end)
{
    sf::Vector2f delta = end - start;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    const int numSteps = std::max((int)(distance / this->_values["size"]), 1) * 3; // At least one circle
    for (int i = 0; i <= numSteps; ++i) {
        float t = static_cast<float>(i) / numSteps;
        sf::Vector2f interpolatedPos = start + t * delta;

        this->_brushes->draw(zone, interpolatedPos, false);
    }
}
