/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "Window.hpp"

Graphic::Window::Window(std::string name, unsigned int w, unsigned int h)
{
    this->_window.create(sf::VideoMode(w, h), name.c_str(), sf::Style::Default);
    this->_window.setFramerateLimit(1000);
    this->_camera = std::make_shared<Graphic::Camera>(0, 0, w, h);
    this->_window.setView(this->_camera->getCoreCamera());
    this->_zoomMult = 1;

    sf::Image cursorImage;
    cursorImage.loadFromFile("assets/cursor.png");

    this->_mouseDraw.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(16, 16));
}

Graphic::Window::~Window()
{

}

void Graphic::Window::resetRender()
{
    this->_window.clear(sf::Color(50, 50, 50));
    this->_mouseJustPressed = false;
    if (isMouseInUI()) {
        this->_window.setMouseCursorVisible(true);
        this->_window.setMouseCursor(sf::Cursor());
    } else {
        this->_window.setMouseCursor(this->_mouseDraw);

    }
    this->_mouseTranslation = sf::Vector2f{0, 0};
    this->_lastKeyPressed = this->_keyPressed;
    this->_mouseJustReleased = false;
    this->_mouseWheel = 0;
    while (this->_window.pollEvent(this->_event))
    {
        ImGui::SFML::ProcessEvent(this->_window, this->_event);
        switch (this->_event.type) {
            case sf::Event::Resized: checkResize(); break;
            case sf::Event::Closed: checkClose(); break;
            case sf::Event::MouseWheelScrolled: checkZoom(); break;
            case sf::Event::MouseMoved: checkMouse(); break;
            case sf::Event::MouseButtonReleased:
                this->_mouseJustReleased = true;
                break;
            case sf::Event::MouseButtonPressed:
                if (this->_mouseInUI = ImGui::GetIO().WantCaptureMouse) {
                    this->_mouseJustPressed = false;
                    this->_mouseTranslation = {0, 0};
                    break;
                }
                this->_mouseJustPressed = (this->_event.mouseButton.button == sf::Mouse::Left);
                break;

            case sf::Event::KeyPressed:
                this->_keyPressed[this->_event.key.code] = true;
                break;
            case sf::Event::KeyReleased:
                this->_keyPressed[this->_event.key.code] = false;
                break;
        }
    }
}

void Graphic::Window::drawSprite(const sf::Sprite &sprite)
{
    this->_window.draw(sprite);
}

void Graphic::Window::drawShape(const sf::Shape &shape)
{
    this->_window.draw(shape);
}

void Graphic::Window::displayRender()
{
    this->_window.setView(this->_camera->getCoreCamera());
    this->_window.display();
}

bool Graphic::Window::isOpen()
{
    return this->_window.isOpen();
}

void Graphic::Window::checkResize()
{
    this->_camera->setSize(this->_window.getSize().x, this->_window.getSize().y);
}

void Graphic::Window::checkClose()
{
    switch(this->_event.type) {
        case sf::Event::Closed:
            this->_window.close();
            break;
    }
}

void Graphic::Window::checkZoom()
{
    if (this->_event.mouseWheelScroll.delta > 0) {
        this->_mouseWheel = 1;
    } else {
        this->_mouseWheel = -1;
    }
}

void Graphic::Window::checkMouse()
{
    if (this->_mouseInUI = ImGui::GetIO().WantCaptureMouse) {
        this->_mouseJustPressed = false;
        this->_mouseTranslation = {0, 0};
        return;
    }
    this->_mousePosition = this->_window.mapPixelToCoords(sf::Mouse::getPosition(this->_window));
    this->_mouseTranslation = this->_mousePosition - this->_previousMousePosition;
    this->_previousMousePosition = this->_mousePosition;
}

int Graphic::Window::getMouseWheel()
{
    return this->_mouseWheel;
}

bool Graphic::Window::isLeftMousePressed()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool Graphic::Window::isLeftMouseJustPressed()
{
    return this->_mouseJustPressed;
}

bool Graphic::Window::isLeftMouseJustReleased()
{
    return this->_mouseJustReleased;
}

bool Graphic::Window::isRightMousePressed()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Right);
}

bool Graphic::Window::isMouseInUI()
{
    return this->_mouseInUI;
}

const sf::Vector2f &Graphic::Window::getMousePosition()
{
    return this->_mousePosition;
}

const sf::Vector2f &Graphic::Window::getMouseTranslation()
{
    return this->_mouseTranslation;
}

const std::shared_ptr<Graphic::Camera> &Graphic::Window::getCamera()
{
    return this->_camera;
}

sf::RenderWindow &Graphic::Window::getCoreWindow()
{
    return this->_window;
}

const sf::Event &Graphic::Window::getCoreEvent()
{
    return this->_event;
}

bool Graphic::Window::isKeyPressed(sf::Keyboard::Key key)
{
    return this->_keyPressed[key];
}

bool Graphic::Window::isKeyJustPressed(sf::Keyboard::Key key)
{
    return this->_keyPressed[key] == true && this->_lastKeyPressed[key] == false;
}

void Graphic::Window::zoomCamera()
{
    if (this->isMouseInUI() || this->_mouseWheel == 0) {
        return;
    }
    this->_camera->zoom(1 + (0.1f * -this->_mouseWheel));
}

