/*
** ProtoPaint
** File description:
** Core
*/

#include "ToolBrush.hpp"
#include "../Gui/BrushWin.hpp"
#include "BrushCircle.hpp"
#include "BrushSquare.hpp"
#include "BrushLine.hpp"

ProtoPaint::ToolBrush::ToolBrush()
{
    this->_gui = std::make_unique<GUI::BrushWin>();

    this->_values["brush"] = 0;
    this->_values["size"] = 4;
    this->_values["gradient"] = false;
    this->_values["rainbow"] = false;
    this->_values["symetricalHor"] = false;
    this->_values["symetricalVert"] = false;

    this->_brushes.push_back(std::make_unique<ProtoPaint::BrushCircle>());
    this->_brushes.push_back(std::make_unique<ProtoPaint::BrushSquare>());
    this->_brushes.push_back(std::make_unique<ProtoPaint::BrushLine>(45));
    this->_brushes.push_back(std::make_unique<ProtoPaint::BrushLine>(-45));
}

void ProtoPaint::ToolBrush::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
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
    if ((this->_values["gradient"] || this->_values["rainbow"]) && win->getMouseTranslation() == (sf::Vector2f){0, 0}) {
        return;
    }
    if (!this->_used) {
        this->_brushes[index]->setColor(this->getMainColor());
    }
    this->_used = true;

    sf::Vector2f pos = win->getMousePosition();
    pos = zone->getRelatedPosition(pos);
    sf::Color brushColor;
    if (this->_values["rainbow"]) {
        brushColor = this->getRainbowColor(this->_brushes[index]->getColor());
        brushColor.a = this->getMainColor().a;
    } else {
        brushColor = this->getMainColor();
    }

    if (this->_values["gradient"]) {
        brushColor.a /= 20;
    }

    this->_brushes[index]->setColor(brushColor);

    sf::Vector2f lastPos = pos - win->getMouseTranslation();
    this->drawLine(zone, lastPos, pos);

}

void ProtoPaint::ToolBrush::drawPreview(std::shared_ptr<Graphic::Window> win)
{
    int index = this->_values["brush"];
    this->_brushes[index]->setSize(this->_values["size"]);
    this->_brushes[index]->drawPreview(win, win->getMousePosition());
}

void ProtoPaint::ToolBrush::drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end)
{
    int index = this->_values["brush"];
    sf::Vector2f delta = end - start;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    int numSteps = std::max((int)(distance / this->_values["size"]), 1) * 3; // At least one brush
    if (index == 2 || index == 3) {
        numSteps = numSteps * 10;
    }
    for (int i = 0; i <= numSteps; ++i) {
        float t = static_cast<float>(i) / numSteps;
        sf::Vector2f interpolatedPos = start + t * delta;
        float initialX = interpolatedPos.x;
        this->_brushes[index]->draw(zone, interpolatedPos, this->_values["gradient"]);
        if (this->_values["symetricalHor"]) {
            interpolatedPos.x = zone->getSize().x - interpolatedPos.x;
            this->_brushes[index]->draw(zone, interpolatedPos, this->_values["gradient"]);
        }
        if (this->_values["symetricalVert"]) {
            interpolatedPos.y = zone->getSize().y - interpolatedPos.y;
            this->_brushes[index]->draw(zone, interpolatedPos, this->_values["gradient"]);
        }
        if (this->_values["symetricalVert"] && this->_values["symetricalVert"]) {
            interpolatedPos.x = initialX;
            this->_brushes[index]->draw(zone, interpolatedPos, this->_values["gradient"]);
        }
    }
}

sf::Color ProtoPaint::ToolBrush::getRainbowColor(const sf::Color& currentColor) {
    sf::Color nextColor = currentColor;

    if (currentColor.r == 255 && currentColor.g < 255) {
        nextColor.r = 255;
        nextColor.g = currentColor.g + 5;
        nextColor.b = 0;
    } else if (currentColor.g == 255 && currentColor.b < 255) {
        nextColor.r = 0;
        nextColor.g = 255;
        nextColor.b = currentColor.b + 5;
    } else if (currentColor.b == 255) {
        nextColor.r = currentColor.r + 5;
        nextColor.g = 0;
        nextColor.b = 255;
    } else {
        nextColor.r = 255;
        nextColor.g = 0;
        nextColor.b = 0;
    }

    nextColor.r = (nextColor.r > 255) ? 255 : nextColor.r;
    nextColor.g = (nextColor.g > 255) ? 255 : nextColor.g;
    nextColor.b = (nextColor.b > 255) ? 255 : nextColor.b;

    nextColor.a = currentColor.a;

    return nextColor;
}
