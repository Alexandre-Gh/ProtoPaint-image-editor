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
