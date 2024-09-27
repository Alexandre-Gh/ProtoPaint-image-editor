/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** OOP
*/

#ifndef TOOLBRUSH_H_
    #define TOOLBRUSH_H_

    #include "ATool.hpp"

    namespace EpiGimp
    {
        class ToolBrush: public EpiGimp::ATool
        {
            public:
                ToolBrush();
                ~ToolBrush() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);

            private:
                sf::CircleShape _brush;
        };
    }

#endif