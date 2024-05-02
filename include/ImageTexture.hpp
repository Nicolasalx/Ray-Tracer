/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** ImageTexture
*/

#ifndef IMAGETEXTURE_HPP_
    #define IMAGETEXTURE_HPP_

    #include "ITexture.hpp"
    #include "ImageLoader.hpp"
    #include "Interval.hpp"

namespace Rt
{
    class ImageTexture : public Rt::ITexture
    {
    private:
        Rt::ImageLoader image_;

    public:
        ImageTexture(const std::string &filename) : image_(filename) {}

        Math::Color01 value(double u, double v, const Math::Point3D &) const override;
    };
}

#endif /* !IMAGETEXTURE_HPP_ */
