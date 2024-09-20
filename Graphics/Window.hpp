/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef MYWINDOW_H_
    #define MYWINDOW_H_

    #include "../includes/Headers.hpp"
    #include "Camera.hpp"

    namespace Graphic
    {
        class Window
        {
            public:
                Window(std::string name, unsigned int x, unsigned int y);
                ~Window();
                void resetRender();
                void displayRender();
                bool isOpen();
                void checkResize();
                void checkClose();
                bool isLeftMousePressed();
                const sf::Vector2f &getMousePosition();
                const Graphic::Camera &getCamera();


            private:
                sf::RenderWindow _window;
                sf::Event _event;
                Graphic::Camera _camera;

        };
    }

#endif