/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** ITexture
*/

#ifndef ITEXTURE_HPP_
    #define ITEXTURE_HPP_

    #include "Color01.hpp"
    #include "Point3D.hpp"

namespace Rt
{
    class ITexture
    {
    public:
        virtual ~ITexture() = default;

        virtual Math::Color01 value(double u, double v, const Math::Point3D &p) const = 0;
    };
}

#endif /* !ITEXTURE_HPP_ */
