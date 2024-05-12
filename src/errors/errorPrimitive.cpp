/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** errorPrimitive
*/

#include "ErrorPrimitive.hpp"

Rt::ErrorPrimitive::ErrorPrimitive(std::ostream &os, const std::string &message) noexcept
{
    os << message << std::endl;
}