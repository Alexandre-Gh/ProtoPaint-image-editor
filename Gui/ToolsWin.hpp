/*
** EPITECH PROJECT, 2024
** EpiGimp
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
                std::map<EpiGimp::varTool, std::unique_ptr<sf::Sprite>> _buttonSprites;
                std::map<EpiGimp::varTool, std::string> _ids;
                sf::Color _bgColor;

                void setCurrentTool(EpiGimp::varTool toolType) { GlobalData.setCurrentTool(toolType); }
                const EpiGimp::varTool &getCurrentTool() { return GlobalData.getCurrentTool(); }
        };
    }

#endif