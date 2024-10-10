/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef BRUSHCIRCLE_H_
    #define BRUSHCIRCLE_H_

    #include "ABrush.hpp"

    namespace EpiGimp
    {
        class BrushCircle : public EpiGimp::ABrush
        {
            public:
                BrushCircle();
                ~BrushCircle();

                void drawPreview(std::shared_ptr<Graphic::Window> win, sf::Vector2f pos);
                void draw(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f pos, bool add);

                void setSize(float size);
                const float &getSize();

                void setColor(sf::Color color);
                const sf::Color &getColor();

            protected:
                sf::CircleShape _brush;
                sf::CircleShape _previewBrush;

        };
    }

#endif