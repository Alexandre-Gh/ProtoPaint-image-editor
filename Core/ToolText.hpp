/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** OOP
*/

#ifndef TOOL_TEXT_H_
    #define TOOL_TEXT_H_

    #include "ATool.hpp"
    #include "../Interfaces/IBrush.hpp"

    namespace EpiGimp
    {
        class ToolText: public EpiGimp::ATool
        {
            public:
                ToolText();
                ~ToolText() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);
                void drawPreviewInCurrentCanvas(std::shared_ptr<Graphic::Window> win);
                void drawPreview(std::shared_ptr<Graphic::Window> win);

            private:
                bool _used;
                sf::RectangleShape _textLine;
                sf::RectangleShape _textZone;
                sf::Vector2f _textPosition;
                sf::Text _text;
                sf::Clock _clock;
                sf::Clock _deleteClock;
                std::string _textString;
                int _skipLines;
                std::shared_ptr<Graphic::DrawZone> _previewZone;

                std::vector<sf::Font> _fonts;
                std::vector<sf::Text::Style> _styles;
                int _currentToolIndex = 0;
        };
    }

#endif