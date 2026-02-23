/*
** ProtoPaint
** File description:
** Core
*/

#include "BrushLine.hpp"

ProtoPaint::BrushLine::BrushLine(float angle)
{
    this->_previewBrush.setOutlineColor(sf::Color::Black);
    this->_previewBrush.setFillColor(sf::Color::Black);
    this->_previewBrush.rotate(angle);
    this->_brush.rotate(angle);
}

ProtoPaint::BrushLine::~BrushLine()
{

}

void ProtoPaint::BrushLine::drawPreview(std::shared_ptr<Graphic::Window> win, sf::Vector2f pos)
{
    this->_previewBrush.setPosition(pos);
    win->drawShape(this->_previewBrush);
}

void ProtoPaint::BrushLine::draw(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f pos, bool add)
{
    this->_brush.setPosition(pos);
    if (add) {
        zone->addDraw(this->_brush);
    } else {
        zone->setDraw(this->_brush);
    }
}

void ProtoPaint::BrushLine::setSize(float size)
{
    sf::RectangleShape vect;
    this->_brush.setSize({size, 2});
    this->_brush.setOrigin(size / 2, 0.5f);
    this->_previewBrush.setSize({size, 2});
    this->_previewBrush.setOrigin(size / 2, 0.5f);
    this->_size = size;
}

void ProtoPaint::BrushLine::setColor(sf::Color color)
{
    this->_brush.setFillColor(color);
    this->_color = color;
}
