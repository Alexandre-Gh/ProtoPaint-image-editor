/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** OOP
*/

#ifndef TOOLRECT_H_
    #define TOOLRECT_H_

    #include "ATool.hpp"
    #include "../Interfaces/IBrush.hpp"

    namespace EpiGimp
    {
        class ToolRect: public EpiGimp::ATool
        {
            public:
                ToolRect();
                ~ToolRect() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);
                void drawPreviewInCurrentCanvas(std::shared_ptr<Graphic::Window> win);

            private:
                sf::RectangleShape _shape;
                sf::Vector2f _firstPos;
                bool _used;
                bool _isInCanvas;
                bool _isFirstInCanvas;
        };
    }

#endif