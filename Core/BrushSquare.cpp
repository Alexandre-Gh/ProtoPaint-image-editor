/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "BrushSquare.hpp"

EpiGimp::BrushSquare::BrushSquare()
{
    this->_previewBrush.setOutlineColor(sf::Color::Black);
    this->_previewBrush.setOutlineThickness(0.5f);
    this->_previewBrush.setFillColor(sf::Color::Transparent);
}

EpiGimp::BrushSquare::~BrushSquare()
{

}

void EpiGimp::BrushSquare::drawPreview(std::shared_ptr<Graphic::Window> win, sf::Vector2f pos)
{
    this->_previewBrush.setPosition(pos);
    win->drawShape(this->_previewBrush);
}

void EpiGimp::BrushSquare::draw(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f pos, bool add)
{
    this->_brush.setPosition(pos);
    if (add) {
        zone->addDraw(this->_brush);
    } else {
        zone->setDraw(this->_brush);
    }
}

void EpiGimp::BrushSquare::setSize(float size)
{
    sf::Vector2f vect(size, size);
    this->_brush.setSize(vect);
    this->_brush.setOrigin(size / 2, size / 2);
    this->_previewBrush.setSize(vect);
    this->_previewBrush.setOrigin(size / 2, size / 2);
    this->_size = size;
}

void EpiGimp::BrushSquare::setColor(sf::Color color)
{
    this->_brush.setFillColor(color);
    this->_color = color;
}
