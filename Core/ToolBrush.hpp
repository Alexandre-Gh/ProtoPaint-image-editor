/*
** ProtoPaint
** File description:
** OOP
*/

#ifndef TOOL_BRUSH_H_
    #define TOOL_BRUSH_H_

    #include "ATool.hpp"
    #include "../Interfaces/IBrush.hpp"

    namespace ProtoPaint
    {
        class ToolBrush: public ProtoPaint::ATool
        {
            public:
                ToolBrush();
                ~ToolBrush() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);
                void drawPreview(std::shared_ptr<Graphic::Window> win);

            private:
                std::vector<std::unique_ptr<ProtoPaint::IBrush>> _brushes;

                sf::Color getRainbowColor(const sf::Color& currentColor);
                void drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end);
        };
    }

#endif