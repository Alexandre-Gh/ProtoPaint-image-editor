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
    this->isNavBar = true;
}

void GUI::NavBar::content()
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("New")) GlobalData.setCurrentAction(EpiGimp::NEW);
        if (ImGui::MenuItem("Open", "Ctrl+O")) GlobalData.setCurrentAction(EpiGimp::IMPORT_IMAGE);
        if (ImGui::MenuItem("Save", "Ctrl+S")) GlobalData.setCurrentAction(EpiGimp::SAVE_IMAGE);
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit"))
    {
        if (ImGui::MenuItem("Undo", "Ctrl+Z")) GlobalData.setCurrentAction(EpiGimp::UNDO);
        if (ImGui::MenuItem("Redo", "Ctrl+Y")) GlobalData.setCurrentAction(EpiGimp::REDO);
        ImGui::EndMenu();
    }

}