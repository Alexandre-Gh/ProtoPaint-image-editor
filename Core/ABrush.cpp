/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "ABrush.hpp"

EpiGimp::ABrush::ABrush()
{

}

EpiGimp::ABrush::~ABrush()
{

}

void EpiGimp::ABrush::drawPreview(std::shared_ptr<Graphic::Window> win, sf::Vector2f pos)
{
    sf::CircleShape shape;
    shape.setPosition(pos);
    win->drawShape(shape);
}

void EpiGimp::ABrush::draw(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f pos, bool add)
{
    sf::CircleShape shape;
    shape.setPosition(pos);
    if (add) {
        zone->addDraw(shape);
    } else {
        zone->setDraw(shape);
    }
}

void EpiGimp::ABrush::setSize(float size)
{
    this->_size = size;
}

const float &EpiGimp::ABrush::getSize()
{
    return this->_size;
}

void EpiGimp::ABrush::setColor(sf::Color color)
{
    this->_color = color;
}

const sf::Color &EpiGimp::ABrush::getColor()
{
    return this->_color;
}
