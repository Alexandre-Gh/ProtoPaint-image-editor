/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "LineWin.hpp"

GUI::LineWin::LineWin() :
    AGUIWindow("Line")
{

}

void GUI::LineWin::content()
{
    ImTextureID texture_id;
    ImGuiStyle colorButton = ImGui::GetStyle();

    ImGui::SetWindowCollapsed(false);
    if (ImGui::SliderInt("Thickness", &this->_thickness, 1, 10)) {
        GlobalData.setCurrentToolValue("thickness", this->_thickness);
    }
    if (ImGui::Checkbox("Rounded Edges", &this->_filled)) {
        GlobalData.setCurrentToolValue("rounded", this->_filled);
    }
}