/*
** ProtoPaint
** File description:
** Core
*/

#include "ATool.hpp"

ProtoPaint::ATool::ATool()
{
    
}

ProtoPaint::ATool::~ATool()
{

}

void ProtoPaint::ATool::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    if (win->isMouseInUI()) {
        return;
    }
}

void ProtoPaint::ATool::setValue(std::pair<std::string, int> value)
{
    this->_values.at(value.first) = value.second;
}

void ProtoPaint::ATool::drawPreview(std::shared_ptr<Graphic::Window> win)
{

}

void ProtoPaint::ATool::drawPreviewInCurrentCanvas(std::shared_ptr<Graphic::Window> win)
{

}

void ProtoPaint::ATool::displayGUI()
{
    if (this->_gui != nullptr) {
        this->_gui->display();
    }
}
