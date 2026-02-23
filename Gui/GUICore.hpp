/*
** ProtoPaint
** File description:
** Core
*/

#pragma once

#ifndef GUICORE_H_
    #define GUICORE_H_

    #include "../includes/Headers.hpp"
    #include "../Graphics/Window.hpp"
    #include "../Interfaces/IGUIWindow.hpp"


    namespace GUI
    {
        class GUICore
        {
            public:
                GUICore(std::shared_ptr<Graphic::Window> win);
                ~GUICore();

                void update();
                void display();
                void startLoadFile();
                void startSaveFile();

                const std::string &getFilePath();
                const bool &getFDClosed();
                void resetFilePath();

            private:
                sf::Clock _clock;
                std::shared_ptr<Graphic::Window> _window;

                std::string selectedFilePath;
                bool _FDClosed = true;
        };
    }

#endif