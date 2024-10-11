/*
** EPITECH PROJECT, 2024
** EpiGimp
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
                void setPosition(sf::Vector2f pos);
                const sf::Vector2f &getPosition();
                void setSize(int w, int h);
                void setSize(sf::Vector2f size);
                const sf::Vector2f &getSize();
                void moveCamera(float x, float y);
                void moveCamera(sf::Vector2f translation);

                void zoom(float zoomMult);
                void resetZoom();

                const sf::View &getCoreCamera();

            private:
                sf::View _camera;
                int _w;
                int _h;

        };
    }

#endif