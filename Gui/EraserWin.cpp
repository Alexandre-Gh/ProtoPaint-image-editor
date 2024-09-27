/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "EraserWin.hpp"

GUI::EraserWin::EraserWin() :
    AGUIWindow("Eraser")
{
    
}

void GUI::EraserWin::content()
{
    ImTextureID texture_id;
    ImGuiStyle colorButton = ImGui::GetStyle();

    ImGui::SetWindowCollapsed(false);
    if (ImGui::SliderInt("Brush Size", &this->_size, 1, 50)) {
        GlobalData.setCurrentToolValue("size", this->_size);
    }

}