/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "FunnyHammerWin.hpp"

GUI::FunnyHammerWin::FunnyHammerWin() :
    AGUIWindow("Funny Hammer")
{

}

void GUI::FunnyHammerWin::content()
{
    ImTextureID texture_id;
    ImGuiStyle colorButton = ImGui::GetStyle();

    ImGui::SetWindowCollapsed(false);

    if (ImGui::SliderInt("Size", &this->_size, 10, 40)) {
        GlobalData.setCurrentToolValue("size", this->_size);
    }
    if (ImGui::Checkbox("Random Rotation", &this->_rotate)) {
        GlobalData.setCurrentToolValue("rotate", this->_rotate);
    }
}