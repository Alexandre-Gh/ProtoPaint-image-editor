/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** OOP
*/

#ifndef TOOLERASER_H_
    #define TOOLERASER_H_

    #include "ATool.hpp"

    namespace EpiGimp
    {
        class ToolEraser: public EpiGimp::ATool
        {
            public:
                ToolEraser();
                ~ToolEraser() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);

            private:
                sf::CircleShape _brush;
        };
    }

#endif