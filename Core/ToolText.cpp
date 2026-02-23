/*
** ProtoPaint
** File description:
** Core
*/

#include "../Gui/TextWin.hpp"
#include "ToolText.hpp"

ProtoPaint::ToolText::ToolText()
{
    this->_gui = std::make_unique<GUI::TextWin>();

    this->_previewZone = std::make_shared<Graphic::DrawZone>(GlobalData.getCanvasSize().x, GlobalData.getCanvasSize().y);

    std::vector<std::string> _fontFiles = GlobalData.getFontFilepaths();
    for (const auto& path : _fontFiles) {
        sf::Font newFont;
        if (!newFont.loadFromFile(path)) {
            continue;
        }
        this->_fonts.push_back(newFont);
    }

    this->_values["font"] = 0;
    this->_values["size"] = 16;
    this->_values["style"] = 0;
    this->_used = false;

    this->_textLine.setOutlineColor(sf::Color::Black);
    this->_textLine.setOutlineThickness(1);
    this->_textLine.setFillColor(sf::Color::Black);
    this->_textLine.setOrigin(0, 0);

    this->_textZone.setOutlineColor(sf::Color::Black);
    this->_textZone.setOutlineThickness(1);
    this->_textZone.setFillColor(sf::Color::Transparent);
    this->_textZone.setOrigin(0, 0);

    this->_styles.push_back(sf::Text::Style::Regular);
    this->_styles.push_back(sf::Text::Style::Bold);
    this->_styles.push_back(sf::Text::Style::Italic);
    this->_styles.push_back(sf::Text::Style::Underlined);
    this->_styles.push_back(sf::Text::Style::StrikeThrough);
}

void ProtoPaint::ToolText::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    sf::Vector2f mousePos = win->getMousePosition();
    if (win->isLeftMouseJustPressed() && this->_used) {
        zone->addDraw(this->_text);
        if (!this->_textString.empty()) {
            GlobalData.setAddState(true);
        }
        this->_textString.clear();
        this->_text.setString("");
        this->_used = false;
        return;
    }
    if (win->isLeftMouseJustPressed() && zone->isInZone(mousePos)) {
        this->_textPosition = zone->getRelatedPosition(mousePos);
        this->_textString.clear();
        this->_text.setString("");
        this->_used = true;
    }
    if (!this->_used) return;

    this->_text.setFont(this->_fonts[this->_values["font"]]);
    this->_textString += win->getEnteredText();
    if (win->isKeyJustPressed(sf::Keyboard::BackSpace)) {
        this->_clock.restart();
        if (this->_textString.length() != 0) {
            this->_textString.pop_back();
        }
    }
    if (this->_clock.getElapsedTime().asSeconds() > 0.4f && win->isKeyPressed(sf::Keyboard::BackSpace))
    {
        if (this->_textString.length() != 0 && this->_deleteClock.getElapsedTime().asMilliseconds() > 50) {
            this->_deleteClock.restart();
            this->_textString.pop_back();
        }
    }
    if (win->isKeyJustPressed(sf::Keyboard::Enter)) {
        this->_textString += "\n";
    }
    this->_text.setString(this->_textString);
    this->_text.setPosition(this->_textPosition);
    this->_text.setCharacterSize(this->_values["size"]);
    this->_text.setFillColor(GlobalData.getMainColor());

}

void ProtoPaint::ToolText::drawPreviewInCurrentCanvas(std::shared_ptr<Graphic::Window> win)
{
    if (this->_used) {
        this->_previewZone->setSize(GlobalData.getCanvasSize().x, GlobalData.getCanvasSize().y);
        this->_previewZone->clear();
        sf::Vector2f size = {1, (float)this->_values["size"] / 2};
        this->_textLine.setSize(size);

        std::istringstream stream(this->_textString);
        std::string line;
        std::string lastLine;

        while (std::getline(stream, line)) {
            lastLine = line;
        }
        lastLine = line;
        this->_textZone.setPosition(this->_textPosition.x - 10, this->_textPosition.y - 10);
        this->_textZone.setSize({this->_text.getGlobalBounds().width + 20, this->_text.getGlobalBounds().height + 20});
        float textHeight = this->_text.getGlobalBounds().height;
        this->_text.setString(lastLine);
        float textWidth = this->_text.getGlobalBounds().width;
        if (lastLine.empty()) {
            this->_text.setString("e");
            // textHeight += this->_text.getGlobalBounds().height;
        }
        if (this->_textZone.getSize().y < this->_textLine.getSize().y + 20) {
            this->_textZone.setSize({this->_textZone.getSize().x, this->_textLine.getSize().y + 20});
        }

        this->_textLine.setPosition(this->_textPosition.x + textWidth, this->_textPosition.y + textHeight);
        this->_text.setFont(this->_fonts[this->_values["font"]]);
        this->_text.setString(this->_textString);
        this->_text.setStyle(this->_styles[this->_values["style"]]);
        this->_text.setCharacterSize(this->_values["size"]);
        this->_previewZone->addDraw(this->_textZone);
        this->_previewZone->addDraw(this->_textLine);
        this->_previewZone->addDraw(this->_text);
        win->drawSprite(this->_previewZone->getSprite());
    }
}

void ProtoPaint::ToolText::drawPreview(std::shared_ptr<Graphic::Window> win)
{
    if (!this->_used) {
        sf::Vector2f size = {1, (float)this->_values["size"] / 2};
        this->_textLine.setSize(size);
        this->_textLine.setPosition(win->getMousePosition());
        win->drawShape(this->_textLine);
    }
}
