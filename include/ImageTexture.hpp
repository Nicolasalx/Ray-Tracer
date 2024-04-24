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

        Math::Color01 value(double u, double v, const Math::Point3D &p) const override
        {
            // If we have no texture data, then return solid cyan as a debugging aid.
            if (image_.getSizeY() <= 0) {
                return Math::Color01(0,1,1);
            }

            u = Rt::Interval(0, 1).clamp(u);
            v = 1.0 - Rt::Interval(0, 1).clamp(v);

            auto i = int(u * image_.getSizeX());
            auto j = int(v * image_.getSizeY());

            return image_.getPixelColor(i,j);
        }
    };
}

#endif /* !IMAGETEXTURE_HPP_ */
