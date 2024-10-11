/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "ToolBrush.hpp"
#include "../Gui/BrushWin.hpp"
#include "BrushCircle.hpp"
#include "BrushSquare.hpp"
#include "BrushLine.hpp"

EpiGimp::ToolBrush::ToolBrush()
{
    this->_gui = std::make_unique<GUI::BrushWin>();

    this->_values["brush"] = 0;
    this->_values["size"] = 4;
    this->_values["gradient"] = false;
    this->_values["rainbow"] = false;

    this->_brushes.push_back(std::make_unique<EpiGimp::BrushCircle>());
    this->_brushes.push_back(std::make_unique<EpiGimp::BrushSquare>());
    this->_brushes.push_back(std::make_unique<EpiGimp::BrushLine>(45));
    this->_brushes.push_back(std::make_unique<EpiGimp::BrushLine>(-45));
}

void EpiGimp::ToolBrush::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    int index = this->_values["brush"];
    if (win->isLeftMouseJustReleased() && this->_used) {
        GlobalData.setAddState(true);
        this->_used = false;
    }
    if (!win->isLeftMousePressed()
        || !zone->getSprite().getGlobalBounds().contains(win->getMousePosition())) {
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
    pos = zone->getSprite().getInverseTransform().transformPoint(pos);
    sf::Color brushColor;
    if (this->_values["rainbow"]) {
        brushColor = this->getRainbowColor(this->_brushes[index]->getColor());
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

void EpiGimp::ToolBrush::drawPreview(std::shared_ptr<Graphic::Window> win)
{
    int index = this->_values["brush"];
    this->_brushes[index]->setSize(this->_values["size"]);
    this->_brushes[index]->drawPreview(win, win->getMousePosition());
}

void EpiGimp::ToolBrush::drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end)
{
    int index = this->_values["brush"];
    sf::Vector2f delta = end - start;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    const int numSteps = std::max((int)(distance / this->_values["size"]), 1) * 3; // At least one circle
    for (int i = 0; i <= numSteps; ++i) {
        float t = static_cast<float>(i) / numSteps;
        sf::Vector2f interpolatedPos = start + t * delta;

        this->_brushes[index]->draw(zone, interpolatedPos, this->_values["gradient"]);
    }
}

sf::Color EpiGimp::ToolBrush::getRainbowColor(const sf::Color& currentColor) {
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

    return nextColor;
}
