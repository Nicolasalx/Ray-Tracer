/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** ChessTexture
*/

#ifndef CHESSTEXTURE_HPP_
    #define CHESSTEXTURE_HPP_

    #include "ITexture.hpp"
    #include <memory>
    #include "SolidColor.hpp"

namespace Rt
{
    class ChessTexture : public Rt::ITexture
    {
    private:
        double inv_scale;
        std::shared_ptr<Rt::ITexture> even;
        std::shared_ptr<Rt::ITexture> odd;

    public:
        ChessTexture(double scale, std::shared_ptr<ITexture> even, std::shared_ptr<ITexture> odd)
            : inv_scale(1.0 / scale), even(even), odd(odd) {}

        ChessTexture(double scale, const Math::Color01 &c1, const Math::Color01 &c2)
            : inv_scale(1.0 / scale),
            even(std::make_shared<Rt::SolidColor>(c1)),
            odd(std::make_shared<Rt::SolidColor>(c2))
        {
        }
        ~ChessTexture() = default;

        Math::Color01 value(double u, double v, const Math::Point3D &p) const override;
    };
}

#endif /* !CHESSTEXTURE_HPP_ */
