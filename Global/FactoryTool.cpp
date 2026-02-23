/*
** ProtoPaint
** File description:
** FactoryObject
*/

#include "FactoryTool.hpp"
#include "../Core/ToolBrush.hpp"
#include "../Core/ToolEraser.hpp"
#include "../Core/ToolBucket.hpp"
#include "../Core/ToolColorPicker.hpp"
#include "../Core/ToolPencil.hpp"
#include "../Core/ToolSpray.hpp"
#include "../Core/ToolRect.hpp"
#include "../Core/ToolCircle.hpp"
#include "../Core/ToolLine.hpp"
#include "../Core/ToolText.hpp"
#include "../Core/ToolImage.hpp"
#include "../Core/ToolSelection.hpp"
#include "../Core/ToolFunnyHammer.hpp"



FactoryTool::FactoryTool()
{
    _allTools["Brush"] = [&]() -> std::unique_ptr<ProtoPaint::ITool> { return std::make_unique<ProtoPaint::ToolBrush>(); };
    _allTools["Eraser"] = [&]() -> std::unique_ptr<ProtoPaint::ITool> { return std::make_unique<ProtoPaint::ToolEraser>(); };
    _allTools["Bucket"] = [&]() -> std::unique_ptr<ProtoPaint::ITool> { return std::make_unique<ProtoPaint::ToolBucket>(); };
    _allTools["ColorPicker"] = [&]() -> std::unique_ptr<ProtoPaint::ITool> { return std::make_unique<ProtoPaint::ToolColorPicker>(); };
    _allTools["Pencil"] = [&]() -> std::unique_ptr<ProtoPaint::ITool> { return std::make_unique<ProtoPaint::ToolPencil>(); };
    _allTools["Spray"] = [&]() -> std::unique_ptr<ProtoPaint::ITool> { return std::make_unique<ProtoPaint::ToolSpray>(); };
    _allTools["Rect"] = [&]() -> std::unique_ptr<ProtoPaint::ITool> { return std::make_unique<ProtoPaint::ToolRect>(); };
    _allTools["Circle"] = [&]() -> std::unique_ptr<ProtoPaint::ITool> { return std::make_unique<ProtoPaint::ToolCircle>(); };
    _allTools["Line"] = [&]() -> std::unique_ptr<ProtoPaint::ITool> { return std::make_unique<ProtoPaint::ToolLine>(); };
    _allTools["Text"] = [&]() -> std::unique_ptr<ProtoPaint::ITool> { return std::make_unique<ProtoPaint::ToolText>(); };
    _allTools["BrushImage"] = [&]() -> std::unique_ptr<ProtoPaint::ITool> { return std::make_unique<ProtoPaint::ToolImage>(); };
    _allTools["Selection"] = [&]() -> std::unique_ptr<ProtoPaint::ITool> { return std::make_unique<ProtoPaint::ToolSelection>(); };
    _allTools["FunnyHammer"] = [&]() -> std::unique_ptr<ProtoPaint::ITool> { return std::make_unique<ProtoPaint::ToolFunnyHammer>(); };

}

FactoryTool &FactoryTool::GetInstance()
{
    static FactoryTool instance;
    return instance;
}

std::unique_ptr<ProtoPaint::ITool> FactoryTool::createTool(const std::string toolName)
{
    if (_allTools.count(toolName) == 0) {
        throw ErrorException("This tool does not exist in the factory");
    }
    return _allTools[toolName]();
}