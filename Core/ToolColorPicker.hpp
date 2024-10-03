/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** OOP
*/

#ifndef TOOLCOLORPICKER_H_
    #define TOOLCOLORPICKER_H_

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