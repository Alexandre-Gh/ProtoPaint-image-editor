/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef NAVBAR_H_
    #define NAVBAR_H_

    #include "../includes/Headers.hpp"
    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class NavBar : public GUI::AGUIWindow
        {
            public:
                NavBar();
                ~NavBar() = default;

                void content(); //Actual function to modify in inherited classes
                void setDisplayedText(std::string text);

            private:
                bool _darkMode = true;
                std::string _displayedText = "";

        };
    }

#endif