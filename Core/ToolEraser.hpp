/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** OOP
*/

#ifndef TOOLERASER_H_
    #define TOOLERASER_H_

    #include "ATool.hpp"
    #include "../Interfaces/IBrush.hpp"

    namespace EpiGimp
    {
        class ToolEraser: public EpiGimp::ATool
        {
            public:
                ToolEraser();
                ~ToolEraser() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);
                void drawPreview(std::shared_ptr<Graphic::Window> win);

            private:
                std::vector<std::unique_ptr<EpiGimp::IBrush>> _brushes;
                bool _used = false;

                void drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end);
        };
    }

#endif