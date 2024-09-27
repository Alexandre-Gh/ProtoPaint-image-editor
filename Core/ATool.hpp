/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef ATOOL_H_
    #define ATOOL_H_

    #include "../includes/Headers.hpp"
    #include "../Graphics/Window.hpp"
    #include "../Interfaces/IGUIWindow.hpp"
    #include "../Graphics/DrawZone.hpp"
    #include "../Interfaces/ITool.hpp"
    #include "../Global/DataTransfer.hpp"

    namespace EpiGimp
    {
        class ATool : public EpiGimp::ITool
        {
            public:
                ATool();
                ~ATool();
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);
                void setValue(std::string valueName, int value);

            protected:
                std::unordered_map<std::string, int> _values;

                const sf::Color& getMainColor() { return GlobalData.getMainColor(); }
                const sf::Color& getSecondColor() { return GlobalData.getSecondColor(); }

        };
    }

#endif