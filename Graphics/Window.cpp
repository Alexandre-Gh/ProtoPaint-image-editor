/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "Window.hpp"

Graphic::Window::Window(std::string name, unsigned int w, unsigned int h)
{
    this->_window.create(sf::VideoMode(w, h), name.c_str(), sf::Style::Default);
    this->_window.setFramerateLimit(144);
    this->_camera = std::make_shared<Graphic::Camera>(0, 0, w, h);
    this->_window.setView(this->_camera->getCoreCamera());
}

Graphic::Window::~Window()
{

}

void Graphic::Window::resetRender()
{
    this->_window.clear(sf::Color(50, 50, 50));
    while (this->_window.pollEvent(this->_event))
    {
        std::cout << this->_event.type << std::endl;
        this->checkClose();
        this->checkResize();
        this->checkMouse();
    }
}

void Graphic::Window::drawSprite(const sf::Sprite &sprite)
{
    this->_window.draw(sprite);
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
    if (this->_event.type == sf::Event::Resized) {
        this->_camera->setSize(this->_window.getSize().x, this->_window.getSize().y);
    }
}

void Graphic::Window::checkClose()
{
    if (this->_event.type == sf::Event::Closed) {
        this->_window.close();
    }
}

void Graphic::Window::checkMouse()
{
    this->_mousePosition = this->_window.mapPixelToCoords(sf::Mouse::getPosition(), this->_camera->getCoreCamera());
    if (this->_event.type == sf::Event::MouseMoved) {
        this->_mouseTranslation = this->_mousePosition - this->_previousMousePosition;
    } else {
        this->_mouseTranslation = {0, 0};
    }
    this->_previousMousePosition = this->_mousePosition;
}

bool Graphic::Window::isLeftMousePressed()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool Graphic::Window::isRightMousePressed()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Right);
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