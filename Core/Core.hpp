/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef CORE_H_
    #define CORE_H_

    #include "../includes/Headers.hpp"
    #include "../Gui/GUICore.hpp"
    #include "../Graphics/Window.hpp"
    #include "../Graphics/DrawZone.hpp"
    #include "../Global/FactoryTool.hpp"
    #include "../Gui/LayersWin.hpp"
    #include "../Gui/SizeWin.hpp"
    #include "Layer.hpp"


    namespace EpiGimp
    {
        class Core
        {
            public:
                Core();
                ~Core();
                void loop();
                void moveCamera();
                void handleTool();
                void handleAction();
                void handleFileDialog();
                void handleShortcuts();
                void resetCanvas();
                void openFile();
                void saveFile();

                void reposition();

                void addState(const std::vector<std::shared_ptr<EpiGimp::Layer>>& layers);
                void undo();
                void redo();
                void flipAll(bool vertical);
                void flipCurrent(bool vertical);
                void rotateCanvas(float angle);

            private:
                unsigned int _currentLayerIndex;
                unsigned int _currentStateIndex;
                std::shared_ptr<GUI::GUICore> _guiCore;
                std::shared_ptr<Graphic::Window> _window;
                std::vector<std::shared_ptr<EpiGimp::Layer>> _canvasLayers; //when multiple layers
                std::vector<std::vector<std::shared_ptr<EpiGimp::Layer>>> _canvasHistory;
                std::unique_ptr<Graphic::DrawZone> _canvasBG;
                std::unique_ptr<Graphic::DrawZone> _canvasFG;
                std::map<EpiGimp::varTool, std::unique_ptr<EpiGimp::ITool>> _tools;

                std::unique_ptr<GUI::IGUIWindow> _toolWindow;
                std::unique_ptr<GUI::SizeWin> _sizeWindow;
                std::unique_ptr<GUI::IGUIWindow> _navBar;
                std::unique_ptr<GUI::LayersWin> _layersWindow;

                std::vector<std::shared_ptr<EpiGimp::Layer>> _undoCanvas;
                bool _loadFile = false;
                bool _saveFile = false;
                bool _nextSaveState = false;
                bool _toolIsUsed = true;

        };
    }

#endif