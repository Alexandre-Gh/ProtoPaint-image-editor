/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "BrushCircle.hpp"

EpiGimp::BrushCircle::BrushCircle()
{
    this->_previewBrush.setOutlineColor(sf::Color::Black);
    this->_previewBrush.setOutlineThickness(1);
    this->_previewBrush.setFillColor(sf::Color::Transparent);
}

EpiGimp::BrushCircle::~BrushCircle()
{

}

void EpiGimp::BrushCircle::drawPreview(std::shared_ptr<Graphic::Window> win, sf::Vector2f pos)
{
    this->_previewBrush.setPosition(pos);
    win->drawShape(this->_previewBrush);
}

void EpiGimp::BrushCircle::draw(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f pos, bool add)
{
    this->_brush.setPosition(pos);
    if (add) {
        zone->addDraw(this->_brush);
    } else {
        zone->setDraw(this->_brush);
    }
}

void EpiGimp::BrushCircle::setSize(float size)
{
    float value = size / 2;
    this->_brush.setRadius(value);
    this->_brush.setOrigin(value, value);
    this->_previewBrush.setRadius(value);
    this->_previewBrush.setOrigin(value, value);
    this->_size = value;
}

void EpiGimp::BrushCircle::setColor(sf::Color color)
{
    this->_brush.setFillColor(color);
    this->_color = color;
}
