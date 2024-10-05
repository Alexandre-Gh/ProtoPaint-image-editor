/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "Layer.hpp"

EpiGimp::Layer::Layer(std::string name, unsigned int w, unsigned int h)
{
    this->_drawZone = std::make_shared<Graphic::DrawZone>(w, h);
    this->_name = name;
    this->_visible = true;
}

EpiGimp::Layer::Layer(const Layer& other)
{
    this->_drawZone = other._drawZone->clone();
    this->_name = other._name;
    this->_visible = other._visible;
}

const std::shared_ptr<Graphic::DrawZone> &EpiGimp::Layer::getDrawZone()
{
    return this->_drawZone;
}

void EpiGimp::Layer::setName(std::string name)
{
    this->_name = name;
}

const std::string &EpiGimp::Layer::getName()
{
    return this->_name;
}

void EpiGimp::Layer::setVisible(bool visible)
{
    this->_visible = visible;
}

const bool &EpiGimp::Layer::isVisible()
{
    return this->_visible;
}
