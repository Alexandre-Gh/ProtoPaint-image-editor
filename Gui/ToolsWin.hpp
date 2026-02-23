/*
** ProtoPaint
** File description:
** Core
*/

#pragma once

#ifndef TOOLS_WIN_H_
    #define TOOLS_WIN_H_

    #include "../includes/Headers.hpp"
    #include "AGUIWindow.hpp"

    namespace GUI
    {
        class ToolsWin : public GUI::AGUIWindow
        {
            public:
                ToolsWin();
                ~ToolsWin() = default;

                void content(); //Actual function to modify in inherited classes

            private:
                std::map<ProtoPaint::varTool, std::unique_ptr<sf::Sprite>> _buttonSprites;
                std::map<ProtoPaint::varTool, std::string> _ids;
                sf::Color _bgColor;

                void setCurrentTool(ProtoPaint::varTool toolType) { GlobalData.setCurrentTool(toolType); }
                const ProtoPaint::varTool &getCurrentTool() { return GlobalData.getCurrentTool(); }
        };
    }

#endif