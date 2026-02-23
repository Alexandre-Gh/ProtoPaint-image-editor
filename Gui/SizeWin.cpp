/*
** ProtoPaint
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
        this->_x = std::max(1, this->_x);
        this->_y = std::max(1, this->_y);
    }
    ImGui::Spacing();
    ImGui::Checkbox("Resize Canvas Content", &this->_resizeContent);
    if (ImGui::Button("Cancel")) {
        this->_isVisible = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Resize")) {
        sf::Vector2f size = GlobalData.getCanvasSize();
        if (!this->_sizePercent) {
            if (size.x == this->_x && size.y == this->_y) {
                this->_isVisible = false;
                this->_percent = 100;
                return;
            }
        }
        if (this->_sizePercent) {
            if (this->_percent == 100) {
                this->_isVisible = false;
                return;
            }
            this->_x = int(size.x * (this->_percent * 0.01f));
            this->_y = int(size.y * (this->_percent * 0.01f));
        }
        this->_x = std::max(1, this->_x);
        this->_y = std::max(1, this->_y);
        GlobalData.setCanvasSize(_x, _y);
        this->_percent = 100;
        GlobalData.setCurrentAction(this->_resizeContent ? ProtoPaint::varAction::RESIZE : ProtoPaint::varAction::RESIZE_CANVAS);
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
