/*
** ProtoPaint
** File description:
** Core
*/

#include "Layer.hpp"

ProtoPaint::Layer::Layer(std::string name, unsigned int w, unsigned int h)
{
    this->_drawZone = std::make_shared<Graphic::DrawZone>(w, h);
    this->_name = name;
    this->_visible = true;
}

ProtoPaint::Layer::Layer(const Layer& other)
{
    this->_drawZone = other._drawZone->clone();
    this->_name = other._name;
    this->_visible = other._visible;
}

const std::shared_ptr<Graphic::DrawZone> &ProtoPaint::Layer::getDrawZone()
{
    return this->_drawZone;
}

void ProtoPaint::Layer::setName(std::string name)
{
    this->_name = name;
}

const std::string &ProtoPaint::Layer::getName()
{
    return this->_name;
}

void ProtoPaint::Layer::setVisible(bool visible)
{
    this->_visible = visible;
}

const bool &ProtoPaint::Layer::isVisible()
{
    return this->_visible;
}
