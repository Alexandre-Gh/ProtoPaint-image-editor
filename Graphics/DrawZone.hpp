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
                DrawZone(const DrawZone& other);
                ~DrawZone();

                const sf::Sprite &getSprite();

                void setPixel(sf::Vector2f pos, sf::Color color);
                void setFromFile(std::string filepath);
                void saveToFile(std::string filepath);
                const sf::Color &getPixel(sf::Vector2f pos);
                void addDraw(sf::Drawable &drawable);
                void setDraw(sf::Drawable &drawable);

                void addSprite(const sf::Sprite &spr);

                void fill(sf::Vector2f pos, sf::Color color);

                void drawCheckeredBackground();

                void setPosition(int x, int y);
                const sf::Vector2f &getPosition();
                const sf::Vector2f &getMouseRelatedPosition(sf::Vector2f pos);
                void setSize(unsigned int x, unsigned int y);
                const sf::Vector2f &getSize();

                std::shared_ptr<Graphic::DrawZone> clone() const {
                    return std::make_shared<Graphic::DrawZone>(*this);
                }

            private:
                sf::Vector2f _size;
                sf::Sprite _displayer;
                sf::RenderTexture _zone;

        };
    }

#endif