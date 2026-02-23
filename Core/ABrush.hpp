/*
** ProtoPaint
** File description:
** Core
*/

#pragma once

#ifndef ABRUSH_H_
    #define ABRUSH_H_

    #include "../includes/Headers.hpp"
    #include "../Interfaces/IBrush.hpp"

    namespace ProtoPaint
    {
        class ABrush : public ProtoPaint::IBrush
        {
            public:
                ABrush();
                ~ABrush();

                void drawPreview(std::shared_ptr<Graphic::Window> win, sf::Vector2f pos);
                void draw(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f pos, bool add);

                void setSize(float size);
                const float &getSize();

                void setColor(sf::Color color);
                const sf::Color &getColor();

            protected:
                float _size;
                sf::Color _color;

        };
    }

#endif