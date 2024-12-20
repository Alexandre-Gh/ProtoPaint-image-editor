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
    this->_tools[EpiGimp::TOOL_TEXT] = FactoryTool::GetInstance().createTool("Text");
    this->_tools[EpiGimp::TOOL_IMAGE] = FactoryTool::GetInstance().createTool("BrushImage");
    this->_tools[EpiGimp::TOOL_SELECTION] = FactoryTool::GetInstance().createTool("Selection");
    this->_tools[EpiGimp::TOOL_FUNNY_HAMMER] = FactoryTool::GetInstance().createTool("FunnyHammer");


    this->_toolWindow = std::make_unique<GUI::ToolsWin>();
    this->_sizeWindow = std::make_unique<GUI::SizeWin>();
    this->_navBar = std::make_unique<GUI::NavBar>();
    this->_layersWindow = std::make_unique<GUI::LayersWin>(this->_canvasLayers);
    this->_colorHistoryWindow = std::make_unique<GUI::ColorHistoryWin>();
    this->_lightWindow = std::make_unique<GUI::LightWin>();
    this->_contrastWindow = std::make_unique<GUI::ContrastWin>();

    this->_currentLayerIndex = 0;
    this->_currentStateIndex = 0;

    this->_shortcutCTRL = {
        { sf::Keyboard::Z, []() { GlobalData.setCurrentAction(EpiGimp::varAction::UNDO); } },
        { sf::Keyboard::Y, []() { GlobalData.setCurrentAction(EpiGimp::varAction::REDO); } },
        { sf::Keyboard::O, [this]() { if (!this->_loadFile) GlobalData.setCurrentAction(EpiGimp::varAction::IMPORT_IMAGE); } },
        { sf::Keyboard::S, [this]() { if (!this->_saveFile) GlobalData.setCurrentAction(EpiGimp::varAction::SAVE_IMAGE); } },
        { sf::Keyboard::N, []() { GlobalData.setCurrentAction(EpiGimp::varAction::NEW); } },
        { sf::Keyboard::R, []() { GlobalData.setCurrentAction(EpiGimp::varAction::REPOSITION); } }
    };
    this->_shortcutCTRLShift = {
        { sf::Keyboard::S, []() { GlobalData.setCurrentAction(EpiGimp::varAction::SAVE_IMAGE_ACTIVE); } },
        { sf::Keyboard::R, []() { GlobalData.setCurrentAction(EpiGimp::varAction::WIN_RESIZE); } },
        { sf::Keyboard::O, []() { GlobalData.setCurrentAction(EpiGimp::varAction::IMPORT_IMAGE_LAYER); } },
    };

    this->_infoTexts[EpiGimp::IMPORT_IMAGE] = "Imported a new image into the project";
    this->_infoTexts[EpiGimp::IMPORT_IMAGE_LAYER] = "Imported a new image as a layer into the project";
    this->_infoTexts[EpiGimp::IMPORT_IMAGE_CURRENT] = "Imported the current image into the project";
    this->_infoTexts[EpiGimp::SAVE_IMAGE] = "Saved the current image to disk";
    this->_infoTexts[EpiGimp::UNDO] = "Action undo-ed";
    this->_infoTexts[EpiGimp::REDO] = "Action redo-ed";
    this->_infoTexts[EpiGimp::NEW] = "Created a new, empty project";
    this->_infoTexts[EpiGimp::RESIZE] = "Resized the image";
    this->_infoTexts[EpiGimp::RESIZE_CANVAS] = "Resized the canvas without changing image size";
    this->_infoTexts[EpiGimp::FLIP_HOR] = "Flipped the current layer horizontally";
    this->_infoTexts[EpiGimp::FLIP_VERT] = "Flipped the current layer vertically";
    this->_infoTexts[EpiGimp::FLIP_ALL_HOR] = "Flipped all layers horizontally";
    this->_infoTexts[EpiGimp::FLIP_ALL_VERT] = "Flipped all layers vertically";
    this->_infoTexts[EpiGimp::ROTATE_LEFT] = "Rotated the image 90 degrees counterclockwise";
    this->_infoTexts[EpiGimp::ROTATE_RIGHT] = "Rotated the image 90 degrees clockwise";
    this->_infoTexts[EpiGimp::ROTATE_FULL] = "Rotated the image by 180 degrees";
    this->_infoTexts[EpiGimp::SAVE_IMAGE_ACTIVE] = "Saved the active image layers";
    this->_infoTexts[EpiGimp::REPOSITION] = "Reseted camera";

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

        //Canvas History Check
        if (GlobalData.getAddState()) {
            this->addState(this->_layersWindow->getLayers());
            GlobalData.setAddState(false);
            this->_nextSaveState = false;
            sf::Vector2f newSize = currentLayer->getDrawZone()->getSize();
            this->_sizeWindow->setSize(newSize.x, newSize.y);
        }

        this->_canvasLayers = this->_layersWindow->getLayers();
        this->_currentLayerIndex = this->_layersWindow->getCurrentLayerIndex();

        currentLayer = this->_canvasLayers[this->_currentLayerIndex];

        this->handleShortcuts();
        this->moveCamera();

        if (!this->_window->isMouseInUI()) {
            this->_tools[GlobalData.getCurrentTool()]->action(this->_window, currentLayer->getDrawZone());
        }

        if (this->_window->isKeyPressed(sf::Keyboard::LControl) && this->_window->isKeyJustPressed(sf::Keyboard::V)) {
            std::cout << "Paste\n";
            GlobalData.setCurrentTool(EpiGimp::TOOL_SELECTION);

        }

        this->_window->drawSprite(this->_canvasBG->getSprite());
        for (auto const &e: this->_canvasLayers) {
            if (e->isVisible())
                this->_window->drawSprite(e->getDrawZone()->getSprite());
            if (currentLayer == e) {
                this->_tools[GlobalData.getCurrentTool()]->drawPreviewInCurrentCanvas(this->_window);
            }
        }

        this->handleTool();
        this->handleAction();
        this->handleFileDialog();

        this->_toolWindow->display();

        this->_colorHistoryWindow->display();

        this->_sizeWindow->display();
        this->_lightWindow->display();
        this->_contrastWindow->display();
        this->_layersWindow->display();
        this->_navBar->display();

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
    EpiGimp::varAction action = GlobalData.getCurrentAction();
    switch (action) {
        case EpiGimp::varAction::NO_ACTION: break;

        case EpiGimp::varAction::SAVE_IMAGE: this->_saveFile = true; break;
        case EpiGimp::varAction::IMPORT_IMAGE: this->_loadFile = true; break;
        case EpiGimp::varAction::IMPORT_IMAGE_CURRENT: this->_loadFile = true; this->_loadOnLayer = true; break;
        case EpiGimp::varAction::IMPORT_IMAGE_LAYER: this->_loadFile = true; this->_loadAsLayer = true; break;
        case EpiGimp::varAction::UNDO: this->undo(); break;
        case EpiGimp::varAction::REDO: this->redo(); break;
        case EpiGimp::varAction::NEW: this->resetCanvas(); break;
        case EpiGimp::varAction::RESIZE: this->reposition(); this->addState(this->_canvasLayers); break;
        case EpiGimp::varAction::RESIZE_CANVAS: this->reposition(); this->addState(this->_canvasLayers); break;
        case EpiGimp::varAction::FLIP_HOR: this->flipCurrent(false); break;
        case EpiGimp::varAction::FLIP_VERT: this->flipCurrent(true); break;
        case EpiGimp::varAction::FLIP_ALL_HOR: this->flipAll(false); break;
        case EpiGimp::varAction::FLIP_ALL_VERT: this->flipAll(true); break;
        case EpiGimp::varAction::ROTATE_LEFT: this->rotateCanvas(90); break;
        case EpiGimp::varAction::ROTATE_RIGHT: this->rotateCanvas(270); break;
        case EpiGimp::varAction::ROTATE_FULL: this->rotateCanvas(180); break;
        case EpiGimp::varAction::SAVE_IMAGE_ACTIVE: this->_saveFile = true; this->_saveActiveOnly = true; break;
        case EpiGimp::varAction::REPOSITION:
            this->_window->getCamera()->setPosition(GlobalData.getCanvasSize() * 0.5f);
            this->_window->getCamera()->resetZoom();
            break;
        case EpiGimp::varAction::LIGHT: this->_canvasLayers[this->_currentLayerIndex]->getDrawZone()->changeLighting(this->_lightWindow->getValue());
                                        this->addState(this->_canvasLayers); break;
        case EpiGimp::varAction::INVERT: this->_canvasLayers[this->_currentLayerIndex]->getDrawZone()->invert();
                                            this->addState(this->_canvasLayers); break;
        case EpiGimp::varAction::CONTRAST: this->_canvasLayers[this->_currentLayerIndex]->getDrawZone()->changeContrast(this->_contrastWindow->getValue());
                                        this->addState(this->_canvasLayers); break;
        case EpiGimp::varAction::WIN_RESIZE: this->_sizeWindow->setVisible(true); break;
        case EpiGimp::varAction::WIN_LIGHT: this->_lightWindow->setValue(0); this->_lightWindow->setVisible(true); break;
        case EpiGimp::varAction::WIN_CONTRAST: this->_contrastWindow->setValue(0); this->_contrastWindow->setVisible(true); break;
    }
    if (action != EpiGimp::varAction::NO_ACTION && this->_infoTexts.count(action) != 0) {
        this->_navBar->setDisplayedText(this->_infoTexts[action]);
    }
    GlobalData.setCurrentAction(EpiGimp::varAction::NO_ACTION);
}

void EpiGimp::Core::handleFileDialog()
{
    if (this->_loadFile) {
        if (!this->_loadAsLayer && system("zenity --question --text=\"Are you sure you want to open a new file?\n\nCurrent progress will be lost if you didn't save\"")) {
            this->_loadFile = false; this->_loadAsLayer = false; this->_loadOnLayer = false;
            return;
        }
        // this->_guiCore->startLoadFile();
        this->openFile();
        return;
    }
    if (this->_saveFile) {
        // this->_guiCore->startSaveFile();
        this->saveFile();
    }
}

void EpiGimp::Core::handleShortcuts()
{
    if (this->_window->isKeyPressed(sf::Keyboard::LControl)) {
        for (const auto& [key, action] : _shortcutCTRL)
            if (this->_window->isKeyJustPressed(key))
                action();

        if (this->_window->isKeyPressed(sf::Keyboard::LShift)) {
            for (const auto& [key, action] : _shortcutCTRLShift)
                if (this->_window->isKeyJustPressed(key))
                    action();
        }
    }
}

void EpiGimp::Core::resetCanvas()
{
    if (GlobalData.getCurrentAction() == EpiGimp::NEW) {
        if (system("zenity --question --text=\"Are you sure you want to reset the canvas?\n\nCurrent progress will be lost if you didn't save\" --width=400 --height=200")) {
            return;
        }
    }
    this->_canvasLayers.clear();
    this->_canvasLayers.push_back(std::make_shared<EpiGimp::Layer>("Layer 1", 400, 300));
    GlobalData.setCanvasSize(400, 300);
    this->_currentLayerIndex = 0;
    this->_layersWindow = std::make_unique<GUI::LayersWin>(this->_canvasLayers);
    this->_window->getCamera()->resetZoom();
    this->_window->getCamera()->setPosition(GlobalData.getCanvasSize().x / 2, GlobalData.getCanvasSize().y / 2);
    this->_canvasHistory.clear();
    this->addState(this->_canvasLayers);
    this->_currentStateIndex = 0;
}

void EpiGimp::Core::saveFile()
{
    // std::string filepath = this->_guiCore->getFilePath();
    std::string filepath = this->getFilePathSave();
    if (filepath == "") {
        this->_saveFile = false;
        this->_saveActiveOnly = false;
        return;
    }
    Graphic::DrawZone saved(GlobalData.getCanvasSize().x, GlobalData.getCanvasSize().y);
    for (auto const &e: this->_canvasLayers) {
        if (this->_saveActiveOnly) {
            if (e->isVisible())
                saved.addSprite(e->getDrawZone()->getSprite());
        } else {
            saved.addSprite(e->getDrawZone()->getSprite());
        }
    }
    saved.saveToFile(filepath);
    this->_saveFile = false;
    this->_saveActiveOnly = false;
}

void EpiGimp::Core::openFile()
{
    // std::string filepath = this->_guiCore->getFilePath();
    std::string filepath = this->getFilePathLoad();
    if (filepath == "") {
        this->_loadFile = false;
        return;
    }
    if (this->_loadAsLayer) {
        this->_guiCore->resetFilePath();
        this->_layersWindow->addLayer();
        this->_canvasLayers = this->_layersWindow->getLayers();
        this->_currentLayerIndex = this->_layersWindow->getCurrentLayerIndex();
        sf::Texture fileText;
        if (fileText.loadFromFile(filepath)) {
            this->_canvasLayers[this->_currentLayerIndex]->getDrawZone()->setSize(fileText.getSize().x, fileText.getSize().y);
            this->_canvasLayers[this->_currentLayerIndex]->getDrawZone()->addFromFile(filepath);
        }
        sf::Vector2f imageSize = this->_canvasLayers[this->_currentLayerIndex]->getDrawZone()->getSize();
        imageSize.x = std::max(imageSize.x, GlobalData.getCanvasSize().x);
        imageSize.y = std::max(imageSize.y, GlobalData.getCanvasSize().y);
        GlobalData.setCanvasSize(imageSize.x, imageSize.y);
        for (const auto& layer : this->_canvasLayers) {
            layer->getDrawZone()->setSize(imageSize, false);
        }
        this->addState(this->_canvasLayers);
        this->reposition();
    } else {
        if (!this->_loadOnLayer) {
            this->resetCanvas();
        }
        this->_guiCore->resetFilePath();
        if (this->_loadOnLayer && this->_canvasLayers.size() > 1) {
            this->_canvasLayers[this->_currentLayerIndex]->getDrawZone()->addFromFile(filepath);
        } else {
            this->_canvasLayers[this->_currentLayerIndex]->getDrawZone()->setFromFile(filepath);
        }
        // this->_canvasHistory.clear();
        this->addState(this->_canvasLayers);
        this->reposition();
    }
    this->_loadFile = false;
    this->_loadOnLayer = false;
    this->_loadAsLayer = false;
}

void EpiGimp::Core::addState(const std::vector<std::shared_ptr<EpiGimp::Layer>>& layers)
{
    if (this->_currentStateIndex + 1 < this->_canvasHistory.size()) {
        std::cout << "Override history at " << this->_currentStateIndex + 1 << std::endl;
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
    std::cout << "New State at: " << this->_canvasHistory.size() << std::endl;
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
            GlobalData.setCanvasSize(size.x, size.y);
        }
        std::cout << "Undo at: " << this->_currentStateIndex + 1 << " out of "<< this->_canvasHistory.size() << std::endl;
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
            GlobalData.setCanvasSize(size.x, size.y);
        }
        std::cout << "Redo at: " << this->_currentStateIndex + 1 << " out of "<< this->_canvasHistory.size() << std::endl;
    } else {
        std::cout << "No more redos available." << std::endl;
    }
}

void EpiGimp::Core::reposition()
{
    for (auto const &e: this->_canvasLayers) {
        e->getDrawZone()->setSize(GlobalData.getCanvasSize().x, GlobalData.getCanvasSize().y, GlobalData.getCurrentAction() == EpiGimp::varAction::RESIZE);
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

void EpiGimp::Core::rotateCanvas(float angle)
{
    for (auto const &e: this->_canvasLayers) {
        e->getDrawZone()->rotate(angle);
    }
    this->_canvasBG->rotate(angle);
    GlobalData.setCanvasSize(this->_canvasBG->getSize().x, this->_canvasBG->getSize().y);
    this->_canvasBG->drawCheckeredBackground();
    this->_sizeWindow->setSize(this->_canvasBG->getSize().x, this->_canvasBG->getSize().y);
    this->addState(this->_canvasLayers);
}

std::string EpiGimp::Core::getFilePathLoad()
{
    std::string command = "zenity --file-selection --file-filter='PNG files | *.png' --file-filter='JPG files | *.jpg' --file-filter='Bitmap files | *.bmp' --title='Select a file'";
    std::string res = "";

    // Open a pipe to execute the command and capture the output
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to run Zenity command" << std::endl;
        return res;
    }

    // Read the selected file path from Zenity output
    char buffer[512];
    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        // Remove the newline character at the end of the string
        buffer[strcspn(buffer, "\n")] = '\0';
        res = std::string(buffer);
        std::cout << res << std::endl;
    }

    fclose(pipe);
    return res;
}

std::string EpiGimp::Core::getFilePathSave()
{
    std::string command = "zenity --file-selection --save --file-filter='PNG files | *.png' --file-filter='JPG files | *.jpg' --file-filter='Bitmap files | *.bmp' --title='Save As'";

    // Open a pipe to execute the command and capture the output
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to run Zenity command" << std::endl;
        return "";
    }

    // Read the selected file path from Zenity output
    char buffer[512];
    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        // Remove the newline character at the end of the string
        buffer[strcspn(buffer, "\n")] = '\0';
        fclose(pipe);
        return std::string(buffer);
    }

    fclose(pipe);
    return "";
}
