/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** OOP
*/

#ifndef TOOL_SPRAY_H_
    #define TOOL_SPRAY_H_

    #include "ATool.hpp"
    #include "../Interfaces/IBrush.hpp"

    namespace EpiGimp
    {
        class ToolSpray: public EpiGimp::ATool
        {
            public:
                ToolSpray();
                ~ToolSpray() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);
                void drawPreview(std::shared_ptr<Graphic::Window> win);

            private:
                std::vector<std::unique_ptr<EpiGimp::IBrush>> _brushes;
                sf::Clock _clock;
                sf::Color _brushColor;

                sf::Color getRainbowColor(const sf::Color& currentColor);
                void drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end);
                sf::Vector2f getRandomPositionInRadius(const sf::Vector2f& center, float radius);
        };
    }

#endif