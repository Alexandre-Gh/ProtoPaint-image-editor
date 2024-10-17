/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef RECT_WIN_H_
    #define RECT_WIN_H_

    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class RectWin : public GUI::AGUIWindow
        {
            public:
                RectWin();
                ~RectWin() = default;

                void content(); //Actual function to modify in inherited classes

            private:
                int _thickness = 4;
                bool _filled = false;
        };
    }

#endif