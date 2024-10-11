/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** FactoryObject
*/

#include "FactoryTool.hpp"
#include "../Core/ToolBrush.hpp"
#include "../Core/ToolEraser.hpp"
#include "../Core/ToolBucket.hpp"
#include "../Core/ToolColorPicker.hpp"
#include "../Core/ToolPencil.hpp"


FactoryTool::FactoryTool()
{
    _allTools["Brush"] = [&]() -> std::unique_ptr<EpiGimp::ITool> { return std::make_unique<EpiGimp::ToolBrush>(); };
    _allTools["Eraser"] = [&]() -> std::unique_ptr<EpiGimp::ITool> { return std::make_unique<EpiGimp::ToolEraser>(); };
    _allTools["Bucket"] = [&]() -> std::unique_ptr<EpiGimp::ITool> { return std::make_unique<EpiGimp::ToolBucket>(); };
    _allTools["ColorPicker"] = [&]() -> std::unique_ptr<EpiGimp::ITool> { return std::make_unique<EpiGimp::ToolColorPicker>(); };
    _allTools["Pencil"] = [&]() -> std::unique_ptr<EpiGimp::ITool> { return std::make_unique<EpiGimp::ToolPencil>(); };
}

FactoryTool &FactoryTool::GetInstance()
{
    static FactoryTool instance;
    return instance;
}

std::unique_ptr<EpiGimp::ITool> FactoryTool::createTool(const std::string toolName)
{
    if (_allTools.count(toolName) == 0) {
        throw ErrorException("This tool does not exist in the factory");
    }
    return _allTools[toolName]();
}