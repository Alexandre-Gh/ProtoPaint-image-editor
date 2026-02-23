/*
** ProtoPaint
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
    if (!this->_isVisible) return;
    if (this->_isNavBar) {
        ImGui::BeginMainMenuBar();
    } else {
        ImGui::Begin(this->_title.c_str());
    }

    this->content();

    if (this->_isNavBar) {
        ImGui::EndMainMenuBar();
    } else {
        ImGui::End();
    }
}

void GUI::AGUIWindow::content()
{
    ImGui::Button("Modify content() to edit this window");
}

void GUI::AGUIWindow::setVisible(bool visible)
{
    this->_isVisible = visible;
}

const bool &GUI::AGUIWindow::getVisible()
{
    return this->_isVisible;
}
