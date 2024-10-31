/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "TextWin.hpp"

GUI::TextWin::TextWin() :
    AGUIWindow("Text")
{
    this->_fonts = GlobalData.getFonts();
    this->_styles.push_back("Regular");
    this->_styles.push_back("Bold");
    this->_styles.push_back("Italic");
    this->_styles.push_back("Underline");
    this->_styles.push_back("Crossed");
}

void GUI::TextWin::content()
{
    ImTextureID texture_id;
    ImGuiStyle colorButton = ImGui::GetStyle();

    ImGui::SetWindowCollapsed(false);
    if (ImGui::BeginCombo("Font", this->_fonts[this->_currentFontIndex].c_str())) {
        for (int i = 0; i < this->_fonts.size(); i++) {
            bool isSelected = (this->_currentFontIndex == i);
            if (ImGui::Selectable(this->_fonts[i].c_str(), isSelected)) {
                this->_currentFontIndex = i; // Update the current item
                GlobalData.setCurrentToolValue("font", i);
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus(); // Focus on the selected item
            }
        }
        ImGui::EndCombo();
    }
    if (ImGui::BeginCombo("Style", this->_styles[this->_currentStyleIndex].c_str())) {
        for (int i = 0; i < this->_styles.size(); i++) {
            bool isSelected = (this->_currentStyleIndex == i);
            if (ImGui::Selectable(this->_styles[i].c_str(), isSelected)) {
                this->_currentStyleIndex = i; // Update the current item
                GlobalData.setCurrentToolValue("style", i);
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus(); // Focus on the selected item
            }
        }
        ImGui::EndCombo();
    }
    if (ImGui::SliderInt("Size", &this->_size, 2, 100)) {
        GlobalData.setCurrentToolValue("size", this->_size);
    }
    
}