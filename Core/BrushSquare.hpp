/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef BRUSHSQUARE_H_
    #define BRUSHSQUARE_H_

    #include "ABrush.hpp"

    namespace EpiGimp
    {
        class BrushSquare : public EpiGimp::ABrush
        {
            public:
                BrushSquare();
                ~BrushSquare();

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