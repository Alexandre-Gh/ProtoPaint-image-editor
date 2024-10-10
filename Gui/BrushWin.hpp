/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef BRUSH_WIN_H_
    #define BRUSH_WIN_H_

    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class BrushWin : public GUI::AGUIWindow
        {
            public:
                BrushWin();
                ~BrushWin() = default;

                void content(); //Actual function to modify in inherited classes

            private:
                int _size = 4;
                bool _gradient = false;
                bool _rainbow = false;
        };
    }

#endif