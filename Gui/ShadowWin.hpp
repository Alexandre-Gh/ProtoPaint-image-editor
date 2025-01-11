/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef ShadowWin_H_
    #define ShadowWin_H_

    #include "../includes/Headers.hpp"
    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class ShadowWin : public GUI::AGUIWindow
        {
            public:
                ShadowWin();
                ~ShadowWin() = default;

                void content(); //Actual function to modify in inherited classes
                void setValue(float f);
                const float &getValue();

            private:
                float _f;

        };
    }

#endif