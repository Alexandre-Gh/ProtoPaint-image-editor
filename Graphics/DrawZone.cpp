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
    // this->_displayer.setOrigin(w / 2, h / 2);
    this->_zone.clear(GlobalData.getSecondColor());
    this->_displayer.setTexture(this->_zone.getTexture(), true);
    this->setSize(w, h);
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
    sf::Image im = this->_zone.getTexture().copyToImage();
    im.setPixel(pos.x, pos.y, color);
}

const sf::Color &Graphic::DrawZone::getPixel(sf::Vector2u pos)
{
    
}

void Graphic::DrawZone::addDraw(sf::Drawable &drawable)
{
    this->_zone.draw(drawable);
}

void Graphic::DrawZone::fill(sf::Vector2f pos, sf::Color color)
{
    sf::Image image = this->_zone.getTexture().copyToImage();

    sf::Color targetColor = image.getPixel(pos.x, pos.y);
    if (targetColor == color) {
        return;
    }

    std::stack<sf::Vector2i> pixels;
    pixels.push(sf::Vector2i(pos.x, pos.y));

    while (!pixels.empty()) {
        sf::Vector2i p = pixels.top();
        pixels.pop();

        // Check bounds
        if (p.x < 0 || p.x >= image.getSize().x || p.y < 0 || p.y >= image.getSize().y)
            continue;

        // Check if the current pixel matches the target color
        if (image.getPixel(p.x, p.y) != targetColor)
            continue;

        // Set the pixel to the fill color
        image.setPixel(p.x, p.y, color);

        // Push neighboring pixels
        pixels.push(sf::Vector2i(p.x + 1, p.y));
        pixels.push(sf::Vector2i(p.x - 1, p.y));
        pixels.push(sf::Vector2i(p.x, p.y + 1));
        pixels.push(sf::Vector2i(p.x, p.y - 1));
    }
    image.flipVertically();
    sf::Texture final;
    final.loadFromImage(image);
    this->_zone.draw(sf::Sprite(final));
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

