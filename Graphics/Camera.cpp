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
    this->_w = w;
    this->_h = h;

}

Graphic::Camera::~Camera()
{
    
}

void Graphic::Camera::setPosition(int x, int y)
{
    this->_camera.setCenter(x, y);
}

void Graphic::Camera::setPosition(sf::Vector2f pos)
{
    this->_camera.setCenter(pos);
}

const sf::Vector2f &Graphic::Camera::getPosition()
{
    return this->_camera.getCenter();
}

void Graphic::Camera::setSize(int w, int h)
{
    this->_w = w;
    this->_h = h;
    this->_camera.setSize(w, h);
}

void Graphic::Camera::setSize(sf::Vector2f size)
{
    this->_camera.setSize(size);
}

const sf::Vector2f &Graphic::Camera::getSize()
{
    return this->_camera.getSize();
}

const sf::View &Graphic::Camera::getCoreCamera()
{
    return this->_camera;
}

void Graphic::Camera::moveCamera(float x, float y)
{
    this->_camera.move(x, y);
}

void Graphic::Camera::moveCamera(sf::Vector2f translation)
{
    this->_camera.move(translation);
}

void Graphic::Camera::zoom(float zoomMult)
{
    this->_camera.zoom(zoomMult);
}

void Graphic::Camera::resetZoom()
{
    this->setSize(this->_w, this->_h);
}
