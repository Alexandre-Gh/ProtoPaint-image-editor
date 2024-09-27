/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** FactoryObject
*/

#include "FactorySprite.hpp"
#include "../Core/ToolBrush.hpp"

FactorySprite::FactorySprite()
{
    _textures["CanvasBG"].loadFromFile("./assets/canvas_bg.png", {0, 0, 32, 32});
    _textures["CanvasGB"].setRepeated(true);
    _textures["Brush"].loadFromFile("./assets/icons.png", {0, 0, 28, 28});
    _textures["Eraser"].loadFromFile("./assets/icons.png", {28, 0, 28, 28});

    _allSprites["Brush"] = [&]() -> std::unique_ptr<sf::Sprite> { return std::make_unique<sf::Sprite>(_textures["Brush"]); };
    _allSprites["Eraser"] = [&]() -> std::unique_ptr<sf::Sprite> { return std::make_unique<sf::Sprite>(_textures["Eraser"]); };
    _allSprites["CanvasBG"] = [&]() -> std::unique_ptr<sf::Sprite> { return std::make_unique<sf::Sprite>(_textures["CanvasBG"]); };
}

FactorySprite &FactorySprite::GetInstance()
{
    static FactorySprite instance;
    return instance;
}

std::unique_ptr<sf::Sprite> FactorySprite::createSprite(const std::string spriteName)
{
    if (_allSprites.count(spriteName) == 0) {
        throw ErrorException("This sprite does not exist in the factory");
    }
    return _allSprites[spriteName]();
}