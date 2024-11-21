/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "ImageWin.hpp"

GUI::ImageWin::ImageWin() :
    AGUIWindow("Image Brush")
{
    
}

void GUI::ImageWin::content()
{
    ImTextureID texture_id;
    ImGuiStyle colorButton = ImGui::GetStyle();

    ImGui::SetWindowCollapsed(false);

    if (ImGui::Button("...")) {
        this->_filepath = this->getFilePathLoad();
        if (!this->_filepath.empty()) {
            GlobalData.setImageBrushFilepath(this->_filepath);
        }
    }
    ImGui::Text("Current File:");
    ImGui::Text(this->_filepath.c_str());

}

std::string GUI::ImageWin::getFilePathLoad()
{
    std::string command = "zenity --file-selection --file-filter='PNG files | *.png' --file-filter='JPG files | *.jpg' --file-filter='Bitmap files | *.bmp' --title='Select a file'";
    std::string res = "";

    // Open a pipe to execute the command and capture the output
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to run Zenity command" << std::endl;
        return res;
    }

    // Read the selected file path from Zenity output
    char buffer[512];
    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        // Remove the newline character at the end of the string
        buffer[strcspn(buffer, "\n")] = '\0';
        res = std::string(buffer);
        std::cout << res << std::endl;
    }

    fclose(pipe);
    return res;
}
