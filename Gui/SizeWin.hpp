/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef SIZEWIN_H_
    #define SIZEWIN_H_

    #include "../includes/Headers.hpp"
    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class SizeWin : public GUI::AGUIWindow
        {
            public:
                SizeWin();
                ~SizeWin() = default;

                void content(); //Actual function to modify in inherited classes

            private:
                int _x;
                int _y;

        };
    }

#endif