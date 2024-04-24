/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** TextureChecker
*/

#ifndef TEXTURECHECKER_HPP_
    #define TEXTURECHECKER_HPP_

    #include "ITexture.hpp"
    #include <memory>
    #include "SolidColor.hpp"

namespace Rt
{
    class TextureChecker : public Rt::ITexture
    {
    private:
        double inv_scale;
        std::shared_ptr<Rt::ITexture> even;
        std::shared_ptr<Rt::ITexture> odd;

    public:
        TextureChecker(double scale, std::shared_ptr<ITexture> even, std::shared_ptr<ITexture> odd)
            : inv_scale(1.0 / scale), even(even), odd(odd) {}

        TextureChecker(double scale, const Math::Color01 &c1, const Math::Color01 &c2)
            : inv_scale(1.0 / scale),
            even(std::make_shared<Rt::SolidColor>(c1)),
            odd(std::make_shared<Rt::SolidColor>(c2))
        {
        }
        ~TextureChecker() = default;

        Math::Color01 value(double u, double v, const Math::Point3D &p) const override
        {
            auto xInteger = int(std::floor(inv_scale * p.x()));
            auto yInteger = int(std::floor(inv_scale * p.y()));
            auto zInteger = int(std::floor(inv_scale * p.z()));

            bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;

            return isEven ? even->value(u, v, p) : odd->value(u, v, p);
        }
    };
}

#endif /* !TEXTURECHECKER_HPP_ */
