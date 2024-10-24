/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef SPRAY_WIN_H_
    #define SPRAY_WIN_H_

    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class SprayWin : public GUI::AGUIWindow
        {
            public:
                SprayWin();
                ~SprayWin() = default;

                void content(); //Actual function to modify in inherited classes

            private:
                int _size = 30;
                bool _rainbow = false;
        };
    }

#endif