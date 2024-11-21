/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef COLOR_HISTORY_WIN_H_
    #define COLOR_HISTORY_WIN_H_

    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class ColorHistoryWin : public GUI::AGUIWindow
        {
            public:
                ColorHistoryWin();
                ~ColorHistoryWin() = default;

                void content(); //Actual function to modify in inherited classes

                void addColor();

            private:
                sf::Color _lastColor;

                struct ColorComparator {
                    bool operator()(const sf::Color& lhs, const sf::Color& rhs) const {
                        return std::tie(lhs.r, lhs.g, lhs.b, lhs.a) < std::tie(rhs.r, rhs.g, rhs.b, rhs.a);
                    }
                };

                std::map<sf::Color, ImVec4, ColorComparator> _colors;

        };
    }

#endif