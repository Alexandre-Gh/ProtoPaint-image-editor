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
    ImGui::SliderInt("Brush Size", 0, 1, 50);

}