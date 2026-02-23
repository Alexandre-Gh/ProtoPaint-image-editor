/*
** ProtoPaint
** File description:
** Core
*/

#pragma once

#ifndef LINE_WIN_H_
    #define LINE_WIN_H_

    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class LineWin : public GUI::AGUIWindow
        {
            public:
                LineWin();
                ~LineWin() = default;

                void content(); //Actual function to modify in inherited classes

            private:
                int _thickness = 4;
                bool _filled = false;
        };
    }

#endif