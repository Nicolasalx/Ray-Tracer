/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** SolidColor
*/

#ifndef SOLIDCOLOR_HPP_
    #define SOLIDCOLOR_HPP_
    
    #include "ITexture.hpp"

namespace Rt
{
    class SolidColor : public ITexture
    {
    private:
        Math::Color01 albedo;

    public:
        SolidColor(const Math::Color01 &albedo) : albedo(albedo) {}

        SolidColor(double red, double green, double blue) : SolidColor(Math::Color01(red, green, blue)) {}

        Math::Color01 value(double u, double v, const Math::Point3D &p) const override
        {
            return albedo;
        }
    };
}

#endif /* !SOLIDCOLOR_HPP_ */
