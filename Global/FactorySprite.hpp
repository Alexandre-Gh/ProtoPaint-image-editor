/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** ErrorException
*/

#pragma once

#ifndef FACTORY_SPRITE_H_
    #define FACTORY_SPRITE_H_

    #include "../Interfaces/ITool.hpp"

        class FactorySprite
        {
            public:
                static FactorySprite &GetInstance();
                std::unique_ptr<sf::Sprite> createSprite(const std::string spriteName);

            protected:
                FactorySprite();
                FactorySprite(const FactorySprite&) = delete;
                FactorySprite& operator=(const FactorySprite&) = delete;

                std::map<std::string, sf::Texture> _textures;
                std::map<std::string, std::function<std::unique_ptr<sf::Sprite>()>> _allSprites;
        };

#endif