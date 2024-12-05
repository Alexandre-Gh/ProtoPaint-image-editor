/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "ToolImage.hpp"
#include "../Gui/ImageWin.hpp"
#include "BrushCircle.hpp"
#include "BrushSquare.hpp"

EpiGimp::ToolImage::ToolImage()
{
    this->_gui = std::make_unique<GUI::ImageWin>();

    this->_texture.loadFromFile("./assets/templateImageBrush.png");
    this->_sprite.setTexture(this->_texture);
    sf::Vector2f size = (sf::Vector2f)this->_texture.getSize();
    size.x = size.x / 2;
    size.y = size.y / 2;
    this->_sprite.setOrigin(size);
}

void EpiGimp::ToolImage::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    if (this->_currentFilepath != GlobalData.getImageBrushFilepath()) {
        this->_currentFilepath = GlobalData.getImageBrushFilepath();
        this->_texture.loadFromFile(this->_currentFilepath);
        this->_sprite.setTexture(this->_texture, true);
        sf::Vector2f size = (sf::Vector2f)this->_texture.getSize();
        size.x = size.x / 2;
        size.y = size.y / 2;
        this->_sprite.setOrigin(size);
        this->_imageEmpty = false;
    }
    if (win->isLeftMouseJustReleased() && this->_used && !this->_imageEmpty) {
        GlobalData.setAddState(true);
        this->_used = false;
    }
    if (!win->isLeftMousePressed()
        || !zone->isInZone(win->getMousePosition())
        || this->_imageEmpty) {
        return;
    }
    this->_used = true;

    sf::Vector2f pos = win->getMousePosition();
    pos = zone->getRelatedPosition(pos);

    sf::Vector2f lastPos = pos - win->getMouseTranslation();

    this->drawLine(zone, lastPos, pos);
}

void EpiGimp::ToolImage::drawPreview(std::shared_ptr<Graphic::Window> win)
{
    this->_sprite.setPosition(win->getMousePosition());
    win->drawSprite(this->_sprite);
}

void EpiGimp::ToolImage::drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end)
{
    sf::Vector2f delta = end - start;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    const int numSteps = std::max((int)(distance), 1) * 2;
    for (int i = 0; i <= numSteps; ++i) {
        float t = static_cast<float>(i) / numSteps;
        sf::Vector2f interpolatedPos = start + t * delta;
        zone->addDraw(this->_sprite);
    }
}
