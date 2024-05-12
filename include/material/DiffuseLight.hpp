/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** DiffuseLight
*/

#ifndef DIFFUSELIGHT_HPP_
    #define DIFFUSELIGHT_HPP_

    #include "AMaterial.hpp"
    #include "ITexture.hpp"
    #include "SolidColor.hpp"

namespace Rt
{
    class DiffuseLight : public AMaterial
    {
    private:
        std::shared_ptr<Rt::ITexture> texture_;

    public:
        DiffuseLight(std::shared_ptr<Rt::ITexture> texture) : texture_(std::move(texture)) {}
        DiffuseLight(const Math::Color01 &emit) : texture_(std::make_shared<Rt::SolidColor>(emit)) {}

        Math::Color01 emitted(double u, double v, const Math::Point3D &p) const override
        {
            return texture_->value(u, v, p);
        }
    };
}

#endif /* !DIFFUSELIGHT_HPP_ */
