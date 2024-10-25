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
    this->_x = std::max(0, std::min(this->_x, 3000));
    this->_y = std::max(0, std::min(this->_y, 3000));
    if (ImGui::Button("Resize")) {
        if (this->_x == GlobalData.getCanvasSize().x && this->_y == GlobalData.getCanvasSize().y) {
            return;
        }
        GlobalData.setCanvasSize(_x, _y);
        GlobalData.setCurrentAction(EpiGimp::varAction::RESIZE);
    }
}

void GUI::SizeWin::setSize(int x, int y)
{
    this->_x = x;
    this->_y = y;
}

const sf::Vector2f &GUI::SizeWin::getSize()
{
    this->_ret.x = this->_x;
    this->_ret.y = this->_y;
    return this->_ret;
}
