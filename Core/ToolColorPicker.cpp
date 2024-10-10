/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "ToolColorPicker.hpp"

EpiGimp::ToolColorPicker::ToolColorPicker()
{

}

void EpiGimp::ToolColorPicker::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    if (!win->isLeftMouseJustPressed() || !zone->getSprite().getGlobalBounds().contains(win->getMousePosition())) {
        return;
    }

    sf::Vector2f pos = win->getMousePosition();
    pos = zone->getSprite().getInverseTransform().transformPoint(pos);

    sf::Color picked(zone->getPixel(pos));

    if (win->isKeyPressed(sf::Keyboard::LControl)) {
        GlobalData.setSecondColor(picked);
    } else {
        GlobalData.setMainColor(picked);
    }
}