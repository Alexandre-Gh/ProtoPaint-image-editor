/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "../Gui/LineWin.hpp"
#include "ToolLine.hpp"

EpiGimp::ToolLine::ToolLine()
{
    this->_gui = std::make_unique<GUI::LineWin>();

    this->_previewZone = std::make_shared<Graphic::DrawZone>(GlobalData.getCanvasSize().x, GlobalData.getCanvasSize().y);

    this->_values["thickness"] = 4;
    this->_values["rounded"] = false;
    this->_used = false;

    this->_shape.setOutlineColor(sf::Color::Black);
    this->_shape.setOutlineThickness(1);
    this->_shape.setFillColor(sf::Color::Black);
    this->_shape.setOrigin(0, 0);
}

void EpiGimp::ToolLine::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    this->_isInCanvas = zone->isInZone(win->getMousePosition());
    this->_isFirstInCanvas = zone->isInZone(this->_firstPos);
    if (win->isLeftMouseJustReleased() && this->_used) {
        if (this->_isFirstInCanvas) {
            zone->addDraw(this->_shape);
            this->drawBorders(zone, this->_firstPos, win->getMousePosition());
            this->_border.setPosition(this->_firstPos);
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
    pos = zone->getRelatedPosition(pos);
    this->_shape.setOutlineColor(this->getMainColor());
    this->_shape.setFillColor(this->getMainColor());
    sf::Vector2f direction = pos - this->_firstPos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    this->_shape.setSize(sf::Vector2f(length, this->_values["thickness"]));
    this->_shape.setOrigin(0, this->_values["thickness"] / 2.0f);
    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159;
    this->_shape.setRotation(angle);
    this->_shape.setPosition(this->_firstPos);
}

void EpiGimp::ToolLine::drawPreviewInCurrentCanvas(std::shared_ptr<Graphic::Window> win)
{
    if (this->_used && this->_isFirstInCanvas) {
        this->_previewZone->setSize(GlobalData.getCanvasSize().x, GlobalData.getCanvasSize().y);
        this->_previewZone->clear();
        _previewZone->addDraw(this->_shape);
        this->drawBorders(this->_previewZone, this->_firstPos, win->getMousePosition());
        win->drawSprite(_previewZone->getSprite());
    }
}

void EpiGimp::ToolLine::drawBorders(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f pos1, sf::Vector2f pos2)
{
    if (this->_values["rounded"]) {
        this->_border.setFillColor(this->getMainColor());
        this->_border.setRadius(this->_values["thickness"] / 2 + 1);
        this->_border.setOrigin(this->_border.getRadius(), this->_border.getRadius());
        this->_border.setPosition(pos1);
        zone->addDraw(this->_border);
        this->_border.setPosition(pos2);
        zone->addDraw(this->_border);
    }
}
