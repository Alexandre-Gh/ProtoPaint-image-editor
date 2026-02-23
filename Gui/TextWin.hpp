/*
** ProtoPaint
** File description:
** Core
*/

#pragma once

#ifndef TEXT_WIN_H_
    #define TEXT_WIN_H_

    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class TextWin : public GUI::AGUIWindow
        {
            public:
                TextWin();
                ~TextWin() = default;

                void content(); //Actual function to modify in inherited classes

            private:
                int _size = 16;

                std::vector<std::string> _fonts;
                std::vector<std::string> _styles;
                int _currentFontIndex = 0;
                int _currentStyleIndex = 0;
        };
    }

#endif