/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef DATA_TRANSFER_H_
    #define DATA_TRANSFER_H_

        #include "../includes/Headers.hpp"

        namespace EpiGimp
        {
            enum varTool
            {
                NONE = 0,

                TOOL_BRUSH = 1,
                TOOL_ERASER = 2,
                TOOL_BUCKET = 3
            };
        };

        class DataTransfer
        {
            public:
                static DataTransfer &GetInstance() { static DataTransfer instance; return instance; }

                //=====GLOBAL DATA=======

                const sf::Color &getMainColor() { return _mainColor; }
                void setMainColor(sf::Color color) { _mainColor = color; }

                const sf::Color &getSecondColor() { return _secondColor; }
                void setSecondColor(sf::Color color) { _secondColor = color; }

                const EpiGimp::varTool &getCurrentTool() { return _currentTool; }
                void setCurrentTool(EpiGimp::varTool toolType) { _currentTool = toolType; }

                const EpiGimp::varTool &setCurrentToolValue(std::string valueName, int value);
                const std::pair<std::string, int> &getCurrentToolValue();
                bool wasCurrentToolValueModified();

                //=======================

            protected:
                DataTransfer();
                DataTransfer(const DataTransfer&) = delete;
                DataTransfer& operator=(const DataTransfer&) = delete;

                //=====GLOBAL DATA=======
                sf::Color _mainColor = sf::Color::Red;
                sf::Color _secondColor = sf::Color::White;
                EpiGimp::varTool _currentTool = EpiGimp::TOOL_BRUSH;

                std::pair<std::string, int> _lastModifiedValue;
                bool _wasModified = false;
                //=======================
        };

        #define GlobalData DataTransfer::GetInstance()

#endif