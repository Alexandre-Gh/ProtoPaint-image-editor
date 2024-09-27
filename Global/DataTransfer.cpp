/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** FactoryObject
*/

#include "DataTransfer.hpp"
#include "FactoryTool.hpp"

DataTransfer::DataTransfer()
{

}

const std::pair<std::string, int> &DataTransfer::getCurrentToolValue()
{
    _wasModified = false;
    return _lastModifiedValue;
}

const EpiGimp::varTool &DataTransfer::setCurrentToolValue(std::string valueName, int value)
{
    _lastModifiedValue = {valueName, value};
    _wasModified = true;
}

bool DataTransfer::wasCurrentToolValueModified()
{
    return _wasModified;
}
