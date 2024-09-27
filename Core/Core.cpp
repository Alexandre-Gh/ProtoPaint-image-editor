/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "Core.hpp"
#include "../Gui/ToolsWin.hpp"
#include "../Gui/BrushWin.hpp"
#include "../Gui/EraserWin.hpp"
#include "../Global/FactorySprite.hpp"


EpiGimp::Core::Core()
{
    this->_window = std::make_shared<Graphic::Window>("EpiGimp", 1600, 900);
    this->_canvasLayers = std::make_shared<Graphic::DrawZone>(400, 300);
    this->_canvasLayers->setPosition(0, 0);
    this->_window->getCamera()->setPosition(0, 0);
    this->_guiCore = std::make_shared<GUI::GUICore>(this->_window);

    this->_tools[EpiGimp::TOOL_BRUSH] = FactoryTool::GetInstance().createTool("Brush");
    this->_tools[EpiGimp::TOOL_ERASER] = FactoryTool::GetInstance().createTool("Eraser");
    this->_tools[EpiGimp::TOOL_BUCKET] = FactoryTool::GetInstance().createTool("Bucket");

    this->_toolsWindows[EpiGimp::TOOL_BRUSH] = std::make_unique<GUI::BrushWin>();
    this->_toolsWindows[EpiGimp::TOOL_ERASER] = std::make_unique<GUI::EraserWin>();

    this->_toolWindow = std::make_unique<GUI::ToolsWin>();
}

EpiGimp::Core::~Core()
{

}

void EpiGimp::Core::loop()
{
    while (this->_window->isOpen()) {
        this->_window->resetRender();
        this->_guiCore->update();

        this->_tools[GlobalData.getCurrentTool()]->action(this->_window, this->_canvasLayers);
        if (GlobalData.wasCurrentToolValueModified()) {
            this->_tools[GlobalData.getCurrentTool()]->setValue(GlobalData.getCurrentToolValue());
        }

        this->_window->drawSprite(this->_canvasLayers->getSprite());

        if (this->_window->isRightMousePressed()) {
            this->_window->getCamera()->moveCamera(this->_window->getMouseTranslation() * -0.9f);
        }
        this->_toolWindow->display();
        if (this->_toolsWindows.count(GlobalData.getCurrentTool()) != 0) {
            this->_toolsWindows[GlobalData.getCurrentTool()]->display();
        }

        this->_guiCore->display();
        this->_window->displayRender();
    }
}