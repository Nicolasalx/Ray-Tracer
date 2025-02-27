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
        Math::Color01 albedo_;

    public:
        SolidColor(const Math::Color01 &albedo) : albedo_(albedo) {}

        SolidColor(double red, double green, double blue) : SolidColor(Math::Color01(red, green, blue))
        {
        }

        Math::Color01 value(double, double, const Math::Point3D &) const override;
    };
}

#endif /* !SOLIDCOLOR_HPP_ */
