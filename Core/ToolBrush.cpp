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
    this->_values["rainbow"] = false;
    this->_rainbowPrevColor = sf::Color::Red;
    this->_previewBrush.setOutlineColor(sf::Color::Black);
    this->_previewBrush.setOutlineThickness(1);
    this->_previewBrush.setFillColor(sf::Color::Transparent);
}

void EpiGimp::ToolBrush::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    if (win->isLeftMouseJustReleased() && this->_used) {
        GlobalData.setAddState(true);
        this->_used = false;
    }

    if (!win->isLeftMousePressed()
        || !zone->getSprite().getGlobalBounds().contains(win->getMousePosition())) {
        return;
    }
    if ((this->_values["gradient"] || this->_values["rainbow"]) && win->getMouseTranslation() == (sf::Vector2f){0, 0}) {
        return;
    }

    this->_used = true;

    sf::Vector2f pos = win->getMousePosition();
    pos = zone->getSprite().getInverseTransform().transformPoint(pos);
    sf::Color brushColor;
    if (this->_values["rainbow"]) {
        brushColor = this->getRainbowColor(_rainbowPrevColor);
    } else {
        brushColor = this->getMainColor();

    }

    if (this->_values["gradient"]) {
        brushColor.a /= 20;
    }

    this->_brush.setRadius(this->_values["size"]);
    this->_brush.setOrigin(this->_values["size"], this->_values["size"]);
    this->_brush.setFillColor(brushColor);
    this->_brush.setPosition(pos);

    sf::Vector2f lastPos = pos - win->getMouseTranslation();

    sf::Vector2f delta = pos - lastPos;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    const int numSteps = std::max((int)(distance / this->_values["size"]), 1) * 3; // At least one circle
    for (int i = 0; i <= numSteps; ++i) {
        float t = static_cast<float>(i) / numSteps;
        sf::Vector2f interpolatedPos = lastPos + t * delta;
        this->_brush.setPosition(interpolatedPos);

        if (this->_values["gradient"]) {
            zone->addDraw(this->_brush);
        } else {
            zone->setDraw(this->_brush);
        }
    }

}

void EpiGimp::ToolBrush::drawPreview(std::shared_ptr<Graphic::Window> win)
{
    this->_previewBrush.setRadius(this->_values["size"]);
    this->_previewBrush.setOrigin(this->_values["size"], this->_values["size"]);
    this->_previewBrush.setPosition(win->getMousePosition());
    win->drawShape(this->_previewBrush);
}

sf::Color EpiGimp::ToolBrush::getRainbowColor(const sf::Color& currentColor) {
    sf::Color nextColor = currentColor;

    // Determine which color component should be set to 255
    if (currentColor.r == 255 && currentColor.g < 255) {
        nextColor.r = 255; // Keep red at 255
        nextColor.g = currentColor.g + 5; // Increment green
        nextColor.b = 0; // Reset blue
    } else if (currentColor.g == 255 && currentColor.b < 255) {
        nextColor.r = 0; // Reset red
        nextColor.g = 255; // Keep green at 255
        nextColor.b = currentColor.b + 5; // Increment blue
    } else if (currentColor.b == 255) {
        nextColor.r = currentColor.r + 5; // Increment red
        nextColor.g = 0; // Reset green
        nextColor.b = 255; // Keep blue at 255
    } else {
        nextColor.r = 255; // Reset red to start the cycle
        nextColor.g = 0; // Reset green
        nextColor.b = 0; // Reset blue
    }

    // Ensure the color values are capped between 0 and 255
    nextColor.r = (nextColor.r > 255) ? 255 : nextColor.r;
    nextColor.g = (nextColor.g > 255) ? 255 : nextColor.g;
    nextColor.b = (nextColor.b > 255) ? 255 : nextColor.b;

    _rainbowPrevColor = nextColor;
    return nextColor;
}