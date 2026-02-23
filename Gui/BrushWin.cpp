/*
** ProtoPaint
** File description:
** Core
*/

#include "BrushWin.hpp"

GUI::BrushWin::BrushWin() :
    AGUIWindow("Brush")
{
    this->_items.push_back("Circle");
    this->_items.push_back("Square");
    this->_items.push_back("Line");
    this->_items.push_back("Reverse Line");
}

void GUI::BrushWin::content()
{
    ImTextureID texture_id;
    ImGuiStyle colorButton = ImGui::GetStyle();

    ImGui::SetWindowCollapsed(false);
    if (ImGui::BeginCombo("Brush", this->_items[this->_currentToolIndex].c_str())) {
        for (int i = 0; i < this->_items.size(); i++) {
            bool isSelected = (this->_currentToolIndex == i);
            if (ImGui::Selectable(this->_items[i].c_str(), isSelected)) {
                this->_currentToolIndex = i; // Update the current item
                GlobalData.setCurrentToolValue("brush", i);
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus(); // Focus on the selected item
            }
        }
        ImGui::EndCombo();
    }
    if (ImGui::SliderInt("Size", &this->_size, 2, 100)) {
        GlobalData.setCurrentToolValue("size", this->_size);
    }
    if (ImGui::Checkbox("Gradient", &this->_gradient)) {
        GlobalData.setCurrentToolValue("gradient", this->_gradient);
    }
    if (ImGui::Checkbox("Rainbow", &this->_rainbow)) {
        GlobalData.setCurrentToolValue("rainbow", this->_rainbow);
    }
    if (ImGui::Checkbox("Simetry X", &this->_symetricalHor)) {
        GlobalData.setCurrentToolValue("symetricalHor", this->_symetricalHor);
    }
    if (ImGui::Checkbox("Simetry Y", &this->_symetricalVert)) {
        GlobalData.setCurrentToolValue("symetricalVert", this->_symetricalVert);
    }
}