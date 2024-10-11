/*
** EPITECH PROJECT, 2024
** EpiGimp
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
                void drawSprite(const sf::Sprite &sprite);
                void drawShape(const sf::Shape &shape);
                void displayRender();
                bool isOpen();
                void checkResize();
                void checkClose();
                void checkZoom();
                void checkMouse();
                bool isLeftMousePressed();
                bool isLeftMouseJustReleased();
                bool isLeftMouseJustPressed();
                bool isRightMousePressed();
                int getMouseWheel();
                bool isKeyPressed(sf::Keyboard::Key key);
                bool isKeyJustPressed(sf::Keyboard::Key key);
                bool isMouseInUI();
                void zoomCamera();
                const sf::Vector2f &getMousePosition();
                const sf::Vector2f &getMouseTranslation();
                const std::shared_ptr<Graphic::Camera> &getCamera();

                sf::RenderWindow &getCoreWindow();
                const sf::Event &getCoreEvent();

            private:
                sf::RenderWindow _window;
                sf::Event _event;
                std::shared_ptr<Graphic::Camera> _camera;
                float _zoomMult;
                sf::Vector2f _mousePosition;
                sf::Vector2f _previousMousePosition;
                sf::Vector2f _mouseTranslation;
                bool _mouseJustPressed;
                bool _mouseJustReleased;
                bool _mouseInUI;
                std::map<sf::Keyboard::Key,bool> _keyPressed;
                std::map<sf::Keyboard::Key,bool> _lastKeyPressed;
                int _mouseWheel;

        };
    }

#endif