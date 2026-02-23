/*
** ProtoPaint
** File description:
** Core
*/

#pragma once

#ifndef ERASER_WIN_H_
    #define ERASER_WIN_H_

    #include "../includes/Headers.hpp"
    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class EraserWin : public GUI::AGUIWindow
        {
            public:
                EraserWin();
                ~EraserWin() = default;

                void content(); //Actual function to modify in inherited classes

            private:
                int _size = 4;

                std::vector<std::string> _items;
                int _currentToolIndex = 0;
        };
    }

#endif