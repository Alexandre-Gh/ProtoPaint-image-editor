/*
** ProtoPaint
** File description:
** Core
*/

#include "LightWin.hpp"

GUI::LightWin::LightWin() :
    AGUIWindow("Ajust Lighting")
{
    this->_isVisible = false;
    this->_f = 0;
}

void GUI::LightWin::content()
{
    ImGui::SliderFloat("Factor", &this->_f, -10, 10);
    ImGui::Spacing();
    if (ImGui::Button("Cancel")) {
        this->_isVisible = false;
    }
    ImGui::SameLine();
    std::string info = this->_f < 0 ? "Darken" : "Brighten";
    if (ImGui::Button(info.c_str())) {
        GlobalData.setCurrentAction(ProtoPaint::varAction::LIGHT);
        this->_isVisible = false;
    }
}

void GUI::LightWin::setValue(float f)
{
    this->_f = f;
}

const float &GUI::LightWin::getValue()
{
    return this->_f;
}
