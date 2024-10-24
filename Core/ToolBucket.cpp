/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "ToolBucket.hpp"

EpiGimp::ToolBucket::ToolBucket()
{
    this->_values["size"] = 4;
    this->_brush;
}

void EpiGimp::ToolBucket::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    if (!win->isLeftMouseJustPressed() || !zone->getSprite().getGlobalBounds().contains(win->getMousePosition())) {
        return;
    }
    GlobalData.setAddState(true);

    sf::Vector2f pos = win->getMousePosition();
    pos = zone->getRelatedPosition(pos);

    if (win->isKeyPressed(sf::Keyboard::LControl)) {
        zone->fill(pos, this->getSecondColor());
    } else {
        zone->fill(pos, this->getMainColor());
    }
}