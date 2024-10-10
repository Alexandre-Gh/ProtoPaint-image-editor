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
                void drawPreview(std::shared_ptr<Graphic::Window> win);
                void drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end, sf::Color color);

            private:
                sf::CircleShape _previewBrush;
                sf::CircleShape _brush;
                sf::Color _rainbowPrevColor;

                sf::Color getRainbowColor(const sf::Color& currentColor);
        };
    }

#endif