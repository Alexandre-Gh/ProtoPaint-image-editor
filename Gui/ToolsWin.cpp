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

    this->_ids[EpiGimp::TOOL_BRUSH] = "Brush";
    this->_ids[EpiGimp::TOOL_ERASER] = "Eraser";
    this->_ids[EpiGimp::TOOL_BUCKET] = "Bucket";
}

void GUI::ToolsWin::content()
{
    ImTextureID texture_id;
    ImGuiStyle colorButton = ImGui::GetStyle();

    ImGui::SetWindowCollapsed(false);
    for (auto const &e: this->_buttonSprites) {
        texture_id = reinterpret_cast<ImTextureID>(e.second->getTexture()->getNativeHandle());
        if (e.first != this->getCurrentTool()) {
            ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        } else {
            ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 1.0f, 0.8f);
        }
        if (ImGui::ImageButton(_ids[e.first].c_str(), texture_id, ImVec2(32, 32))) {
            GlobalData.setCurrentTool(e.first);
        }
    }

    ImGui::Spacing();
    ImGui::Spacing();

    sf::Color previousColor = this->getMainColor();
    float color[4] = {previousColor.r / 255.0f, previousColor.g / 255.0f, previousColor.b / 255.0f, previousColor.a / 255.0f};
    ImGui::ColorEdit4("Primary", color);
    GlobalData.setMainColor(sf::Color(color[0] * 255, color[1] * 255, color[2] * 255, color[3] * 255));

    previousColor = this->getSecondColor();
    float scolor[4] = {previousColor.r / 255.0f, previousColor.g / 255.0f, previousColor.b / 255.0f, previousColor.a / 255.0f};
    ImGui::ColorEdit4("Secondary", scolor);
    GlobalData.setSecondColor(sf::Color(scolor[0] * 255, scolor[1] * 255, scolor[2] * 255, scolor[3] * 255));


}