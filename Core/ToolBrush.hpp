/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** OOP
*/

#ifndef TOOLBRUSH_H_
    #define TOOLBRUSH_H_

    #include "ATool.hpp"
    #include "../Interfaces/IBrush.hpp"

    namespace EpiGimp
    {
        class ToolBrush: public EpiGimp::ATool
        {
            public:
                ToolBrush();
                ~ToolBrush() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);
                void drawPreview(std::shared_ptr<Graphic::Window> win);

            private:
                std::vector<std::unique_ptr<EpiGimp::IBrush>> _brushes;
                sf::Color _rainbowPrevColor;

                sf::Color getRainbowColor(const sf::Color& currentColor);
                void drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end);
        };
    }

#endif