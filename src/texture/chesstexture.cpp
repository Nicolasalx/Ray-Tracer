/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** chesstexture
*/

#include "ChessTexture.hpp"

Math::Color01 Rt::ChessTexture::value(double u, double v, const Math::Point3D &p) const
{
    int xInteger = std::floor(inv_scale * p.x());
    int yInteger = std::floor(inv_scale * p.y());
    int zInteger = std::floor(inv_scale * p.z());

    bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;

    return isEven ? even->value(u, v, p) : odd->value(u, v, p);
}