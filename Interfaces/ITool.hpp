/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef ITOOL_H_
    #define ITOOL_H_

    #include "../includes/Headers.hpp"
    #include "../Graphics/Window.hpp"
    #include "../Graphics/DrawZone.hpp"

    namespace EpiGimp
    {
        class ITool
        {
            public:
                virtual ~ITool() = default;

                virtual void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone) = 0;
                virtual void setValue(std::string valueName, int value) = 0;
        };
    }

#endif