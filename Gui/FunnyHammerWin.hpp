/*
** ProtoPaint
** File description:
** Core
*/

#pragma once

#ifndef FUNNY_HAMMER_WIN_H_
    #define FUNNY_HAMMER_WIN_H_

    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class FunnyHammerWin : public GUI::AGUIWindow
        {
            public:
                FunnyHammerWin();
                ~FunnyHammerWin() = default;

                void content(); //Actual function to modify in inherited classes

            private:
                int _size = 10;
                bool _rotate = false;
        };
    }

#endif