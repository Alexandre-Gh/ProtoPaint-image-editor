/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "../Gui/RectWin.hpp"
#include "ToolRect.hpp"

EpiGimp::ToolRect::ToolRect()
{
    this->_gui = std::make_unique<GUI::RectWin>();

    this->_values["thickness"] = 4;
    this->_values["filled"] = false;
    this->_used = false;

    this->_shape.setOutlineColor(sf::Color::Black);
    this->_shape.setOutlineThickness(1);
    this->_shape.setFillColor(sf::Color::Transparent);
    this->_shape.setOrigin(0, 0);
}

void EpiGimp::ToolRect::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    this->_isInCanvas = zone->getSprite().getGlobalBounds().contains(win->getMousePosition());
    this->_isFirstInCanvas = zone->getSprite().getGlobalBounds().contains(this->_firstPos);
    if (win->isLeftMouseJustReleased() && this->_used) {
        if (this->_isFirstInCanvas) {
            zone->addDraw(this->_shape);
            GlobalData.setAddState(true);
        }
        this->_used = false;
    }
    if (!win->isLeftMousePressed()) {
        return;
    }
    this->_used = true;
    if (win->isLeftMouseJustPressed()) {
        this->_firstPos = win->getMousePosition();
        this->_shape.setPosition(this->_firstPos);
    }

    sf::Vector2f pos = win->getMousePosition();
    pos = zone->getSprite().getInverseTransform().transformPoint(pos);
    this->_shape.setOutlineColor(this->getMainColor());
    this->_shape.setFillColor(this->_values["filled"] ? this->getSecondColor() : sf::Color::Transparent);
    sf::Vector2f size = pos - this->_firstPos;
    this->_shape.setSize(size);
    this->_shape.setOutlineThickness(this->_values["thickness"]);
}

void EpiGimp::ToolRect::drawPreviewInCurrentCanvas(std::shared_ptr<Graphic::Window> win)
{
    if (this->_used && this->_isFirstInCanvas) {
        win->drawShape(this->_shape);
    }
}
