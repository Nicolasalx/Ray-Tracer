/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** imagetexture
*/

#include "ImageTexture.hpp"

Math::Color01 Rt::ImageTexture::value(double u, double v, const Math::Point3D &) const
{
    if (image_.getSizeY() <= 0) {
        return Math::Color01(1, 1, 1);
    }

    u = Rt::Interval(0, 1).clamp(u);
    v = 1.0 - Rt::Interval(0, 1).clamp(v);

    std::size_t i = u * image_.getSizeX();
    std::size_t j = v * image_.getSizeY();

    return image_.getPixelColor(i, j);
}