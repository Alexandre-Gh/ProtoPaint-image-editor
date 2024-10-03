/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "SizeWin.hpp"

GUI::SizeWin::SizeWin() :
    AGUIWindow("Canvas Size")
{
    this->_x = GlobalData.getCanvasSize().x;
    this->_y = GlobalData.getCanvasSize().y;
}

void GUI::SizeWin::content()
{
    ImGui::InputInt("X", &_x);
    ImGui::InputInt("Y", &_y);
    if (ImGui::Button("Resize")) {
        GlobalData.setCanvasSize(_x, _y);
    }
}