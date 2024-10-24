/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** OOP
*/

#ifndef TOOLCIRCLE_H_
    #define TOOLCIRCLE_H_

    #include "ATool.hpp"
    #include "../Interfaces/IBrush.hpp"

    namespace EpiGimp
    {
        class ToolCircle: public EpiGimp::ATool
        {
            public:
                ToolCircle();
                ~ToolCircle() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);
                void drawPreviewInCurrentCanvas(std::shared_ptr<Graphic::Window> win);

            private:
                sf::CircleShape _shape;
                sf::Vector2f _firstPos;
                bool _used;
                bool _isInCanvas;
                bool _isFirstInCanvas;
                Graphic::DrawZone _previewZone;
        };
    }

#endif