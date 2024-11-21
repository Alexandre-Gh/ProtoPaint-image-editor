/*
** EPITECH PROJECT, 2024
** EpiGimp
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
                TOOL_COLORPICKER = 4,
                TOOL_PENCIL = 5,
                TOOL_SPRAY = 6,
                TOOL_RECT = 7,
                TOOL_CIRCLE = 8,
                TOOL_LINE = 9,
                TOOL_TEXT = 10,
                TOOL_IMAGE = 11,
                TOOL_SYMETRICAL = 12,
            };

            enum varAction
            {
                NO_ACTION,

                IMPORT_IMAGE,
                IMPORT_IMAGE_LAYER,
                IMPORT_IMAGE_CURRENT,
                SAVE_IMAGE,
                UNDO,
                REDO,
                NEW,
                RESIZE,
                RESIZE_CANVAS,
                FLIP_HOR,
                FLIP_VERT,
                FLIP_ALL_HOR,
                FLIP_ALL_VERT,
                ROTATE_LEFT,
                ROTATE_RIGHT,
                ROTATE_FULL,
                SAVE_IMAGE_ACTIVE,
                REPOSITION,

                WIN_RESIZE,
                WIN_IMPORT,
                WIN_WARNING,
            };
        };

        class DataTransfer
        {
            public:
                static DataTransfer &GetInstance() { static DataTransfer instance; return instance; }

                //======GLOBAL DATA======

                const sf::Color &getMainColor() { return _mainColor; }
                void setMainColor(sf::Color color) { _mainColor = color; }

                const sf::Color &getSecondColor() { return _secondColor; }
                void setSecondColor(sf::Color color) { _secondColor = color; }

                const EpiGimp::varTool &getCurrentTool() { return _currentTool; }
                void setCurrentTool(EpiGimp::varTool toolType) { _currentTool = toolType; }

                const sf::Vector2f &getCanvasSize() { return _canvasSize; }
                void setCanvasSize(float w, float h) { _canvasSize = {w, h}; }

                void setCurrentToolValue(std::string valueName, int value);
                const std::pair<std::string, int> &getCurrentToolValue();
                bool wasCurrentToolValueModified();

                const EpiGimp::varAction &getCurrentAction();
                void setCurrentAction(EpiGimp::varAction action);

                const bool &getAddState() { return _nextStateState; };
                void setAddState(bool value) { _nextStateState = value; };

                const std::vector<std::string> &getFonts() { return _fonts; };
                const std::vector<std::string> &getFontFilepaths() { return _fontFilepaths; };

                const std::string &getImageBrushFilepath() { return _currentImageBrushFilepath; }
                void setImageBrushFilepath(std::string filepath) { _currentImageBrushFilepath = filepath; }

                //========================

            protected:
                DataTransfer();
                DataTransfer(const DataTransfer&) = delete;
                DataTransfer& operator=(const DataTransfer&) = delete;

                //======GLOBAL DATA======
                sf::Color _mainColor = sf::Color::Red;
                sf::Color _secondColor = sf::Color::White;
                EpiGimp::varTool _currentTool = EpiGimp::TOOL_BRUSH;
                std::string _currentImageBrushFilepath = "";

                bool _wasModified = false;

                std::pair<std::string, int> _lastModifiedValue;
                EpiGimp::varAction _currentAction = EpiGimp::varAction::NO_ACTION;

                sf::Vector2f _canvasSize = {400, 300};

                bool _nextStateState = false;

                std::vector<std::string> _fonts;
                std::vector<std::string> _fontFilepaths;

                //=====================
        };

        #define GlobalData DataTransfer::GetInstance()

        #define SelectedButtonColor ImVec4(0.0f, 0.0f, 1.0f, 0.8f)
        #define ButtonColor ImVec4(1.0f, 1.0f, 1.0f, 0.1f)

#endif