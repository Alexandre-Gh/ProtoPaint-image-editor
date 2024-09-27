/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "Core.hpp"
#include "../Gui/ToolsWin.hpp"
#include "../Global/FactorySprite.hpp"


EpiGimp::Core::Core()
{
    this->_window = std::make_shared<Graphic::Window>("EpiGimp", 1600, 900);
    this->_canvasLayers = std::make_shared<Graphic::DrawZone>(800, 600);
    this->_canvasLayers->setPosition(0, 0);
    this->_window->getCamera()->setPosition(0, 0);
    this->_guiCore = std::make_shared<GUI::GUICore>(this->_window);

    this->_tools[EpiGimp::TOOL_BRUSH] = FactoryTool::GetInstance().createTool("Brush");
    this->_tools[EpiGimp::TOOL_ERASER] = FactoryTool::GetInstance().createTool("Eraser");

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

        this->_window->drawSprite(this->_canvasLayers->getSprite());

        if (this->_window->isRightMousePressed()) {
            this->_window->getCamera()->moveCamera(this->_window->getMouseTranslation() * 0.5f);
        }
        std::cout << this->_window->getMouseTranslation().x << " | " << this->_window->getMouseTranslation().y << std::endl;

        this->_toolWindow->display();

        this->_guiCore->display();
        this->_window->displayRender();
    }
}