/*
** EPITECH PROJECT, 2024
** EpiGimp
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

            private:
                sf::Clock _clock;
                std::shared_ptr<Graphic::Window> _window;
                std::vector<std::unique_ptr<GUI::IGUIWindow>> _guis; //All gui windows
        };
    }

#endif