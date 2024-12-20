/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef ContrastWin_H_
    #define ContrastWin_H_

    #include "../includes/Headers.hpp"
    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class ContrastWin : public GUI::AGUIWindow
        {
            public:
                ContrastWin();
                ~ContrastWin() = default;

                void content(); //Actual function to modify in inherited classes
                void setValue(float f);
                const float &getValue();

            private:
                float _f;

        };
    }

#endif