/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "ToolEraser.hpp"
#include "../Gui/EraserWin.hpp"

EpiGimp::ToolEraser::ToolEraser()
{
    this->_gui = std::make_unique<GUI::EraserWin>();

    this->_values["size"] = 4;
    this->_brush;
    this->_previewBrush.setOutlineColor(sf::Color::Black);
    this->_previewBrush.setOutlineThickness(1);
    this->_previewBrush.setFillColor(sf::Color::Transparent);
}

void EpiGimp::ToolEraser::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    if (win->isLeftMouseJustReleased() && this->_used) {
        GlobalData.setAddState(true);
        this->_used = false;
    }

    if (!win->isLeftMousePressed()
        || !zone->getSprite().getGlobalBounds().contains(win->getMousePosition())
        || win->getMouseTranslation() == sf::Vector2f{0, 0}) {
        return;
    }
    this->_used = true;

    sf::Vector2f pos = win->getMousePosition();
    pos = zone->getSprite().getInverseTransform().transformPoint(pos);
    sf::Color brushColor = GlobalData.getSecondColor();

    this->_brush.setRadius(this->_values["size"]);
    this->_brush.setOrigin(this->_values["size"], this->_values["size"]);
    this->_brush.setFillColor(brushColor);
    this->_brush.setPosition(pos);

    sf::Vector2f lastPos = pos - win->getMouseTranslation();

    sf::Vector2f delta = pos - lastPos;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    const int numSteps = std::max((int)(distance / this->_values["size"]), 1) * 3; // At least one circle
    for (int i = 0; i <= numSteps; ++i) {
        float t = static_cast<float>(i) / numSteps;
        sf::Vector2f interpolatedPos = lastPos + t * delta;
        this->_brush.setPosition(interpolatedPos);
        zone->setDraw(this->_brush);
    }
}

void EpiGimp::ToolEraser::drawPreview(std::shared_ptr<Graphic::Window> win)
{
    this->_previewBrush.setRadius(this->_values["size"]);
    this->_previewBrush.setOrigin(this->_values["size"], this->_values["size"]);
    this->_previewBrush.setPosition(win->getMousePosition());
    win->drawShape(this->_previewBrush);
}
