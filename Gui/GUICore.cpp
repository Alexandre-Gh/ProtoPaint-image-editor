/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "GUICore.hpp"

GUI::GUICore::GUICore(std::shared_ptr<Graphic::Window> win)
{
    this->_window = win;
    ImGui::SFML::Init(win->getCoreWindow());
}

GUI::GUICore::~GUICore()
{
    ImGui::SFML::Shutdown();
}

void GUI::GUICore::update()
{
    ImGui::SFML::ProcessEvent(this->_window->getCoreWindow(), this->_window->getCoreEvent());
    ImGui::SFML::Update(this->_window->getCoreWindow(), this->_clock.restart());
}

void GUI::GUICore::display()
{
    ImGui::SFML::Render(this->_window->getCoreWindow());
}

void GUI::GUICore::startLoadFile()
{
    IGFD::FileDialogConfig config;
    this->_FDClosed = false;
	config.path = ".";
    config.countSelectionMax = 1;
    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".png,.jpg,.jpeg", config);
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
          this->selectedFilePath = ImGuiFileDialog::Instance()->GetFilePathName();
        }
        ImGuiFileDialog::Instance()->Close();
        this->_FDClosed = true;
    }
}

void GUI::GUICore::startSaveFile()
{
        IGFD::FileDialogConfig config;
    this->_FDClosed = false;
	config.path = ".";
    config.countSelectionMax = 1;
    ImGuiFileDialog::Instance()->OpenDialog("ChooseSaveFileDlgKey", "Choose Folder", "", config);
    if (ImGuiFileDialog::Instance()->Display("ChooseSaveFileDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
          this->selectedFilePath = ImGuiFileDialog::Instance()->GetFilePathName();
        }
        ImGuiFileDialog::Instance()->Close();
        this->_FDClosed = true;
    }
}

void GUI::GUICore::resetFilePath()
{
    this->selectedFilePath = "";
}

const std::string &GUI::GUICore::getFilePath()
{
    return this->selectedFilePath;
}

const bool &GUI::GUICore::getFDClosed()
{
    return this->_FDClosed;
}

