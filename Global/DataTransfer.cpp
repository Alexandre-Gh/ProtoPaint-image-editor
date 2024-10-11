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

const EpiGimp::varAction &DataTransfer::getCurrentAction()
{
    return this->_currentAction;
}

void DataTransfer::setCurrentAction(EpiGimp::varAction action)
{
    this->_currentAction = action;
}
