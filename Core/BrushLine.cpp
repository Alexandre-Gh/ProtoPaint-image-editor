/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "BrushLine.hpp"

EpiGimp::BrushLine::BrushLine(float angle)
{
    this->_previewBrush.setOutlineColor(sf::Color::Black);
    this->_previewBrush.setFillColor(sf::Color::Black);
    this->_previewBrush.rotate(angle);
    this->_brush.rotate(angle);
}

EpiGimp::BrushLine::~BrushLine()
{

}

void EpiGimp::BrushLine::drawPreview(std::shared_ptr<Graphic::Window> win, sf::Vector2f pos)
{
    this->_previewBrush.setPosition(pos);
    win->drawShape(this->_previewBrush);
}

void EpiGimp::BrushLine::draw(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f pos, bool add)
{
    this->_brush.setPosition(pos);
    if (add) {
        zone->addDraw(this->_brush);
    } else {
        zone->setDraw(this->_brush);
    }
}

void EpiGimp::BrushLine::setSize(float size)
{
    sf::RectangleShape vect;
    this->_brush.setSize({size, 2});
    this->_brush.setOrigin(size / 2, 0.5f);
    this->_previewBrush.setSize({size, 2});
    this->_previewBrush.setOrigin(size / 2, 0.5f);
    this->_size = size;
}

void EpiGimp::BrushLine::setColor(sf::Color color)
{
    this->_brush.setFillColor(color);
    this->_color = color;
}
