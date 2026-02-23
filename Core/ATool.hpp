/*
** ProtoPaint
** File description:
** Core
*/

#pragma once

#ifndef ATOOL_H_
    #define ATOOL_H_

    #include "../includes/Headers.hpp"
    #include "../Interfaces/IGUIWindow.hpp"
    #include "../Interfaces/ITool.hpp"

    namespace ProtoPaint
    {
        class ATool : public ProtoPaint::ITool
        {
            public:
                ATool();
                ~ATool();
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);
                void setValue(std::pair<std::string, int> value);
                void drawPreview(std::shared_ptr<Graphic::Window> win);
                void drawPreviewInCurrentCanvas(std::shared_ptr<Graphic::Window> win);
                void displayGUI();

            protected:
                std::unordered_map<std::string, int> _values;
                std::unique_ptr<GUI::IGUIWindow> _gui;

                const sf::Color& getMainColor() { return GlobalData.getMainColor(); }
                const sf::Color& getSecondColor() { return GlobalData.getSecondColor(); }
                bool _used = false;

        };
    }

#endif