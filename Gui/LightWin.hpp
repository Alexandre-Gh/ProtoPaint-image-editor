/*
** ProtoPaint
** File description:
** Core
*/

#pragma once

#ifndef LightWin_H_
    #define LightWin_H_

    #include "../includes/Headers.hpp"
    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class LightWin : public GUI::AGUIWindow
        {
            public:
                LightWin();
                ~LightWin() = default;

                void content(); //Actual function to modify in inherited classes
                void setValue(float f);
                const float &getValue();

            private:
                float _f;

        };
    }

#endif