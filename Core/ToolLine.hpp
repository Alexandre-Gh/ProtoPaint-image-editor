/*
** ProtoPaint
** File description:
** OOP
*/

#ifndef TOOL_LINE_H_
    #define TOOL_LINE_H_

    #include "ATool.hpp"
    #include "../Interfaces/IBrush.hpp"

    namespace ProtoPaint
    {
        class ToolLine: public ProtoPaint::ATool
        {
            public:
                ToolLine();
                ~ToolLine() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);
                void drawPreviewInCurrentCanvas(std::shared_ptr<Graphic::Window> win);

            private:
                void drawBorders(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f pos1, sf::Vector2f pos2);
                sf::RectangleShape _shape;
                sf::CircleShape _border;
                sf::Vector2f _firstPos;
                bool _used;
                bool _isInCanvas;
                bool _isFirstInCanvas;
                std::shared_ptr<Graphic::DrawZone> _previewZone;
        };
    }

#endif