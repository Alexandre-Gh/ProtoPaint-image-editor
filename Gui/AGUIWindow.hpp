/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#pragma once

#ifndef AGUIWINDOW_H_
    #define AGUIWINDOW_H_

    #include "../Interfaces/IGUIWindow.hpp"

    namespace GUI
    {
        class AGUIWindow : public GUI::IGUIWindow
        {
            public:
                AGUIWindow(std::string title);
                ~AGUIWindow();

                void content(); //Actual function to modify in inherited classes
                void display(); //Call to display in other functions

            private:
                std::string _title;

            protected:
                const sf::Color& getMainColor() { return GlobalData.getMainColor(); }
                const sf::Color& getSecondColor() { return GlobalData.getSecondColor(); }
        };
    }

#endif