/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "SprayWin.hpp"

GUI::SprayWin::SprayWin() :
    AGUIWindow("Spray")
{

}

void GUI::SprayWin::content()
{
    ImTextureID texture_id;
    ImGuiStyle colorButton = ImGui::GetStyle();

    ImGui::SetWindowCollapsed(false);

    if (ImGui::SliderInt("Size", &this->_size, 2, 100)) {
        GlobalData.setCurrentToolValue("size", this->_size);
    }
    if (ImGui::Checkbox("Rainbow", &this->_rainbow)) {
        GlobalData.setCurrentToolValue("rainbow", this->_rainbow);
    }
}