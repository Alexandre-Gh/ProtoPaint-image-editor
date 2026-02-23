/*
** ProtoPaint
** File description:
** Core
*/

#include "ShadowWin.hpp"

GUI::ShadowWin::ShadowWin() :
    AGUIWindow("Add Shadow")
{
    this->_isVisible = false;
    this->_f = 0;
}

void GUI::ShadowWin::content()
{
    ImGui::SliderFloat("Light direction", &this->_f, -1, 1);
    ImGui::Spacing();
    if (ImGui::Button("Cancel")) {
        this->_isVisible = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Apply")) {
        GlobalData.setCurrentAction(ProtoPaint::varAction::SHADOW);
        this->_isVisible = false;
    }
}

void GUI::ShadowWin::setValue(float f)
{
    this->_f = f;
}

const float &GUI::ShadowWin::getValue()
{
    return this->_f;
}
