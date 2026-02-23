/*
** ProtoPaint
** File description:
** Core
*/

#pragma once

#ifndef BRUSHCIRCLE_H_
    #define BRUSHCIRCLE_H_

    #include "ABrush.hpp"

    namespace ProtoPaint
    {
        class BrushCircle : public ProtoPaint::ABrush
        {
            public:
                BrushCircle();
                ~BrushCircle();

                void drawPreview(std::shared_ptr<Graphic::Window> win, sf::Vector2f pos);
                void draw(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f pos, bool add);

                void setSize(float size);

                void setColor(sf::Color color);

            protected:
                sf::CircleShape _brush;
                sf::CircleShape _previewBrush;

        };
    }

#endif