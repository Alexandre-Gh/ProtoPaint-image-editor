/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef BRUSHLINE_H_
    #define BRUSHLINE_H_

    #include "ABrush.hpp"

    namespace EpiGimp
    {
        class BrushLine : public EpiGimp::ABrush
        {
            public:
                BrushLine(float angle);
                ~BrushLine();

                void drawPreview(std::shared_ptr<Graphic::Window> win, sf::Vector2f pos);
                void draw(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f pos, bool add);

                void setSize(float size);

                void setColor(sf::Color color);

            protected:
                sf::RectangleShape _brush;
                sf::RectangleShape _previewBrush;

        };
    }

#endif