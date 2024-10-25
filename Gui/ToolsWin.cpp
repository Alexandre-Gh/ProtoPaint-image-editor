/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "ToolsWin.hpp"
#include "../Global/FactorySprite.hpp"


GUI::ToolsWin::ToolsWin() :
    AGUIWindow("Tools")
{
    this->_buttonSprites[EpiGimp::TOOL_BRUSH] = FactorySprite::GetInstance().createSprite("Brush");
    this->_buttonSprites[EpiGimp::TOOL_ERASER] = FactorySprite::GetInstance().createSprite("Eraser");
    this->_buttonSprites[EpiGimp::TOOL_BUCKET] = FactorySprite::GetInstance().createSprite("Bucket");
    this->_buttonSprites[EpiGimp::TOOL_COLORPICKER] = FactorySprite::GetInstance().createSprite("ColorPicker");
    this->_buttonSprites[EpiGimp::TOOL_PENCIL] = FactorySprite::GetInstance().createSprite("Pencil");
    this->_buttonSprites[EpiGimp::TOOL_SPRAY] = FactorySprite::GetInstance().createSprite("Spray");
    this->_buttonSprites[EpiGimp::TOOL_RECT] = FactorySprite::GetInstance().createSprite("Rect");
    this->_buttonSprites[EpiGimp::TOOL_CIRCLE] = FactorySprite::GetInstance().createSprite("Circle");
    this->_buttonSprites[EpiGimp::TOOL_LINE] = FactorySprite::GetInstance().createSprite("Line");

    this->_ids[EpiGimp::TOOL_BRUSH] = "Brush";
    this->_ids[EpiGimp::TOOL_ERASER] = "Eraser";
    this->_ids[EpiGimp::TOOL_BUCKET] = "Bucket";
    this->_ids[EpiGimp::TOOL_COLORPICKER] = "ColorPicker";
    this->_ids[EpiGimp::TOOL_PENCIL] = "Pencil";
    this->_ids[EpiGimp::TOOL_SPRAY] = "Spray";
    this->_ids[EpiGimp::TOOL_RECT] = "Rect";
    this->_ids[EpiGimp::TOOL_CIRCLE] = "Circle";
    this->_ids[EpiGimp::TOOL_LINE] = "Line";
}

void GUI::ToolsWin::content()
{
    ImTextureID texture_id;
    ImGuiStyle colorButton = ImGui::GetStyle();
    ImGui::SetWindowCollapsed(false);
    ImGui::BeginGroup();
    int cols = 0;

    for (auto const &e: this->_buttonSprites) {
        texture_id = reinterpret_cast<ImTextureID>(e.second->getTexture()->getNativeHandle());
        if (e.first != this->getCurrentTool()) {
            ImGui::GetStyle().Colors[ImGuiCol_Button] = ButtonColor;
        } else {
            ImGui::GetStyle().Colors[ImGuiCol_Button] = SelectedButtonColor;
        }
        if (ImGui::ImageButton(_ids[e.first].c_str(), texture_id, ImVec2(32, 32))) {
            GlobalData.setCurrentTool(e.first);
        }
        cols++;
        if (cols >= 3) {
            ImGui::NewLine();
            cols = 0;
        } else {
            ImGui::SameLine();
        }
    }
    ImGui::GetStyle().Colors[ImGuiCol_Button] = ButtonColor;
    std::string dispToolUsed = "Current: " + this->_ids[this->getCurrentTool()];
    ImGui::Text(dispToolUsed.c_str());
    ImGui::EndGroup();
    ImGui::NewLine();

    sf::Color previousColor = this->getMainColor();
    float color[4] = {previousColor.r / 255.0f, previousColor.g / 255.0f, previousColor.b / 255.0f, previousColor.a / 255.0f};
    if (ImGui::ColorEdit4("Primary", color)) {
        GlobalData.setMainColor(sf::Color(color[0] * 255, color[1] * 255, color[2] * 255, color[3] * 255));
    }

    previousColor = this->getSecondColor();
    float scolor[4] = {previousColor.r / 255.0f, previousColor.g / 255.0f, previousColor.b / 255.0f, previousColor.a / 255.0f};
    if (ImGui::ColorEdit4("Secondary", scolor)) {
        GlobalData.setSecondColor(sf::Color(scolor[0] * 255, scolor[1] * 255, scolor[2] * 255, scolor[3] * 255));
    }

}