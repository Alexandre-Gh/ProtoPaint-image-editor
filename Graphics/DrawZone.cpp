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
    this->setSize(w, h);
    this->fill({0, 0}, sf::Color::Transparent);
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

void Graphic::DrawZone::setFromFile(std::string filepath)
{
    sf::Texture fileText;
    if (fileText.loadFromFile(filepath)) {
        this->_zone.draw(sf::Sprite(fileText));
        GlobalData.setCanvasSize(fileText.getSize().x, fileText.getSize().y);
    }
}

void Graphic::DrawZone::saveToFile(std::string filepath)
{
    sf::Image im = this->_zone.getTexture().copyToImage();
    im.saveToFile(filepath);
}

const sf::Color &Graphic::DrawZone::getPixel(sf::Vector2f pos)
{
    sf::Image image = this->_zone.getTexture().copyToImage();
    const sf::Color &targetColor = image.getPixel(pos.x, pos.y);

    return targetColor;
}

void Graphic::DrawZone::addDraw(sf::Drawable &drawable)
{
    this->_zone.draw(drawable);
}

void Graphic::DrawZone::setDraw(sf::Drawable &drawable)
{
    this->_zone.draw(drawable, sf::BlendNone);
}

void Graphic::DrawZone::addSprite(const sf::Sprite &spr)
{
    this->_zone.draw(spr);
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

        if (p.x < 0 || p.x >= image.getSize().x || p.y < 0 || p.y >= image.getSize().y)
            continue;

        if (image.getPixel(p.x, p.y) != targetColor)
            continue;

        image.setPixel(p.x, p.y, color);

        pixels.push(sf::Vector2i(p.x + 1, p.y));
        pixels.push(sf::Vector2i(p.x - 1, p.y));
        pixels.push(sf::Vector2i(p.x, p.y + 1));
        pixels.push(sf::Vector2i(p.x, p.y - 1));
    }
    sf::Texture final;
    final.loadFromImage(image);
    this->_zone.clear({0, 0, 0, 0});
    this->_zone.draw(sf::Sprite(final));
}

void Graphic::DrawZone::drawCheckeredBackground() {
    sf::Color lightGray(200, 200, 200);
    sf::Color darkGray(150, 150, 150);

    int squareSize = this->_size.x / 20;

    for (int x = 0; x < this->_size.x; x += squareSize) {
        for (int y = 0; y < this->_size.y; y += squareSize) {
            sf::Color color = ((x / squareSize) % 2 == (y / squareSize) % 2) ? lightGray : darkGray;

            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setFillColor(color);
            square.setPosition(x, y);
            this->_zone.draw(square);
        }
    }
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
    sf::RenderTexture tempZone;
    tempZone.create(this->_zone.getSize().x, this->_zone.getSize().y);
    tempZone.clear(sf::Color::Transparent);

    sf::Sprite oldSpr(this->_zone.getTexture());
    tempZone.draw(oldSpr);
    tempZone.display();

    this->_zone.create(w, h);
    this->_zone.clear(sf::Color::Transparent);

    sf::Sprite newSpr(tempZone.getTexture());
    newSpr.setScale(w / this->_zone.getSize().x, h / this->_zone.getSize().y);
    this->_zone.draw(newSpr);

    this->_zone.display();

    this->_displayer.setTexture(this->_zone.getTexture(), true);
    this->_size.x = w;
    this->_size.y = h;
}

const sf::Vector2f &Graphic::DrawZone::getSize()
{
    return this->_size;
}

