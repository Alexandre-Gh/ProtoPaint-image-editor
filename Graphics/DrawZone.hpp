/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef DRAWZONE_H_
    #define DRAWZONE_H_

    #include "../includes/Headers.hpp"

    namespace Graphic
    {
        class DrawZone
        {
            public:
                DrawZone(unsigned int w, unsigned int h);
                ~DrawZone();

                void setPixel(sf::Vector2f pos, sf::Color color);
                const sf::Color &getPixel(sf::Vector2u pos);

                void setPosition(int x, int y);
                const sf::Vector2f &getPosition();
                void setSize(unsigned int x, unsigned int y);

            private:
                sf::Sprite _displayer;
                sf::RenderTexture _zone;

        };
    }

#endif