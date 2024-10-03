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

}