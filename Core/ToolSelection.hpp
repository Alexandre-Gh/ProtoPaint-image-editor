/*
** ProtoPaint
** File description:
** OOP
*/

#ifndef TOOL_SELECTION_H_
    #define TOOL_SELECTION_H_

    #include "ATool.hpp"

    namespace ProtoPaint
    {
        class ToolSelection: public ProtoPaint::ATool
        {
            public:
                ToolSelection();
                ~ToolSelection() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);
                void drawPreviewInCurrentCanvas(std::shared_ptr<Graphic::Window> win);

            private:
                sf::RectangleShape _shape;
                Graphic::DrawZone _selectionContent;
                sf::Vector2f _firstPos;
                bool _used;
                bool _selecting;
                bool _isInCanvas;
                bool _isFirstInCanvas;
                bool _changingSize = false;
                Graphic::DrawZone _previewZone;
        };
    }

#endif