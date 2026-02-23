/*
** ProtoPaint
** File description:
** ErrorException
*/

#pragma once

#ifndef DATA_TRANSFER_H_
    #define DATA_TRANSFER_H_

        #include "../includes/Headers.hpp"

        namespace ProtoPaint
        {
            enum varTool
            {
                NONE = 0,

                TOOL_BRUSH,
                TOOL_ERASER,
                TOOL_BUCKET,
                TOOL_COLORPICKER,
                TOOL_PENCIL,
                TOOL_SPRAY,
                TOOL_RECT,
                TOOL_CIRCLE,
                TOOL_LINE,
                TOOL_TEXT,
                TOOL_IMAGE,
                TOOL_SELECTION,

                TOOL_FUNNY_HAMMER,
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
                INVERT,
                LIGHT,
                CONTRAST,
                SHADOW,

                WIN_RESIZE,
                WIN_IMPORT,
                WIN_WARNING,
                WIN_LIGHT,
                WIN_CONTRAST,
                WIN_SHADOW,
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

                const ProtoPaint::varTool &getCurrentTool() { return _currentTool; }
                void setCurrentTool(ProtoPaint::varTool toolType) { _currentTool = toolType; }

                const sf::Vector2f &getCanvasSize() { return _canvasSize; }
                void setCanvasSize(float w, float h) { _canvasSize = {w, h}; }

                void setCurrentToolValue(std::string valueName, int value);
                const std::pair<std::string, int> &getCurrentToolValue();
                bool wasCurrentToolValueModified();

                const ProtoPaint::varAction &getCurrentAction();
                void setCurrentAction(ProtoPaint::varAction action);

                const bool &getAddState() { return _nextStateState; };
                void setAddState(bool value) { _nextStateState = value; };

                const std::vector<std::string> &getFonts() { return _fonts; };
                const std::vector<std::string> &getFontFilepaths() { return _fontFilepaths; };

                const sf::Sprite &getCopy() { _copy.setTexture(_copyTexture, true); return _copy; };
                void setCopy(const sf::Sprite &copy, const sf::Texture &text) { _copy = copy; _copyTexture = text; };

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
                ProtoPaint::varTool _currentTool = ProtoPaint::TOOL_BRUSH;
                std::string _currentImageBrushFilepath = "";

                bool _wasModified = false;

                std::pair<std::string, int> _lastModifiedValue;
                ProtoPaint::varAction _currentAction = ProtoPaint::varAction::NO_ACTION;

                sf::Vector2f _canvasSize = {400, 300};

                bool _nextStateState = false;

                std::vector<std::string> _fonts;
                std::vector<std::string> _fontFilepaths;

                sf::Sprite _copy;
                sf::Texture _copyTexture;

                //=====================
        };

        #define GlobalData DataTransfer::GetInstance()

        #define SelectedButtonColor ImVec4(0.0f, 0.0f, 1.0f, 0.8f)
        #define ButtonColor ImVec4(1.0f, 1.0f, 1.0f, 0.1f)

#endif