/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** AMaterial
*/

#ifndef AMATERIAL_HPP_
    #define AMATERIAL_HPP_

    #include "IMaterial.hpp"

namespace Rt
{
    class AMaterial : public Rt::IMaterial
    {
    public:
        ~AMaterial() = default;

        bool scatter(const Rt::Ray &, const Rt::HitRecord &,
            Math::Color01 &, Rt::Ray &) const override
        {
            return false;
        }
    };
}

#endif /* !AMATERIAL_HPP_ */
