/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** solidcolor
*/

#include "SolidColor.hpp"

Math::Color01 Rt::SolidColor::value(double, double, const Math::Point3D &) const
{
    return albedo_;
}