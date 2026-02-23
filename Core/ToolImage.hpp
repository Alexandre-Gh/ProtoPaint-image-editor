/*
** ProtoPaint
** File description:
** OOP
*/

#ifndef TOOL_Image_H_
    #define TOOL_Image_H_

    #include "ATool.hpp"
    #include "../Interfaces/IBrush.hpp"

    namespace ProtoPaint
    {
        class ToolImage: public ProtoPaint::ATool
        {
            public:
                ToolImage();
                ~ToolImage() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);
                void drawPreview(std::shared_ptr<Graphic::Window> win);

            private:
                sf::Texture _texture;
                sf::Sprite _sprite;
                std::string _currentFilepath = "";
                bool _used = false;
                bool _imageEmpty = true;

                void drawLine(std::shared_ptr<Graphic::DrawZone> zone, sf::Vector2f start, sf::Vector2f end);
        };
    }

#endif