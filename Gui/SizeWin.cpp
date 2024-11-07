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
    this->_isVisible = false;
    this->_x = GlobalData.getCanvasSize().x;
    this->_y = GlobalData.getCanvasSize().y;
    this->_resizeContent = true;
    this->_sizePercent = false;
    this->_percent = 100;
}

void GUI::SizeWin::content()
{
    ImGui::Checkbox("Resize with percentage", &this->_sizePercent);
    ImGui::Spacing();
    if (this->_sizePercent) {
        ImGui::InputInt("%", &_percent);
        ImGui::SameLine();
        this->_percent = std::max(1, std::min(this->_percent, 3000));
    } else {
        ImGui::InputInt("X", &_x);
        ImGui::InputInt("Y", &_y);
        this->_x = std::max(0, std::min(this->_x, 3000));
        this->_y = std::max(0, std::min(this->_y, 3000));
    }
    ImGui::Spacing();
    ImGui::Checkbox("Resize Canvas Content", &this->_resizeContent);
    if (ImGui::Button("Cancel")) {
        this->_isVisible = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Resize")) {
        if (this->_sizePercent) {
            sf::Vector2f size = GlobalData.getCanvasSize();
            GlobalData.setCanvasSize(size.x * (this->_percent / 100), size.y * (this->_percent / 100));
        } else {
            GlobalData.setCanvasSize(_x, _y);
        }
        GlobalData.setCurrentAction(this->_resizeContent ? EpiGimp::varAction::RESIZE : EpiGimp::varAction::RESIZE_CANVAS);
        this->_isVisible = false;
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
