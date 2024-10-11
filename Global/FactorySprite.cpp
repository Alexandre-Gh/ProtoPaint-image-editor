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
    int iconUnit = 28;
    _textures["Brush"].loadFromFile("./assets/icons.png", {iconUnit * 4, 0, 28, 28});
    _textures["Eraser"].loadFromFile("./assets/icons.png", {iconUnit, 0, 28, 28});
    _textures["Bucket"].loadFromFile("./assets/icons.png", {iconUnit * 2, 0, 28, 28});
    _textures["ColorPicker"].loadFromFile("./assets/icons.png", {iconUnit * 3, 0, 28, 28});
    _textures["Pencil"].loadFromFile("./assets/icons.png", {0, 0, 28, 28});

    _allSprites["Brush"] = [&]() -> std::unique_ptr<sf::Sprite> { return std::make_unique<sf::Sprite>(_textures["Brush"]); };
    _allSprites["Eraser"] = [&]() -> std::unique_ptr<sf::Sprite> { return std::make_unique<sf::Sprite>(_textures["Eraser"]); };
    _allSprites["Bucket"] = [&]() -> std::unique_ptr<sf::Sprite> { return std::make_unique<sf::Sprite>(_textures["Bucket"]); };
    _allSprites["ColorPicker"] = [&]() -> std::unique_ptr<sf::Sprite> { return std::make_unique<sf::Sprite>(_textures["ColorPicker"]); };
    _allSprites["Pencil"] = [&]() -> std::unique_ptr<sf::Sprite> { return std::make_unique<sf::Sprite>(_textures["Pencil"]); };
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