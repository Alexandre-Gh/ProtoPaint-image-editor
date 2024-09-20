/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef MYCAMERA_H_
    #define MYCAMERA_H_

    #include "../includes/Headers.hpp"

    namespace Graphic
    {
        class Camera
        {
            public:
                Camera(int x = 0, int y = 0, unsigned int w = 800, unsigned int h = 600);
                ~Camera();

                void setPosition(int x, int y);
                const sf::Vector2f &getPosition();
                void setSize(int x, int y);
                const sf::Vector2f &getSize();

                const sf::View &getCoreCamera();

            private:
                sf::View _camera;

        };
    }

#endif