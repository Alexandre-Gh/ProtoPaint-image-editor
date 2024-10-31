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
                if (std::filesystem::is_regular_file(file.status()) && extension == ".ttf") {
                    this->_fonts.push_back(file.path().filename().string());
                    this->_fontFilepaths.push_back(entry.path().string() + "/" + file.path().filename().string());
                }
            }
        }
    }
    std::cout << this->_fonts.size() << std::endl;
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
