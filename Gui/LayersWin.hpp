/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef LAYERSWIN_H_
    #define LAYERSWIN_H_

    #include "../includes/Headers.hpp"
    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class LayersWin : public GUI::AGUIWindow
        {
            public:
                LayersWin();
                ~LayersWin() = default;

                void content(); //Actual function to modify in inherited classes

            private:


        };
    }

#endif