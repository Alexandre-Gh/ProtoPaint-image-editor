/*
** ProtoPaint
** File description:
** OOP
*/

#ifndef TOOL_PENCIL_H_
    #define TOOL_PENCIL_H_

    #include "ATool.hpp"
    #include "../Interfaces/IBrush.hpp"

    namespace ProtoPaint
    {
        class ToolPencil: public ProtoPaint::ATool
        {
            public:
                ToolPencil();
                ~ToolPencil() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);

            private:
                void drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end);

                bool _used;
        };
    }

#endif