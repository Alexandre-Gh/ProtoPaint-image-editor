/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "ToolBrush.hpp"
#include "../Gui/BrushWin.hpp"

EpiGimp::ToolBrush::ToolBrush()
{
    this->_gui = std::make_unique<GUI::BrushWin>();

    this->_values["size"] = 4;
    this->_values["gradient"] = false;
    this->_brush;
    this->_previewBrush.setOutlineColor(sf::Color::Black);
    this->_previewBrush.setOutlineThickness(1);
    this->_previewBrush.setFillColor(sf::Color::Transparent);
}

void EpiGimp::ToolBrush::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    if (!win->isLeftMouseJustPressed()) {
        if (!win->isLeftMousePressed()
            || !zone->getSprite().getGlobalBounds().contains(win->getMousePosition())
            || win->getMouseTranslation() == sf::Vector2f{0, 0}) {
            return;
        }
    }

    sf::Vector2f pos = win->getMousePosition();
    pos = zone->getSprite().getInverseTransform().transformPoint(pos);
    sf::Color brushColor = this->getMainColor();

    if (this->_values["gradient"]) {
        brushColor.a /= 20;
    }

    this->_brush.setRadius(this->_values["size"]);
    this->_brush.setOrigin(this->_values["size"], this->_values["size"]);
    this->_brush.setFillColor(brushColor);
    this->_brush.setPosition(pos);

    sf::Vector2f lastMousePos = pos - win->getMouseTranslation();

    if (this->_values["gradient"]) {
        zone->addDraw(this->_brush);
    } else {
        zone->setDraw(this->_brush);
    }
}

void EpiGimp::ToolBrush::drawPreview(std::shared_ptr<Graphic::Window> win)
{
    this->_previewBrush.setRadius(this->_values["size"]);
    this->_previewBrush.setOrigin(this->_values["size"], this->_values["size"]);
    this->_previewBrush.setPosition(win->getMousePosition());
    win->drawShape(this->_previewBrush);
}
