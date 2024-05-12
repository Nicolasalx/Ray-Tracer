/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Metal
*/

#ifndef METAL_HPP_
    #define METAL_HPP_

    #include "AMaterial.hpp"

namespace Rt
{
    class Metal : public AMaterial
    {
    private:
        Math::Color01 diffusion_;
        double reflection_;

    public:
        Metal(const Math::Color01 &diffusion, double reflection)
            : diffusion_(diffusion), reflection_(reflection < 1 ? reflection : 1) {}
        ~Metal() override = default;

        bool scatter(const Rt::Ray &ray_in, const Rt::HitData &rec,
            Math::Color01 &attenuation, Rt::Ray &scattered) const override
        {
            Math::Vector3D reflected = ray_in.getDirection().reflect(rec.normal);
            reflected = reflected.unit_vector() + (reflection_ * Math::Vector3D::random_unit_vector());
            scattered = Rt::Ray(rec.pos, reflected);
            attenuation = this->diffusion_;
            return (scattered.getDirection().dot(rec.normal) > 0);
        }
    };
}

#endif /* !METAL_HPP_ */
