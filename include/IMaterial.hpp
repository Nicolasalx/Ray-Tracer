/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Material
*/

#ifndef MATERIAL_HPP_
    #define MATERIAL_HPP_

    #include "Ray.hpp"
    #include "HitData.hpp"
    #include "Color01.hpp"

namespace Rt
{
    struct HitData;

    class IMaterial
    {
    public:
        virtual ~IMaterial() = default;

        virtual bool scatter(const Rt::Ray &ray_in, const Rt::HitData &rec,
            Math::Color01 &attenuation, Rt::Ray &scattered) const = 0;
        virtual Math::Color01 emitted(double u, double v, const Math::Point3D &p) const = 0;
    };
}

#endif /* !MATERIAL_HPP_ */
