/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef IGUIWINDOW_H_
    #define IGUIWINDOW_H_

    #include "../includes/Headers.hpp"

    namespace GUI
    {
        class IGUIWindow
        {
            public:
                virtual ~IGUIWindow() = default;

                virtual void content() = 0;
                virtual void display() = 0;

        };
    }

#endif