/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Dielectric
*/

#ifndef DIELECTRIC_HPP_
    #define DIELECTRIC_HPP_

    #include "AMaterial.hpp"

namespace Rt
{
    class Dielectric : public AMaterial
    {
    private:
        double refraction_index_;

        static double reflectance(double cosine, double refraction_index)
        {
            // Use Schlick's approximation for reflectance.
            double r0 = (1 - refraction_index) / (1 + refraction_index);
            r0 = r0 * r0;
            return r0 + (1 - r0) * std::pow((1 - cosine), 5);
        }

    public:
        Dielectric(double refraction_index) : refraction_index_(refraction_index) {}
        ~Dielectric() = default;

        bool scatter(const Rt::Ray &ray_in, const Rt::HitRecord &rec,
            Math::Color01 & attenuation, Rt::Ray &scattered) const override
        {
            attenuation = Math::Color01(1.0, 1.0, 1.0);
            double ri = rec.front_face ? (1.0 / refraction_index_) : refraction_index_;

            Math::Vector3D unit_direction = ray_in.getDirection().unit_vector();
            double cos_theta = std::fmin((-unit_direction).dot(rec.normal), 1.0);
            double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

            bool cannot_refract = ri * sin_theta > 1.0;
            Math::Vector3D direction;

            if (cannot_refract || reflectance(cos_theta, ri) > Rt::Random::getBw01()) {
                direction = unit_direction.reflect(rec.normal);
            } else {
                direction = unit_direction.refract(rec.normal, ri);
            }

            scattered = Rt::Ray(rec.pos, direction);
            return true;
        }
    };
}

#endif /* !DIELECTRIC_HPP_ */
