/*
** ProtoPaint
** File description:
** Core
*/

#include "ContrastWin.hpp"

GUI::ContrastWin::ContrastWin() :
    AGUIWindow("Ajust Contrast")
{
    this->_isVisible = false;
    this->_f = 0;
}

void GUI::ContrastWin::content()
{
    ImGui::SliderFloat("Factor", &this->_f, -10, 10);
    ImGui::Spacing();
    if (ImGui::Button("Cancel")) {
        this->_isVisible = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Apply")) {
        GlobalData.setCurrentAction(ProtoPaint::varAction::CONTRAST);
        this->_isVisible = false;
    }
}

void GUI::ContrastWin::setValue(float f)
{
    this->_f = f;
}

const float &GUI::ContrastWin::getValue()
{
    return this->_f;
}
