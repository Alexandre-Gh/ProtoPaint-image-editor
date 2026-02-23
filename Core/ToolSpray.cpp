/*
** ProtoPaint
** File description:
** Core
*/

#include "ToolSpray.hpp"
#include "../Gui/SprayWin.hpp"
#include "BrushCircle.hpp"
#include "BrushSquare.hpp"
#include "BrushLine.hpp"

ProtoPaint::ToolSpray::ToolSpray()
{
    this->_gui = std::make_unique<GUI::SprayWin>();

    this->_values["brush"] = 0;
    this->_values["size"] = 30;
    this->_values["gradient"] = false;
    this->_values["rainbow"] = false;

    this->_brushes.push_back(std::make_unique<ProtoPaint::BrushCircle>());
    // this->_brushes.push_back(std::make_unique<ProtoPaint::BrushSquare>());
    // this->_brushes.push_back(std::make_unique<ProtoPaint::BrushLine>(45));
    // this->_brushes.push_back(std::make_unique<ProtoPaint::BrushLine>(-45));
}

void ProtoPaint::ToolSpray::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    int index = this->_values["brush"];
    if (win->isLeftMouseJustReleased() && this->_used) {
        GlobalData.setAddState(true);
        this->_used = false;
    }
    if (!win->isLeftMousePressed()
        || !zone->isInZone(win->getMousePosition())) {
        return;
    }
    if (!this->_used) {
        // this->_brushes[index]->setColor(this->getMainColor());
    }
    this->_used = true;

    sf::Vector2f pos = win->getMousePosition();
    pos = zone->getRelatedPosition(pos);
    if (this->_values["rainbow"]) {
        this->_brushColor = this->getRainbowColor(this->_brushColor);
    } else {
        this->_brushColor = this->getMainColor();
    }

    if (this->_values["gradient"]) {
        this->_brushColor.a /= 20;
    }
    pos = getRandomPositionInRadius(pos, this->_values["size"] / 2);
    zone->setPixel(pos, this->_brushColor);
    // this->_brushes[index]->setColor(brushColor);

    sf::Vector2f lastPos = pos - win->getMouseTranslation();
    // this->drawLine(zone, lastPos, pos);
    // this->_brushes[index]->draw(zone, pos, this->_values["gradient"]);

}

void ProtoPaint::ToolSpray::drawPreview(std::shared_ptr<Graphic::Window> win)
{
    int index = this->_values["brush"];
    this->_brushes[index]->setSize(this->_values["size"]);
    this->_brushes[index]->drawPreview(win, win->getMousePosition());
}

void ProtoPaint::ToolSpray::drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end)
{
    int index = this->_values["brush"];
    sf::Vector2f delta = end - start;
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    int numSteps = std::max((int)(distance / this->_values["size"]), 1) * 3; // At least one brush
    if (this->_values["brush"] == 2 || this->_values["brush"] == 3) {
        numSteps = numSteps * 10;
    }
    for (int i = 0; i <= numSteps; ++i) {
        float t = static_cast<float>(i) / numSteps;
        sf::Vector2f interpolatedPos = start + t * delta;

        // this->_brushes[index]->draw(zone, interpolatedPos, this->_values["gradient"]);
    }
}

sf::Color ProtoPaint::ToolSpray::getRainbowColor(const sf::Color& currentColor) {
    sf::Color nextColor = currentColor;

    if (currentColor.r == 255 && currentColor.g < 255) {
        nextColor.r = 255;
        nextColor.g = currentColor.g + 5;
        nextColor.b = 0;
    } else if (currentColor.g == 255 && currentColor.b < 255) {
        nextColor.r = 0;
        nextColor.g = 255;
        nextColor.b = currentColor.b + 5;
    } else if (currentColor.b == 255) {
        nextColor.r = currentColor.r + 5;
        nextColor.g = 0;
        nextColor.b = 255;
    } else {
        nextColor.r = 255;
        nextColor.g = 0;
        nextColor.b = 0;
    }

    nextColor.r = (nextColor.r > 255) ? 255 : nextColor.r;
    nextColor.g = (nextColor.g > 255) ? 255 : nextColor.g;
    nextColor.b = (nextColor.b > 255) ? 255 : nextColor.b;

    return nextColor;
}


sf::Vector2f ProtoPaint::ToolSpray::getRandomPositionInRadius(const sf::Vector2f& center, float radius) {
    // Random number generation setup
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_real_distribution<float> angleDist(0, 2 * M_PI); // Random angle
    std::uniform_real_distribution<float> radiusDist(0, radius); // Random radius

    // Generate random angle and radius
    float angle = angleDist(gen);
    float r = radiusDist(gen);

    // Convert polar coordinates to cartesian coordinates
    float x = center.x + r * cos(angle);
    float y = center.y + r * sin(angle);

    return sf::Vector2f(x, y);
}