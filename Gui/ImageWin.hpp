/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef Image_WIN_H_
    #define Image_WIN_H_

    #include "../includes/Headers.hpp"
    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class ImageWin : public GUI::AGUIWindow
        {
            public:
                ImageWin();
                ~ImageWin() = default;

                void content(); //Actual function to modify in inherited classes

            private:
                std::string _filepath = "";

                std::string getFilePathLoad();
        };
    }

#endif