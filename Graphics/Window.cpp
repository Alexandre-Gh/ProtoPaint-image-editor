/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "Window.hpp"

Graphic::Window::Window(std::string name, unsigned int w, unsigned int h) :
    _camera(0, 0, w, h)
{
    this->_window.create(sf::VideoMode(w, h), name.c_str(), sf::Style::Default);
    sf::Vector2u size;
    this->_window.setTitle(name);
    this->_window.setSize(sf::Vector2u(w, h));
    this->_window.setVerticalSyncEnabled(false);
    this->_window.setFramerateLimit(60);
}

Graphic::Window::~Window()
{

}

void Graphic::Window::resetRender()
{
    this->_window.pollEvent(this->_event);
    this->_window.clear(sf::Color(50, 50, 50));
}

void Graphic::Window::displayRender()
{
    this->_window.setView(this->_camera.getCoreCamera());
    this->_window.display();
}

bool Graphic::Window::isOpen()
{
    return this->_window.isOpen();
}

void Graphic::Window::checkResize()
{
    if (this->_event.type == sf::Event::Resized) {
        this->_camera.setSize(this->_window.getSize().x, this->_window.getSize().y);
        this->_camera.setPosition(this->_window.getSize().x / 2, this->_window.getSize().y / 2);
    }
}

void Graphic::Window::checkClose()
{
    if (this->_event.type == sf::Event::Closed) {
        this->_window.close();
    }
}

bool Graphic::Window::isLeftMousePressed()
{
    return this->_event.type == sf::Event::MouseLeft;
}

const sf::Vector2f &Graphic::Window::getMousePosition()
{
    return this->_window.mapPixelToCoords({this->_event.mouseButton.x, this->_event.mouseButton.y});
}

const Graphic::Camera &Graphic::Window::getCamera()
{
    return this->_camera;
}