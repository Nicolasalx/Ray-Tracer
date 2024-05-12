/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** errorCamera
*/

#include "ErrorCamera.hpp"

ErrorCamera::ErrorCamera(std::ostream &os, const std::string &message) throw()
{
    os << message << std::endl;
}