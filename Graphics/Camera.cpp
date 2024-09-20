/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "Camera.hpp"

Graphic::Camera::Camera(int x, int y, unsigned int w, unsigned int h)
{
    this->_camera.setCenter(x, y);
    this->_camera.setSize(w, h);
}

Graphic::Camera::~Camera()
{
    
}

void Graphic::Camera::setPosition(int x, int y)
{
    this->_camera.setCenter(x, y);
}

const sf::Vector2f &Graphic::Camera::getPosition()
{
    return this->_camera.getCenter();
}

void Graphic::Camera::setSize(int x, int y)
{
    this->_camera.setSize(x, y);
}

const sf::Vector2f &Graphic::Camera::getSize()
{
    return this->_camera.getSize();
}

const sf::View &Graphic::Camera::getCoreCamera()
{
    return this->_camera;
}
