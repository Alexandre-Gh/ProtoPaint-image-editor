/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** OOP
*/

#ifndef TOOLPENCIL_H_
    #define TOOLPENCIL_H_

    #include "ATool.hpp"
    #include "../Interfaces/IBrush.hpp"

    namespace EpiGimp
    {
        class ToolPencil: public EpiGimp::ATool
        {
            public:
                ToolPencil();
                ~ToolPencil() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);

            private:
                void drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end);

                bool _used;
        };
    }

#endif