/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** FactoryObject
*/

#include "DataTransfer.hpp"
#include "FactoryTool.hpp"

DataTransfer::DataTransfer()
{
    //Get all fonts filepath in user
    std::string fontDir = "/usr/share/fonts";
    for (const auto& entry : std::filesystem::directory_iterator(fontDir)) {
        if (std::filesystem::is_directory(entry.status())) {
            for (const auto& file : std::filesystem::directory_iterator(entry.path())) {
                std::string extension = file.path().extension().string();
                std::string filename = file.path().filename().string();
                if (filename.find("Italic") != std::string::npos) {
                    continue;
                }
                if (filename.find("Bold") != std::string::npos) {
                    continue;
                }
                if (std::filesystem::is_regular_file(file.status()) && (extension == ".otf" || extension == ".ttf")) {
                    this->_fonts.push_back(file.path().filename().string());
                    this->_fontFilepaths.push_back(entry.path().string() + "/" + file.path().filename().string());
                }
            }
        }
    }
    std::sort(this->_fonts.begin(), this->_fonts.end(), std::greater<std::string>());
    std::sort(this->_fontFilepaths.begin(), this->_fontFilepaths.end(), std::greater<std::string>());
    std::cout << "Fonts loaded: " << this->_fonts.size() << std::endl;
}

const std::pair<std::string, int> &DataTransfer::getCurrentToolValue()
{
    _wasModified = false;
    return _lastModifiedValue;
}

void DataTransfer::setCurrentToolValue(std::string valueName, int value)
{
    _lastModifiedValue = {valueName, value};
    _wasModified = true;
}

bool DataTransfer::wasCurrentToolValueModified()
{
    return _wasModified;
}

const EpiGimp::varAction &DataTransfer::getCurrentAction()
{
    return this->_currentAction;
}

void DataTransfer::setCurrentAction(EpiGimp::varAction action)
{
    this->_currentAction = action;
}
