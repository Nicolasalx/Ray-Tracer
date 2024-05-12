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
    #include "ITexture.hpp"
    #include "SolidColor.hpp"

namespace Rt
{
    class Lambertian : public AMaterial
    {
    private:
        std::shared_ptr<Rt::ITexture> texture_;

    public:
        Lambertian(const Math::Color01 albedo) : texture_(std::make_shared<Rt::SolidColor>(albedo)) {}
        Lambertian(std::shared_ptr<ITexture> texture) : texture_(std::move(texture)) {}
        ~Lambertian() override = default;
    
        bool scatter(const Rt::Ray &, const Rt::HitData &rec,
            Math::Color01 &attenuation, Rt::Ray &scattered) const override
        {
            Math::Vector3D scatter_direction = rec.normal + Math::Vector3D::random_unit_vector();

            if (scatter_direction.near_zero()) {
                scatter_direction = rec.normal;
            }
            scattered = Rt::Ray(rec.pos, scatter_direction);
            attenuation = this->texture_->value(rec.u, rec.v, rec.pos);
            return true;
        }
    };
}

#endif /* !LAMBERTIAN_HPP_ */
