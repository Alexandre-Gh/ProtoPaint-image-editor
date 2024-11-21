/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "NavBar.hpp"

GUI::NavBar::NavBar() :
    AGUIWindow("Navigation")
{
    this->_isNavBar = true;
}

void GUI::NavBar::content()
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("New")) GlobalData.setCurrentAction(EpiGimp::NEW);
        if (ImGui::MenuItem("Open", "Ctrl+O")) GlobalData.setCurrentAction(EpiGimp::IMPORT_IMAGE);
        if (ImGui::MenuItem("Open as layer", "Ctrl+Shift+O")) GlobalData.setCurrentAction(EpiGimp::IMPORT_IMAGE_LAYER);
        if (ImGui::MenuItem("Open on current layer")) GlobalData.setCurrentAction(EpiGimp::IMPORT_IMAGE_CURRENT);
        if (ImGui::MenuItem("Save", "Ctrl+S")) GlobalData.setCurrentAction(EpiGimp::SAVE_IMAGE);
        if (ImGui::MenuItem("Save Active Layers", "Ctrl+Shift+S")) GlobalData.setCurrentAction(EpiGimp::SAVE_IMAGE_ACTIVE);
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit"))
    {
        if (ImGui::MenuItem("Undo", "Ctrl+Z")) GlobalData.setCurrentAction(EpiGimp::UNDO);
        if (ImGui::MenuItem("Redo", "Ctrl+Y")) GlobalData.setCurrentAction(EpiGimp::REDO);
        if (ImGui::MenuItem("Resize Canvas")) GlobalData.setCurrentAction(EpiGimp::WIN_RESIZE);
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Image"))
    {
        if (ImGui::MenuItem("Flip Horizontally")) GlobalData.setCurrentAction(EpiGimp::FLIP_HOR);
        if (ImGui::MenuItem("Flip Vertically")) GlobalData.setCurrentAction(EpiGimp::FLIP_VERT);
        ImGui::Separator();
        if (ImGui::MenuItem("Flip All Hor.")) GlobalData.setCurrentAction(EpiGimp::FLIP_ALL_HOR);
        if (ImGui::MenuItem("Flip All Vert.")) GlobalData.setCurrentAction(EpiGimp::FLIP_ALL_VERT);
        ImGui::Separator();
        if (ImGui::MenuItem("Rotate 90° Left")) GlobalData.setCurrentAction(EpiGimp::ROTATE_LEFT);
        if (ImGui::MenuItem("Rotate 90° Right")) GlobalData.setCurrentAction(EpiGimp::ROTATE_RIGHT);
        if (ImGui::MenuItem("Rotate 180°")) GlobalData.setCurrentAction(EpiGimp::ROTATE_FULL);
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("View"))
    {
        if (ImGui::MenuItem("Reset View", "Ctrl+R")) GlobalData.setCurrentAction(EpiGimp::REPOSITION);
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Options"))
    {
        if (ImGui::MenuItem("Dark Mode", "", &this->_darkMode)) {
            if (this->_darkMode) {
                ImGui::StyleColorsDark();
            } else {
                ImGui::StyleColorsLight();
            }
        }
        ImGui::EndMenu();
    }
    ImGui::Separator();
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), this->_displayedText.c_str());

}

void GUI::NavBar::setDisplayedText(std::string text)
{
    this->_displayedText = text;
}
