/*
** EPITECH PROJECT, 2024
** EpiGimp
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
                const sf::RenderTexture &getRenderTexture();

                void setPixel(sf::Vector2f pos, sf::Color color);
                void setFromFile(std::string filepath);
                void addFromFile(std::string filepath);
                void saveToFile(std::string filepath);
                const sf::Color &getPixel(sf::Vector2f pos);
                void addDraw(sf::Drawable &drawable);
                void setDraw(sf::Drawable &drawable);

                void addSprite(const sf::Sprite &spr);

                void fill(sf::Vector2f pos, sf::Color color);
                void flip(bool vertical);
                void rotate(float angle);
                void reset(int w, int h);

                void drawCheckeredBackground();

                void setPosition(int x, int y);
                const sf::Vector2f &getPosition();
                sf::Vector2f getRelatedPosition(sf::Vector2f pos);
                void setSize(unsigned int x, unsigned int y, bool content = true);
                void setSize(sf::Vector2f size, bool content = true);
                const sf::Vector2f &getSize();
                bool isInZone(sf::Vector2f pos);

                void invert();
                void changeLighting(float f);
                void changeContrast(float f);
                void castShadows(float strength, float orientationX, float orientationY);
                void castLightAtPoint(float strength, unsigned int lightX, unsigned int lightY);

                void clear();

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