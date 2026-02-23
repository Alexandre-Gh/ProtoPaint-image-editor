/*
** ProtoPaint
** File description:
** Core
*/

#include "ABrush.hpp"

ProtoPaint::ABrush::ABrush()
{

}

ProtoPaint::ABrush::~ABrush()
{

}

void ProtoPaint::ABrush::drawPreview(std::shared_ptr<Graphic::Window> win, sf::Vector2f pos)
{
    sf::CircleShape shape;
    shape.setPosition(pos);
    win->drawShape(shape);
}

void ProtoPaint::ABrush::draw(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f pos, bool add)
{
    sf::CircleShape shape;
    shape.setPosition(pos);
    if (add) {
        zone->addDraw(shape);
    } else {
        zone->setDraw(shape);
    }
}

void ProtoPaint::ABrush::setSize(float size)
{
    this->_size = size;
}

const float &ProtoPaint::ABrush::getSize()
{
    return this->_size;
}

void ProtoPaint::ABrush::setColor(sf::Color color)
{
    this->_color = color;
}

const sf::Color &ProtoPaint::ABrush::getColor()
{
    return this->_color;
}
