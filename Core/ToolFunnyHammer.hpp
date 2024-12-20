/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** OOP
*/

#ifndef TOOL_FUNNY_HAMMER_H_
    #define TOOL_FUNNY_HAMMER_H_

    #include "ATool.hpp"

    namespace EpiGimp
    {
        class ToolFunnyHammer: public EpiGimp::ATool
        {
            public:
                ToolFunnyHammer();
                ~ToolFunnyHammer() = default;
                void action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone);
                void drawPreview(std::shared_ptr<Graphic::Window> win);

            private:
                sf::Texture _drawTexture;
                sf::Sprite _drawSprite;
                sf::Texture _hammerTexture;
                sf::Sprite _hammerSprite;
                sf::SoundBuffer _buffer;
                sf::Sound _snd;
        };
    }

#endif