/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef CORE_H_
    #define CORE_H_

    #include "../includes/Headers.hpp"
    #include "../Gui/GUICore.hpp"
    #include "../Graphics/Window.hpp"
    #include "../Graphics/DrawZone.hpp"
    #include "../Global/FactoryTool.hpp"

    namespace EpiGimp
    {
        class Core
        {
            public:
                Core();
                ~Core();
                void loop();

            private:
                std::shared_ptr<GUI::GUICore> _guiCore;
                std::shared_ptr<Graphic::Window> _window;
                std::shared_ptr<Graphic::DrawZone> _canvasLayers; //when multiple layers
                std::map<EpiGimp::varTool, std::unique_ptr<EpiGimp::ITool>> _tools;

                std::unique_ptr<GUI::IGUIWindow> _toolWindow;

        };
    }

#endif