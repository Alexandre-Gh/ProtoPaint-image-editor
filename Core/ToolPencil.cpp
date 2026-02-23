/*
** ProtoPaint
** File description:
** Core
*/

#include "ToolPencil.hpp"

ProtoPaint::ToolPencil::ToolPencil()
{

}

void ProtoPaint::ToolPencil::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
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

    sf::Vector2f lastPos = pos - win->getMouseTranslation();
    this->drawLine(zone, lastPos, pos);
}

void ProtoPaint::ToolPencil::drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end)
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
