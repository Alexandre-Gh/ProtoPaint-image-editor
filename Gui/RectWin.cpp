/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "RectWin.hpp"

GUI::RectWin::RectWin() :
    AGUIWindow("Rect")
{

}

void GUI::RectWin::content()
{
    ImTextureID texture_id;
    ImGuiStyle colorButton = ImGui::GetStyle();

    ImGui::SetWindowCollapsed(false);
    if (ImGui::SliderInt("Thickness", &this->_thickness, 1, 10)) {
        GlobalData.setCurrentToolValue("thickness", this->_thickness);
    }
    if (ImGui::Checkbox("Filled", &this->_filled)) {
        GlobalData.setCurrentToolValue("filled", this->_filled);
    }
}