/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** ErrorException
*/

#pragma once

#ifndef ITOOL_H_
    #define ITOOL_H_

    #include "../Graphics/Window.hpp"
    #include "../Graphics/DrawZone.hpp"

    namespace EpiGimp
    {
        class ITool
        {
            public:
                virtual ~ITool() = default;

                virtual void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone) = 0;
                virtual void setValue(std::pair<std::string, int> value) = 0;
                virtual void drawPreview(std::shared_ptr<Graphic::Window> win) = 0;
                virtual void drawPreviewInCurrentCanvas(std::shared_ptr<Graphic::Window> win) = 0;
                virtual void displayGUI() = 0;
        };
    }

#endif