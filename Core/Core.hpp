/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef CORE_H_
    #define CORE_H_

    #include "../Graphics/Window.hpp"
    #include "../Graphics/DrawZone.hpp"

    namespace EpiGimp
    {
        class Core
        {
            public:
                Core();
                ~Core();
                void loop();

            private:
                Graphic::Window _window;
                std::shared_ptr<Graphic::DrawZone> _canvasLayers;
                //std::vector<std::shared_ptr<Graphic::DrawZone>> _canvasLayers; //when multiple layers
        };
    }

#endif