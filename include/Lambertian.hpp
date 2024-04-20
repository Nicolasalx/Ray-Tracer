/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Lambertian
*/

#ifndef LAMBERTIAN_HPP_
    #define LAMBERTIAN_HPP_

    #include "Color01.hpp"
    #include "Vector3D.hpp"
    #include "AMaterial.hpp"

namespace Rt
{
    class Lambertian : public AMaterial
    {
    private:
        Math::Color01 whiteness_;

    public:
        Lambertian(const Math::Color01 whiteness) : whiteness_(whiteness) {}
        ~Lambertian() = default;
    
        bool scatter(const Rt::Ray &, const Rt::HitRecord &rec,
            Math::Color01 &attenuation, Rt::Ray &scattered) const override
        {
            Math::Vector3D scatter_direction = rec.normal + Math::Vector3D::random_unit_vector();

            if (scatter_direction.near_zero()) {
                scatter_direction = rec.normal;
            }
            scattered = Rt::Ray(rec.pos, scatter_direction);
            attenuation = this->whiteness_;
            return true;
        }
    };
}

#endif /* !LAMBERTIAN_HPP_ */
