/*
** ProtoPaint
** File description:
** Core
*/

#include "LayersWin.hpp"

GUI::LayersWin::LayersWin(std::vector<std::shared_ptr<ProtoPaint::Layer>> layers) :
    AGUIWindow("Layer Manager")
{
    this->_layers = layers;
    this->_currentLayerIndex = 0;
}

void GUI::LayersWin::content()
{
    std::vector<size_t> layersToRemove;
    bool toggle;

    if (ImGui::Button("Add")) {
        this->addLayer();
        GlobalData.setAddState(true);
    }
    if (this->_layers.size() > 1) {
        ImGui::SameLine();
        if (ImGui::Button("Remove")) {
            layersToRemove.push_back(this->_currentLayerIndex);
            if (this->_currentLayerIndex != 0) {
                this->_currentLayerIndex -= 1;
            }
            GlobalData.setAddState(true);
        }
        if (this->_currentLayerIndex < this->_layers.size() - 1) {
            ImGui::SameLine();
            if (ImGui::Button("Fuse Bottom")) {
                this->_layers[this->_currentLayerIndex + 1]->getDrawZone()->addSprite(this->_layers[this->_currentLayerIndex]->getDrawZone()->getSprite());
                layersToRemove.push_back(this->_currentLayerIndex);
                // if (this->_currentLayerIndex != 0) {
                //     this->_currentLayerIndex += 1;
                // }
                GlobalData.setAddState(true);
            }
        }
        if (this->_currentLayerIndex > 0) {
            ImGui::SameLine();
            if (ImGui::Button("Fuse Top")) {
                this->_layers[this->_currentLayerIndex - 1]->getDrawZone()->addSprite(this->_layers[this->_currentLayerIndex]->getDrawZone()->getSprite());
                layersToRemove.push_back(this->_currentLayerIndex);
                if (this->_currentLayerIndex != 0) {
                    this->_currentLayerIndex -= 1;
                }
                GlobalData.setAddState(true);
            }
        }
    }

    ImGui::BeginChild("Layers", ImVec2(0, 200), true, ImGuiWindowFlags_AlwaysUseWindowPadding);

    for (size_t i = 0; i < this->_layers.size(); ++i) {
        std::shared_ptr<ProtoPaint::Layer>& layer = this->_layers[i];

        ImGui::PushID(i);

        toggle = layer->isVisible();
        if (ImGui::Checkbox("##visible", &toggle)) {
            GlobalData.setAddState(true);
        }
        layer->setVisible(toggle);

        ImGui::SameLine();
        if (this->_currentLayerIndex != i) {
            ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        } else {
            ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 1.0f, 0.8f);
        }
        sf::RenderTexture res;
        
        if (ImGui::ImageButton("##Image", layer->getDrawZone()->getRenderTexture(), sf::Vector2f(60, 30))) {
            this->_currentLayerIndex = i;
        }
        ImGui::SameLine();
        char buffer[32];
        strcpy(buffer, this->_layers[i]->getName().c_str());
        ImGui::SetNextItemWidth(100);
        if (ImGui::InputText("##", buffer, 32, ImGuiInputTextFlags_EnterReturnsTrue)) {
            GlobalData.setAddState(true);
            this->_layers[i]->setName(buffer);
        }

        if (this->_currentLayerIndex == i) {
            ImGui::SameLine();
            if (i > 0 && ImGui::Button("^")) {
                std::swap(this->_layers[i - 1], this->_layers[i]);
                this->_currentLayerIndex -= 1;
                GlobalData.setAddState(true);
            }
            ImGui::SameLine();
            if (i < this->_layers.size() - 1 && ImGui::Button("v")) {
                std::swap(this->_layers[i], this->_layers[i + 1]);
                this->_currentLayerIndex += 1;
                GlobalData.setAddState(true);
            }
        }
        ImGui::PopID();
    }
    ImGui::EndChild();

    for (size_t index : layersToRemove) {
        this->_layers.erase(this->_layers.begin() + index);
    }
}

std::vector<std::shared_ptr<ProtoPaint::Layer>> GUI::LayersWin::getLayers()
{
    return this->_layers;
}

void GUI::LayersWin::setLayers(std::vector<std::shared_ptr<ProtoPaint::Layer>> layers, unsigned int index)
{
    this->_layers = layers;
    this->_currentLayerIndex = index;
    if (this->_currentLayerIndex < 0) {
        this->_currentLayerIndex = 0;
    }
    if (this->_currentLayerIndex >= this->_layers.size()) {
        this->_currentLayerIndex = this->_layers.size() - 1;
    }
}

const unsigned int &GUI::LayersWin::getCurrentLayerIndex()
{
    return this->_currentLayerIndex;
}

void GUI::LayersWin::addLayer()
{
    int oldPos = this->_currentLayerIndex;
    std::string name = "Layer " + std::to_string(this->_layers.size() + 1);
    sf::Vector2f size = GlobalData.getCanvasSize();
    this->_layers.push_back(std::make_shared<ProtoPaint::Layer>(name, size.x, size.y));
    this->_currentLayerIndex = this->_layers.size() - 1;
    this->_layers[this->_currentLayerIndex]->getDrawZone()->setPosition(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        sf::Sprite s = this->_layers[oldPos]->getDrawZone()->getSprite();
        this->_layers[this->_currentLayerIndex]->getDrawZone()->setDraw(s);
    }
}
