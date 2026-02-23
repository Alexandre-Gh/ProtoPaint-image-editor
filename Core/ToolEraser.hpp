/*
** ProtoPaint
** File description:
** OOP
*/

#ifndef TOOL_ERASER_H_
    #define TOOL_ERASER_H_

    #include "ATool.hpp"
    #include "../Interfaces/IBrush.hpp"

    namespace ProtoPaint
    {
        class ToolEraser: public ProtoPaint::ATool
        {
            public:
                ToolEraser();
                ~ToolEraser() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);
                void drawPreview(std::shared_ptr<Graphic::Window> win);

            private:
                std::vector<std::unique_ptr<ProtoPaint::IBrush>> _brushes;
                bool _used = false;

                void drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end);
        };
    }

#endif