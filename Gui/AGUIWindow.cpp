/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "AGUIWindow.hpp"

GUI::AGUIWindow::AGUIWindow(std::string title)
{
    this->_title = title;
}

GUI::AGUIWindow::~AGUIWindow()
{

}

void GUI::AGUIWindow::display()
{
    ImGui::Begin(this->_title.c_str());

    this->content();

    ImGui::End();
}

void GUI::AGUIWindow::content()
{
    ImGui::Button("Modify content() to edit this window");
}