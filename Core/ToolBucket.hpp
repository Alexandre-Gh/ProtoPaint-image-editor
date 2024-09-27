/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** OOP
*/

#ifndef TOOLBUCKET_H_
    #define TOOLBUCKET_H_

    #include "ATool.hpp"

    namespace EpiGimp
    {
        class ToolBucket: public EpiGimp::ATool
        {
            public:
                ToolBucket();
                ~ToolBucket() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);

            private:
                sf::CircleShape _brush;
        };
    }

#endif