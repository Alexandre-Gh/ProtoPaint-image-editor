/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** DrawZone
*/

#include "DrawZone.hpp"

Graphic::DrawZone::DrawZone(unsigned int w, unsigned int h)
{
    this->_zone.create(w, h);
    this->_displayer.setOrigin(w / 2, h / 2);
    this->_zone.clear(GlobalData.getSecondColor());
    this->_displayer.setTexture(this->_zone.getTexture(), true);
}

Graphic::DrawZone::~DrawZone()
{

}

const sf::Sprite &Graphic::DrawZone::getSprite()
{
    return this->_displayer;
}

void Graphic::DrawZone::setPixel(sf::Vector2f pos, sf::Color color)
{
    
}

const sf::Color &Graphic::DrawZone::getPixel(sf::Vector2u pos)
{
    
}

void Graphic::DrawZone::addDraw(sf::Drawable &drawable)
{
    this->_zone.draw(drawable);
}

void Graphic::DrawZone::setAllPixel(sf::Color)
{
    
}

void Graphic::DrawZone::setPosition(int x, int y)
{
    this->_displayer.setPosition(x, y);
}

const sf::Vector2f &Graphic::DrawZone::getPosition()
{
    return this->_displayer.getPosition();
}

void Graphic::DrawZone::setSize(unsigned int w, unsigned int h)
{
    this->_displayer.setTextureRect(sf::IntRect(0, 0, w, h));
    this->_displayer.setOrigin(w / 2, h / 2);
}

