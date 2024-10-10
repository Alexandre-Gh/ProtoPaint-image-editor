/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef IBRUSH_H_
    #define IBRUSH_H_

    #include "../Graphics/DrawZone.hpp"
    #include "../Graphics/Window.hpp"

    namespace EpiGimp
    {
        class IBrush
        {
            public:
                virtual ~IBrush() = default;

                virtual void drawPreview(std::shared_ptr<Graphic::Window> win, sf::Vector2f pos) = 0;
                virtual void draw(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f pos, bool add) = 0;

                virtual void setSize(float size) = 0;
                virtual const float &getSize() = 0;

                virtual void setColor(sf::Color color) = 0;
                virtual const sf::Color &getColor() = 0;
        };
    }

#endif