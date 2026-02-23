/*
** ProtoPaint
** File description:
** Core
*/

#include "BrushCircle.hpp"

ProtoPaint::BrushCircle::BrushCircle()
{
    this->_previewBrush.setOutlineColor(sf::Color::Black);
    this->_previewBrush.setOutlineThickness(0.5f);
    this->_previewBrush.setFillColor(sf::Color::Transparent);
}

ProtoPaint::BrushCircle::~BrushCircle()
{

}

void ProtoPaint::BrushCircle::drawPreview(std::shared_ptr<Graphic::Window> win, sf::Vector2f pos)
{
    this->_previewBrush.setPosition(pos);
    win->drawShape(this->_previewBrush);
}

void ProtoPaint::BrushCircle::draw(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f pos, bool add)
{
    this->_brush.setPosition(pos);
    if (add) {
        zone->addDraw(this->_brush);
    } else {
        zone->setDraw(this->_brush);
    }
}

void ProtoPaint::BrushCircle::setSize(float size)
{
    float value = size / 2;
    this->_brush.setRadius(value);
    this->_brush.setOrigin(value, value);
    this->_previewBrush.setRadius(value);
    this->_previewBrush.setOrigin(value, value);
    this->_size = value;
}

void ProtoPaint::BrushCircle::setColor(sf::Color color)
{
    this->_brush.setFillColor(color);
    this->_color = color;
}
