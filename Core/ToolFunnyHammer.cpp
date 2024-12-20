/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "ToolFunnyHammer.hpp"
#include "../Gui/FunnyHammerWin.hpp"
#include "BrushCircle.hpp"
#include "BrushSquare.hpp"

EpiGimp::ToolFunnyHammer::ToolFunnyHammer()
{
    this->_gui = std::make_unique<GUI::FunnyHammerWin>();

    this->_drawTexture.loadFromFile("./assets/glass.png");
    this->_drawSprite.setTexture(this->_drawTexture);
    sf::Vector2f size = (sf::Vector2f)this->_drawTexture.getSize();
    size.x = size.x / 2;
    size.y = size.y / 2;
    this->_drawSprite.setOrigin(size);

    this->_hammerTexture.loadFromFile("./assets/hammer.png");
    this->_hammerSprite.setTexture(this->_hammerTexture);
    size = (sf::Vector2f)this->_hammerTexture.getSize();
    size.x = 0;
    size.y = size.y;
    this->_hammerSprite.setOrigin(size);

    this->_buffer.loadFromFile("./assets/glass.ogg");
    this->_snd.setBuffer(this->_buffer);
    this->_snd.setVolume(100);

    this->_values["size"] = 10;
    this->_values["rotate"] = false;
}

void EpiGimp::ToolFunnyHammer::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    if (win->isLeftMouseJustPressed() && zone->isInZone(win->getMousePosition())) {
        if (this->_values["rotate"]) {
            this->_drawSprite.setRotation(std::rand() % 360);
        } else {
            this->_drawSprite.setRotation(0);
        }
        this->_snd.play();
        this->_drawSprite.setScale(sf::Vector2f{(float)this->_values["size"] / 40, (float)this->_values["size"] / 40});
        this->_drawSprite.setPosition(win->getMousePosition());
        zone->addDraw(this->_drawSprite);
        GlobalData.setAddState(true);
    }
}

void EpiGimp::ToolFunnyHammer::drawPreview(std::shared_ptr<Graphic::Window> win)
{
    this->_hammerSprite.setScale(sf::Vector2f{(float)this->_values["size"] / 10, (float)this->_values["size"] / 10});
    if (win->isLeftMousePressed()) {
        this->_hammerSprite.setRotation(-90);
    } else {
        this->_hammerSprite.setRotation(0);
    }
    this->_hammerSprite.setPosition(win->getMousePosition() + sf::Vector2f((float)this->_values["size"] * 9, 0));
    win->drawSprite(this->_hammerSprite);
}
