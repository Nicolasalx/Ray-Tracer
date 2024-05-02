/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** ImageLoader
*/

#ifndef IMAGELOADER_HPP_
    #define IMAGELOADER_HPP_

    #include <SFML/Graphics.hpp>
    #include <string>
    #include "my_tracked_exception.hpp"
    #include "my_log.hpp"
    #include "Color01.hpp"

namespace Rt
{
    class ImageLoader
    {
    private:
        sf::Image image_;

    public:
        ImageLoader() = default;
        ImageLoader(const std::string image_path)
        {
            if (!image_.loadFromFile(image_path)) {
                throw my::tracked_exception("Failed to load image: " + image_path);
            }
        }
        ~ImageLoader() = default;

        void loadImage(const std::string &image_path);

        std::size_t getSizeX() const;

        std::size_t getSizeY() const;

        Math::Color01 getPixelColor(std::size_t x, std::size_t y) const;
    };
}

#endif /* !IMAGELOADER_HPP_ */
