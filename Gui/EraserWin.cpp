/*
** ProtoPaint
** File description:
** Core
*/

#include "EraserWin.hpp"

GUI::EraserWin::EraserWin() :
    AGUIWindow("Eraser")
{
    this->_items.push_back("Circle");
    this->_items.push_back("Square");
}

void GUI::EraserWin::content()
{
    ImTextureID texture_id;
    ImGuiStyle colorButton = ImGui::GetStyle();

    ImGui::SetWindowCollapsed(false);
    if (ImGui::BeginCombo("Brush", this->_items[this->_currentToolIndex].c_str())) {
        for (int i = 0; i < this->_items.size(); i++) {
            bool isSelected = (this->_currentToolIndex == i);
            if (ImGui::Selectable(this->_items[i].c_str(), isSelected)) {
                this->_currentToolIndex = i; // Update the current item
                GlobalData.setCurrentToolValue("brush", i);
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus(); // Focus on the selected item
            }
        }
        ImGui::EndCombo();
    }
    if (ImGui::SliderInt("Size", &this->_size, 1, 100)) {
        GlobalData.setCurrentToolValue("size", this->_size);
    }

}