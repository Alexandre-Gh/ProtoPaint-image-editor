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
                TOOL_BUCKET = 3,
                TOOL_COLORPICKER = 4
            };

            enum varAction
            {
                NO_ACTION = 0,

                IMPORT_IMAGE = 1,
                SAVE_IMAGE = 2,
                UNDO = 3,
                REDO = 4,
                NEW = 5,
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

                const sf::Vector2f &getCanvasSize() { return _canvasSize; }
                void setCanvasSize(float w, float h) { _canvasSize = {w, h}; }

                const EpiGimp::varTool &setCurrentToolValue(std::string valueName, int value);
                const std::pair<std::string, int> &getCurrentToolValue();
                bool wasCurrentToolValueModified();

                const EpiGimp::varAction &getCurrentAction();
                void setCurrentAction(EpiGimp::varAction action);

                const bool &getAddState() { return _nextStateState; };
                void setAddState(bool value) { _nextStateState = value; };

                //=======================

            protected:
                DataTransfer();
                DataTransfer(const DataTransfer&) = delete;
                DataTransfer& operator=(const DataTransfer&) = delete;

                //=====GLOBAL DATA=======
                sf::Color _mainColor = sf::Color::Red;
                sf::Color _secondColor = sf::Color::White;
                EpiGimp::varTool _currentTool = EpiGimp::TOOL_BRUSH;

                bool _wasModified = false;

                std::pair<std::string, int> _lastModifiedValue;
                EpiGimp::varAction _currentAction = EpiGimp::varAction::NO_ACTION;

                sf::Vector2f _canvasSize = {400, 300};

                bool _nextStateState = false;


                //=======================
        };

        #define GlobalData DataTransfer::GetInstance()

#endif