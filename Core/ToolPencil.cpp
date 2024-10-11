/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "ToolPencil.hpp"

EpiGimp::ToolPencil::ToolPencil()
{

}

void EpiGimp::ToolPencil::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
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

    sf::Vector2f lastPos = pos - win->getMouseTranslation();
    this->drawLine(zone, lastPos, pos);
}

void EpiGimp::ToolPencil::drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end)
{
    sf::Vector2f delta = end - start;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    const int numSteps = std::max((int)(distance), 1) * 3; // At least one circle
    for (int i = 0; i <= numSteps; ++i) {
        float t = static_cast<float>(i) / numSteps;
        sf::Vector2f interpolatedPos = start + t * delta;

        zone->setPixel(interpolatedPos, GlobalData.getMainColor());
    }
}
