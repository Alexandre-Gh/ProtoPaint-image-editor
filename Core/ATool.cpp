/*
** EPITECH PROJECT, 2024
** EpiGimp
** File description:
** Core
*/

#include "ATool.hpp"

EpiGimp::ATool::ATool()
{

}

EpiGimp::ATool::~ATool()
{

}

void EpiGimp::ATool::action(std::shared_ptr<Graphic::Window> win, std::shared_ptr<Graphic::DrawZone> zone)
{
    
}

void EpiGimp::ATool::setValue(std::string valueName, int value)
{
    this->_values.at(valueName) = value;
}
