/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "LayersWin.hpp"

GUI::LayersWin::LayersWin(std::vector<std::shared_ptr<EpiGimp::Layer>> layers) :
    AGUIWindow("Layer Manager")
{
    this->_layers = layers;
    this->_currentLayerIndex = 0;
}

void GUI::LayersWin::content()
{
    std::vector<size_t> layersToRemove;
    bool toggle;

    if (ImGui::Button("Add layer")) {
        this->addLayer();
    }
    if (this->_layers.size() > 1) {
        ImGui::SameLine();
        if (ImGui::Button("Remove current Layer")) {
            layersToRemove.push_back(this->_currentLayerIndex);
            if (this->_currentLayerIndex != 0) {
                this->_currentLayerIndex -= 1;
            }
        }
    }

    ImGui::BeginChild("Layers", ImVec2(0, 200), true, ImGuiWindowFlags_AlwaysUseWindowPadding);

    for (size_t i = 0; i < this->_layers.size(); ++i) {
        std::shared_ptr<EpiGimp::Layer>& layer = this->_layers[i];

        ImGui::PushID(i);

        toggle = layer->isVisible();
        ImGui::Checkbox("##visible", &toggle);
        layer->setVisible(toggle);

        ImGui::SameLine();
        if (this->_currentLayerIndex != i) {
            ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        } else {
            ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 1.0f, 0.8f);
        }
        if (ImGui::ImageButton("##Image", layer->getDrawZone()->getSprite(), sf::Vector2f(60, 30))) {
            this->_currentLayerIndex = i;
        }
        ImGui::SameLine();
        ImGui::Text("%s", layer->getName().c_str());

        if (this->_currentLayerIndex == i) {
            ImGui::SameLine();
            if (i > 0 && ImGui::Button("^")) {
                std::swap(this->_layers[i - 1], this->_layers[i]);
                this->_currentLayerIndex -= 1;
            }
            ImGui::SameLine();
            if (i < this->_layers.size() - 1 && ImGui::Button("v")) {
                std::swap(this->_layers[i], this->_layers[i + 1]);
                this->_currentLayerIndex += 1;
            }
        }
        ImGui::PopID();
    }
    ImGui::EndChild();

    for (size_t index : layersToRemove) {
        this->_layers.erase(this->_layers.begin() + index);
    }
}

std::vector<std::shared_ptr<EpiGimp::Layer>> GUI::LayersWin::getLayers()
{
    return this->_layers;
}

const unsigned int &GUI::LayersWin::getCurrentLayerIndex()
{
    return this->_currentLayerIndex;
}

void GUI::LayersWin::addLayer()
{
    std::string name = "Layer " + std::to_string(this->_layers.size() + 1);
    sf::Vector2f size = GlobalData.getCanvasSize();
    this->_layers.push_back(std::make_shared<EpiGimp::Layer>(name, size.x, size.y));
    this->_currentLayerIndex = this->_layers.size() - 1;
}
