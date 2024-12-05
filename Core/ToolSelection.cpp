/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "../Gui/RectWin.hpp"
#include "ToolSelection.hpp"

EpiGimp::ToolSelection::ToolSelection() :
    _previewZone(GlobalData.getCanvasSize().x, GlobalData.getCanvasSize().y),
    _selectionContent(1, 1)
{
    this->_used = false;
    this->_selecting = false;
    this->_shape.setOutlineColor(sf::Color::Black);
    this->_shape.setOutlineThickness(1);
    this->_shape.setFillColor(sf::Color::Transparent);
    this->_shape.setOrigin(0, 0);
}

void EpiGimp::ToolSelection::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    this->_isInCanvas = zone->isInZone(win->getMousePosition());
    this->_isFirstInCanvas = zone->isInZone(this->_firstPos);

    if (this->_selecting && this->_used) {
        if (this->_changingSize && (win->isLeftMouseJustReleased() || !win->isKeyPressed(sf::Keyboard::LControl)))
        {
            _selectionContent.setSize(_shape.getSize(), true);
            this->_changingSize = false;
        }
        if (win->isKeyJustPressed(sf::Keyboard::LShift)) {
            _selectionContent.rotate(90);
            return;
        }
        if (win->isLeftMousePressed()) {
            if (win->isKeyPressed(sf::Keyboard::LControl)) {
                this->_changingSize = true;
                _shape.setSize(_shape.getSize() + win->getMouseTranslation());
                return;
            }
            if (_selectionContent.isInZone(win->getMousePosition())) {
                std::cout << "Moving\n";
                sf::Vector2f positionSelection = _selectionContent.getPosition();
                _selectionContent.setPosition(positionSelection.x + win->getMouseTranslation().x, positionSelection.y + win->getMouseTranslation().y);
                _shape.setPosition(_selectionContent.getPosition());
            } else {
                std::cout << "Set\n";
                this->_used = false;
                this->_selecting = false;
                sf::Sprite newSprite = _selectionContent.getSprite();
                zone->addDraw(newSprite);
                _selectionContent.reset(1, 1);
                _shape.setRotation(0);
                GlobalData.setAddState(true);
                return;
            }
        }
        return;
    }
    if (this->_isFirstInCanvas && !this->_selecting && win->isLeftMouseJustReleased() && this->_used) {
        std::cout << "Zone selected\n";
        sf::RectangleShape bgColorShape = this->_shape;
        bgColorShape.setOutlineThickness(0);

        sf::Texture text(*zone->getSprite().getTexture());
        sf::IntRect rect;
        rect.left = bgColorShape.getPosition().x;
        rect.top = bgColorShape.getPosition().y;
        rect.width = bgColorShape.getSize().x;
        rect.height = bgColorShape.getSize().y;
        std::cout << rect.left << " | " << rect.top << " | " << rect.width << " | " << rect.height << std::endl;
        sf::Sprite s(text, rect);
        sf::Vector2f selectSize(bgColorShape.getSize().x, bgColorShape.getSize().y);
        _selectionContent.setSize(selectSize);
        _selectionContent.setPosition(bgColorShape.getPosition().x, bgColorShape.getPosition().y);
        _selectionContent.setDraw(s);
        zone->setDraw(bgColorShape);
        this->_selecting = true;
    }

    if (!win->isLeftMousePressed() || this->_selecting) {
        return;
    }
    if(this->_isInCanvas && win->isLeftMouseJustPressed() && !this->_used) {
        std::cout << "Start\n";
        this->_used = true;
    }
    if (this->_used && !this->_selecting) {
        if (win->isLeftMouseJustPressed()) {
            this->_firstPos = win->getMousePosition();
            this->_shape.setPosition(this->_firstPos);
        }

        sf::Vector2f pos = win->getMousePosition();
        pos = zone->getRelatedPosition(pos);
        sf::Vector2f size = pos - this->_firstPos;
        this->_shape.setSize(size);
    }
}

void EpiGimp::ToolSelection::drawPreviewInCurrentCanvas(std::shared_ptr<Graphic::Window> win)
{
    if (this->_used) {
        this->_previewZone.setSize(GlobalData.getCanvasSize().x, GlobalData.getCanvasSize().y);
        this->_previewZone.clear();
        _previewZone.addDraw(this->_shape);
        if (_selecting) {
            sf::Sprite s = _selectionContent.getSprite();
            _previewZone.addDraw(s);
        }
        win->drawSprite(_previewZone.getSprite());
    }
}
