/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "Core.hpp"
#include "../Gui/ToolsWin.hpp"
#include "../Gui/NavBar.hpp"
#include "../Global/FactorySprite.hpp"


EpiGimp::Core::Core()
{
    this->_window = std::make_shared<Graphic::Window>("EpiGimp", 1600, 900);
    this->_canvasLayers.push_back(std::make_shared<EpiGimp::Layer>("Layer 1", 400, 300));
    this->_canvasLayers[0]->getDrawZone()->setPosition(0, 0);
    this->addState(this->_canvasLayers);
    this->_canvasBG = std::make_unique<Graphic::DrawZone>(400, 300);
    this->_canvasBG->setPosition(0, 0);
    this->_canvasBG->drawCheckeredBackground();
    this->_window->getCamera()->setPosition(200, 150);
    this->_guiCore = std::make_shared<GUI::GUICore>(this->_window);

    this->_tools[EpiGimp::TOOL_BRUSH] = FactoryTool::GetInstance().createTool("Brush");
    this->_tools[EpiGimp::TOOL_ERASER] = FactoryTool::GetInstance().createTool("Eraser");
    this->_tools[EpiGimp::TOOL_BUCKET] = FactoryTool::GetInstance().createTool("Bucket");
    this->_tools[EpiGimp::TOOL_COLORPICKER] = FactoryTool::GetInstance().createTool("ColorPicker");
    this->_tools[EpiGimp::TOOL_PENCIL] = FactoryTool::GetInstance().createTool("Pencil");
    this->_tools[EpiGimp::TOOL_SPRAY] = FactoryTool::GetInstance().createTool("Spray");
    this->_tools[EpiGimp::TOOL_RECT] = FactoryTool::GetInstance().createTool("Rect");
    this->_tools[EpiGimp::TOOL_CIRCLE] = FactoryTool::GetInstance().createTool("Circle");
    this->_tools[EpiGimp::TOOL_LINE] = FactoryTool::GetInstance().createTool("Line");

    this->_toolWindow = std::make_unique<GUI::ToolsWin>();
    this->_sizeWindow = std::make_unique<GUI::SizeWin>();
    this->_navBar = std::make_unique<GUI::NavBar>();
    this->_layersWindow = std::make_unique<GUI::LayersWin>(this->_canvasLayers);

    this->_currentLayerIndex = 0;
    this->_currentStateIndex = 0;
}

EpiGimp::Core::~Core()
{

}

void EpiGimp::Core::loop()
{
    std::shared_ptr<EpiGimp::Layer> currentLayer;
    while (this->_window->isOpen()) {
        this->_window->resetRender();
        this->_guiCore->update();

        this->_canvasLayers = this->_layersWindow->getLayers();
        this->_currentLayerIndex = this->_layersWindow->getCurrentLayerIndex();

        currentLayer = this->_canvasLayers[this->_currentLayerIndex];

        this->handleShortcuts();
        this->moveCamera();

        if (!this->_window->isMouseInUI()) {
            this->_tools[GlobalData.getCurrentTool()]->action(this->_window, currentLayer->getDrawZone());
        }

        this->_window->drawSprite(this->_canvasBG->getSprite());
        for (auto const &e: this->_canvasLayers) {
            if (e->isVisible())
                this->_window->drawSprite(e->getDrawZone()->getSprite());
            if (currentLayer == e) {
                this->_tools[GlobalData.getCurrentTool()]->drawPreviewInCurrentCanvas(this->_window);
            }
        }

        // if (this->_window->isKeyJustPressed(sf::Keyboard::P)) {
        //     sf::Font font;
        //     font.loadFromFile("./assets/Monocraft.ttf");
        //     sf::Text text("JAMBON", font, 20);
        //     text.setStyle(sf::Text::Underlined);
        //     currentLayer->getDrawZone()->addDraw(text);
        // }

        this->handleTool();
        this->handleAction();
        this->handleFileDialog();

        this->_toolWindow->display();

        this->_sizeWindow->display();
        this->_layersWindow->display();
        this->_navBar->display();


        if (GlobalData.getAddState()) {
            this->addState(this->_layersWindow->getLayers());
            GlobalData.setAddState(false);
            this->_nextSaveState = false;
            sf::Vector2f newSize = currentLayer->getDrawZone()->getSize();
            this->_sizeWindow->setSize(newSize.x, newSize.y);
        }


        this->_guiCore->display();
        this->_window->displayRender();
    }
}

void EpiGimp::Core::moveCamera()
{
    bool hor = this->_window->isKeyPressed(sf::Keyboard::LControl);
    bool ver = this->_window->isKeyPressed(sf::Keyboard::LShift);

    if (!(ver || hor)) {
        this->_window->zoomCamera();
    }
    if (this->_window->isRightMousePressed()) {
        this->_window->getCamera()->moveCamera(this->_window->getMouseTranslation() * -0.9f);
    }

    sf::Vector2f vector(0, 0);
    vector.x = hor ? 20 * this->_window->getMouseWheel() : 0;
    vector.y = ver ? 20 * this->_window->getMouseWheel() : 0;
    if (vector.x != 0 || vector.y != 0) {
        this->_window->getCamera()->moveCamera(vector);
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

void EpiGimp::Core::handleAction()
{
    switch (GlobalData.getCurrentAction()) {
        case EpiGimp::varAction::NO_ACTION: break;

        case EpiGimp::varAction::SAVE_IMAGE: this->_saveFile = true; break;
        case EpiGimp::varAction::IMPORT_IMAGE: this->_loadFile = true; break;
        case EpiGimp::varAction::UNDO: this->undo(); break;
        case EpiGimp::varAction::REDO: this->redo(); break;
        case EpiGimp::varAction::NEW: this->resetCanvas(); break;
        case EpiGimp::varAction::RESIZE: this->reposition(); this->addState(this->_canvasLayers); break;
        case EpiGimp::varAction::FLIP_HOR: this->flipCurrent(false); break;
        case EpiGimp::varAction::FLIP_VERT: this->flipCurrent(true); break;
        case EpiGimp::varAction::FLIP_ALL_HOR: this->flipAll(false); break;
        case EpiGimp::varAction::FLIP_ALL_VERT: this->flipAll(true); break;
    }
    GlobalData.setCurrentAction(EpiGimp::varAction::NO_ACTION);
}

void EpiGimp::Core::handleFileDialog()
{
    if (this->_loadFile) {
        this->_guiCore->startLoadFile();
        this->openFile();
        return;
    }
    if (this->_saveFile) {
        this->_guiCore->startSaveFile();
        this->saveFile();
    }
}

void EpiGimp::Core::handleShortcuts()
{
    if (this->_window->isKeyPressed(sf::Keyboard::LControl)) {
        if (this->_window->isKeyJustPressed(sf::Keyboard::Z)) {
            GlobalData.setCurrentAction(EpiGimp::varAction::UNDO);
        }
        if (this->_window->isKeyJustPressed(sf::Keyboard::Y)) {
            GlobalData.setCurrentAction(EpiGimp::varAction::REDO);
        }
        if (this->_window->isKeyJustPressed(sf::Keyboard::O) && !this->_loadFile) {
            GlobalData.setCurrentAction(EpiGimp::varAction::IMPORT_IMAGE);
        }
        if (this->_window->isKeyJustPressed(sf::Keyboard::S) && !this->_saveFile) {
            GlobalData.setCurrentAction(EpiGimp::varAction::SAVE_IMAGE);
        }
        if (this->_window->isKeyJustPressed(sf::Keyboard::N)) {
            GlobalData.setCurrentAction(EpiGimp::varAction::NEW);
        }
    }
}

void EpiGimp::Core::resetCanvas()
{
    this->_canvasLayers.clear();
    this->_canvasLayers.push_back(std::make_shared<EpiGimp::Layer>("Layer 1", 400, 300));
    GlobalData.setCanvasSize(400, 300);
    this->_currentLayerIndex = 0;
    this->_layersWindow = std::make_unique<GUI::LayersWin>(this->_canvasLayers);
    this->_window->getCamera()->resetZoom();
    this->_window->getCamera()->setPosition(this->_canvasBG->getPosition());
    this->_canvasHistory.clear();
    this->addState(this->_canvasLayers);
    this->_currentStateIndex = 0;
}

void EpiGimp::Core::saveFile()
{
    std::string filepath = this->_guiCore->getFilePath();
    if (filepath != "") {
        this->_guiCore->resetFilePath();
        Graphic::DrawZone saved(GlobalData.getCanvasSize().x, GlobalData.getCanvasSize().y);
        for (auto const &e: this->_canvasLayers) {
            saved.addSprite(e->getDrawZone()->getSprite());
        }
        saved.saveToFile(filepath);
        this->_saveFile = false;
    }
    if (this->_guiCore->getFDClosed()) {
        this->_saveFile = false;
    }
}

void EpiGimp::Core::openFile()
{
    std::string filepath = this->_guiCore->getFilePath();
    if (filepath != "") {
        this->resetCanvas();
        this->_guiCore->resetFilePath();
        this->_canvasLayers[this->_currentLayerIndex]->getDrawZone()->setFromFile(filepath);
        // this->_canvasHistory.clear();
        this->addState(this->_canvasLayers);
        this->_loadFile = false;
        this->reposition();
    }
    if (this->_guiCore->getFDClosed()) {
        this->_loadFile = false;
    }
}

void EpiGimp::Core::addState(const std::vector<std::shared_ptr<EpiGimp::Layer>>& layers)
{
    if (this->_currentStateIndex + 1 < this->_canvasHistory.size()) {
        std::cout << "OVERRIDE " << this->_currentStateIndex << std::endl;
        for (int i = this->_canvasHistory.size() - 1; i > this->_currentStateIndex; i--) {
            this->_canvasHistory.pop_back();
        }
        this->_canvasHistory[this->_currentStateIndex] = this->_undoCanvas;
    }

    std::vector<std::shared_ptr<EpiGimp::Layer>> clonedLayers;
    for (const auto& layer : layers) {
        clonedLayers.push_back(layer->clone());
    }

    this->_canvasHistory.push_back(clonedLayers);
    this->_currentStateIndex = this->_canvasHistory.size() - 1;

    this->_undoCanvas.clear();
    for (const auto& layer : this->_canvasHistory[this->_currentStateIndex]) {
        this->_undoCanvas.push_back(layer->clone());
    }
    std::cout << "NEWSTATE " << this->_canvasHistory.size() << std::endl;
}

void EpiGimp::Core::undo()
{
    if (this->_currentStateIndex > 0) {
        this->_currentStateIndex--;
        this->_layersWindow->setLayers(this->_canvasHistory[this->_currentStateIndex], this->_currentLayerIndex);
        this->_undoCanvas.clear();
        for (const auto& layer : this->_canvasHistory[this->_currentStateIndex]) {
            this->_undoCanvas.push_back(layer->clone());
        }
        sf::Vector2f size = this->_layersWindow->getLayers()[0]->getDrawZone()->getSize();
        if (this->_sizeWindow->getSize() != size) {
            this->_canvasBG->setSize(size);
            this->_canvasBG->drawCheckeredBackground();
            this->_sizeWindow->setSize(size.x, size.y);
        }
        std::cout << "UNDO " << this->_canvasHistory.size() - 1 << " | "<< this->_currentStateIndex + 1 << std::endl;
    } else {
        std::cout << "No more undos available." << std::endl;
    }
}

void EpiGimp::Core::redo()
{
    if (this->_currentStateIndex + 1 < this->_canvasHistory.size()) {
        this->_currentStateIndex++;
        this->_layersWindow->setLayers(this->_canvasHistory[this->_currentStateIndex], this->_currentLayerIndex);
        this->_undoCanvas.clear();
        for (const auto& layer : this->_canvasHistory[this->_currentStateIndex]) {
            this->_undoCanvas.push_back(layer->clone());
        }
        sf::Vector2f size = this->_layersWindow->getLayers()[0]->getDrawZone()->getSize();
        if (this->_sizeWindow->getSize() != size) {
            this->_canvasBG->setSize(size);
            this->_canvasBG->drawCheckeredBackground();
            this->_sizeWindow->setSize(size.x, size.y);
        }
        std::cout << "REDO " << this->_canvasHistory.size() - 1 << " | "<< this->_currentStateIndex + 1 << std::endl;
    } else {
        std::cout << "No more redos available." << std::endl;
    }
}

void EpiGimp::Core::reposition()
{
    for (auto const &e: this->_canvasLayers) {
        e->getDrawZone()->setSize(GlobalData.getCanvasSize().x, GlobalData.getCanvasSize().y);
        e->getDrawZone()->setPosition(0, 0);
    }
    this->_canvasBG->setSize(GlobalData.getCanvasSize().x, GlobalData.getCanvasSize().y);
    this->_canvasBG->setPosition(0, 0);
    this->_canvasBG->drawCheckeredBackground();
    this->_window->getCamera()->setPosition(GlobalData.getCanvasSize().x / 2, GlobalData.getCanvasSize().y / 2);
    sf::Vector2f newSize = this->_canvasBG->getSize();
    this->_sizeWindow->setSize(newSize.x, newSize.y);
}

void EpiGimp::Core::flipAll(bool vertical)
{
    for (auto const &e: this->_canvasLayers) {
        e->getDrawZone()->flip(vertical);
    }
    this->addState(this->_canvasLayers);
}

void EpiGimp::Core::flipCurrent(bool vertical)
{
    this->_canvasLayers[this->_currentLayerIndex]->getDrawZone()->flip(vertical);
    this->addState(this->_canvasLayers);
}
