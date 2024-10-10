/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "BrushWin.hpp"

GUI::BrushWin::BrushWin() :
    AGUIWindow("Brush")
{
    this->_items.push_back("Circle");
    this->_items.push_back("Square");
}

void GUI::BrushWin::content()
{
    ImTextureID texture_id;
    ImGuiStyle colorButton = ImGui::GetStyle();

    ImGui::SetWindowCollapsed(false);
    if (ImGui::SliderInt("Brush Size", &this->_size, 1, 100)) {
        GlobalData.setCurrentToolValue("size", this->_size);
    }
    if (ImGui::Checkbox("Gradient", &this->_gradient)) {
        GlobalData.setCurrentToolValue("gradient", this->_gradient);
    }
    if (ImGui::Checkbox("Rainbow", &this->_rainbow)) {
        GlobalData.setCurrentToolValue("rainbow", this->_rainbow);
    }

    // if (ImGui::BeginCombo("Select an option", this->_items[this->_currentToolIndex].c_str())) {
    //     for (int i = 0; i < this->_items.size(); i++) {
    //         bool isSelected = (this->_currentToolIndex == i);
    //         if (ImGui::Selectable(this->_items[i].c_str(), isSelected)) {
    //             this->_currentToolIndex = i; // Update the current item
    //             GlobalData.setCurrentToolValue("brush", i);
    //         }
    //         if (isSelected) {
    //             ImGui::SetItemDefaultFocus(); // Focus on the selected item
    //         }
    //     }
    //     ImGui::EndCombo();
    // }

}