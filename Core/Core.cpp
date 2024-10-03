/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "Core.hpp"
#include "../Gui/ToolsWin.hpp"
#include "../Gui/SizeWin.hpp"
#include "../Global/FactorySprite.hpp"


EpiGimp::Core::Core()
{
    this->_window = std::make_shared<Graphic::Window>("EpiGimp", 1600, 900);
    this->_canvasLayers.push_back(std::make_shared<EpiGimp::Layer>("Layer 1", 400, 300));
    this->_canvasLayers[0]->getDrawZone()->setPosition(0, 0);
    this->_canvasBG = std::make_unique<Graphic::DrawZone>(400, 300);
    this->_canvasBG->setPosition(0, 0);
    this->_canvasBG->drawCheckeredBackground();
    this->_window->getCamera()->setPosition(0, 0);
    this->_guiCore = std::make_shared<GUI::GUICore>(this->_window);

    this->_tools[EpiGimp::TOOL_BRUSH] = FactoryTool::GetInstance().createTool("Brush");
    this->_tools[EpiGimp::TOOL_ERASER] = FactoryTool::GetInstance().createTool("Eraser");
    this->_tools[EpiGimp::TOOL_BUCKET] = FactoryTool::GetInstance().createTool("Bucket");
    this->_tools[EpiGimp::TOOL_COLORPICKER] = FactoryTool::GetInstance().createTool("ColorPicker");


    this->_toolWindow = std::make_unique<GUI::ToolsWin>();
    this->_sizeWindow = std::make_unique<GUI::SizeWin>();
    this->_layersWindow = std::make_unique<GUI::LayersWin>(this->_canvasLayers);

    this->_currentLayerIndex = 0;
}

EpiGimp::Core::~Core()
{

}

void EpiGimp::Core::loop()
{
    std::shared_ptr<EpiGimp::Layer> currentLayer;
    while (this->_window->isOpen()) {
        this->_canvasLayers = this->_layersWindow->getLayers();
        this->_currentLayerIndex = this->_layersWindow->getCurrentLayerIndex();
        currentLayer = this->_canvasLayers[this->_currentLayerIndex];
        this->_window->resetRender();
        this->_guiCore->update();

        this->moveCamera();

        if (!this->_window->isMouseInUI()) {
            this->_tools[GlobalData.getCurrentTool()]->action(this->_window, currentLayer->getDrawZone());
        }

        this->_window->drawSprite(this->_canvasBG->getSprite());
        for (auto const &e: this->_canvasLayers) {
            if (e->isVisible())
                this->_window->drawSprite(e->getDrawZone()->getSprite());
        }

        this->handleTool();

        this->_toolWindow->display();

        if (GlobalData.getCanvasSize() != currentLayer->getDrawZone()->getSize()) {
            currentLayer->getDrawZone()->setSize(GlobalData.getCanvasSize().x, GlobalData.getCanvasSize().y);
            this->_canvasBG->setSize(GlobalData.getCanvasSize().x, GlobalData.getCanvasSize().y);
            this->_canvasBG->drawCheckeredBackground();
        }

        this->_sizeWindow->display();
        this->_layersWindow->display();

        this->_guiCore->display();
        this->_window->displayRender();
    }
}

void EpiGimp::Core::moveCamera()
{
    if (this->_window->isRightMousePressed()) {
        this->_window->getCamera()->moveCamera(this->_window->getMouseTranslation() * -0.9f);
    }
}

void EpiGimp::Core::handleTool()
{
    if (GlobalData.wasCurrentToolValueModified()) {
        this->_tools[GlobalData.getCurrentTool()]->setValue(GlobalData.getCurrentToolValue());
    }
    if (!this->_window->isMouseInUI()) {
        this->_tools[GlobalData.getCurrentTool()]->drawPreview(this->_window);
    }
    this->_tools[GlobalData.getCurrentTool()]->displayGUI();
}