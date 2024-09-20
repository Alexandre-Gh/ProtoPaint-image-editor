/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "Core.hpp"

EpiGimp::Core::Core() :
    _window("EpiGimp", 800, 600)
{

}

EpiGimp::Core::~Core()
{

}

void EpiGimp::Core::loop()
{
    while (this->_window.isOpen()) {
        this->_window.resetRender();

        this->_window.checkResize();
        this->_window.checkClose();

        this->_window.displayRender();
    }
    std::cout << "TEST";
}