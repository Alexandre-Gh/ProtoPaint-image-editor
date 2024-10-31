/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "../Gui/TextWin.hpp"
#include "ToolText.hpp"

EpiGimp::ToolText::ToolText()
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

    this->_styles.push_back(sf::Text::Style::Regular);
    this->_styles.push_back(sf::Text::Style::Bold);
    this->_styles.push_back(sf::Text::Style::Italic);
    this->_styles.push_back(sf::Text::Style::Underlined);
    this->_styles.push_back(sf::Text::Style::StrikeThrough);
}

void EpiGimp::ToolText::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
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
        if (this->_textString.length() != 0) {
            this->_textString.pop_back();
        }
    }
    if (win->isKeyJustPressed(sf::Keyboard::Enter)) {
        this->_textString += "\n";
    }
    this->_text.setString(this->_textString);
    this->_text.setPosition(this->_textPosition);
    this->_text.setCharacterSize(this->_values["size"]);
    sf::Color col = GlobalData.getMainColor();
    this->_text.setColor(col);

}

void EpiGimp::ToolText::drawPreviewInCurrentCanvas(std::shared_ptr<Graphic::Window> win)
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
        float textHeight = this->_text.getGlobalBounds().height;
        this->_text.setString(lastLine);
        float textWidth = this->_text.getGlobalBounds().width;
        if (lastLine.empty()) {
            this->_text.setString("e");
            // textHeight += this->_text.getGlobalBounds().height;
        }

        this->_textLine.setPosition(this->_textPosition.x + textWidth, this->_textPosition.y + textHeight);
        this->_text.setString(this->_textString);
        this->_text.setStyle(this->_styles[this->_values["style"]]);
        this->_previewZone->addDraw(this->_textLine);
        this->_previewZone->addDraw(this->_text);
        win->drawSprite(this->_previewZone->getSprite());
    }
}

void EpiGimp::ToolText::drawPreview(std::shared_ptr<Graphic::Window> win)
{
    if (!this->_used) {
        sf::Vector2f size = {1, (float)this->_values["size"] / 2};
        this->_textLine.setSize(size);
        this->_textLine.setPosition(win->getMousePosition());
        win->drawShape(this->_textLine);
    }
}
