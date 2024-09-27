/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "Core.hpp"
#include "ToolBrush.hpp"

EpiGimp::ToolBrush::ToolBrush()
{
    this->_values["size"] = 4;
    this->_brush;
}

void EpiGimp::ToolBrush::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    if (!win->isLeftMousePressed()
        || !zone->getSprite().getGlobalBounds().contains(win->getMousePosition())
        || win->getMouseTranslation() != sf::Vector2f{0, 0}) {
        return;
    }

    sf::Vector2f pos = win->getMousePosition();
    pos.y = -pos.y;
    pos = zone->getSprite().getInverseTransform().transformPoint(pos);
    sf::Color brushColor = this->getMainColor();

    this->_brush.setRadius(this->_values["size"]);
    this->_brush.setOrigin(this->_values["size"], this->_values["size"]);
    this->_brush.setFillColor(brushColor);
    this->_brush.setPosition(pos);

    zone->addDraw(this->_brush);
}