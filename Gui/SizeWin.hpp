/*
** ProtoPaint
** File description:
** Core
*/

#pragma once

#ifndef SIZEWIN_H_
    #define SIZEWIN_H_

    #include "../includes/Headers.hpp"
    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class SizeWin : public GUI::AGUIWindow
        {
            public:
                SizeWin();
                ~SizeWin() = default;

                void content(); //Actual function to modify in inherited classes
                void setSize(int x, int y);
                const sf::Vector2f &getSize();

            private:
                int _x;
                int _y;
                int _percent;
                sf::Vector2f _ret;
                bool _sizePercent;
                bool _resizeContent;

        };
    }

#endif