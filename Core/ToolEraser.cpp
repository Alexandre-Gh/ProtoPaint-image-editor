/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "Core.hpp"
#include "ToolEraser.hpp"

EpiGimp::ToolEraser::ToolEraser()
{
    this->_values["size"] = 24;
    this->_brush;
}

void EpiGimp::ToolEraser::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    if (!win->isLeftMousePressed()) {
        return;
    }

    sf::Vector2f pos = zone->getSprite().getInverseTransform().transformPoint(win->getMousePosition());
    sf::Color brushColor = GlobalData.getSecondColor();

    this->_brush.setRadius(this->_values["size"]);
    this->_brush.setOrigin(this->_values["size"] / 2, this->_values["size"] / 2);
    this->_brush.setFillColor(brushColor);
    this->_brush.setPosition(pos);
    zone->addDraw(this->_brush);
}