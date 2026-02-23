/*
** ProtoPaint
** File description:
** Core
*/

#include "ColorHistoryWin.hpp"

GUI::ColorHistoryWin::ColorHistoryWin() :
    AGUIWindow("Color History")
{

}

void GUI::ColorHistoryWin::content()
{
    ImTextureID texture_id;
    ImGuiStyle colorButton = ImGui::GetStyle();

    if (this->_lastColor != GlobalData.getMainColor() && !ImGui::GetIO().WantCaptureMouse) {
        this->_lastColor = GlobalData.getMainColor();
        this->addColor();
    }

    ImGui::SetWindowCollapsed(false);
    int i = 0;
    std::string name;
    for (auto &e : this->_colors) {
        name = std::to_string(i);
        if (ImGui::ColorButton(name.c_str(), e.second, ImGuiColorEditFlags_NoTooltip, ImVec2(30, 30))) {
            // When a color button is clicked, set the current color to this history color
            
            GlobalData.setMainColor(e.first);
        }
        if (i != 4) {
            ImGui::SameLine(0, 5);
        }
        i++;
    }
}

void GUI::ColorHistoryWin::addColor()
{
    if (this->_colors.size() >= 10) {
        this->_colors.erase(this->_colors.begin());
    }
    sf::Color newColor(GlobalData.getMainColor());
    float scolor[4] = {newColor.r / 255.0f, newColor.g / 255.0f, newColor.b / 255.0f, newColor.a / 255.0f};
    if (this->_colors.count(newColor) == 0) {
        this->_colors[newColor] = ImVec4(scolor[0], scolor[1], scolor[2], scolor[3]);
        std::cout << (float)newColor.r << " " << (float)newColor.g << " " << (float)newColor.b << std::endl;
    }
}

