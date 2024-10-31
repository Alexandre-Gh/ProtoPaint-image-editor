/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** OOP
*/

#ifndef TOOL_COLORPICKER_H_
    #define TOOL_COLORPICKER_H_

    #include "ATool.hpp"

    namespace EpiGimp
    {
        class ToolColorPicker: public EpiGimp::ATool
        {
            public:
                ToolColorPicker();
                ~ToolColorPicker() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);

            private:
                
        };
    }

#endif