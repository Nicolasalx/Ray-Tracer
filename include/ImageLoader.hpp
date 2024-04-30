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

        void loadImage(const std::string &image_path)
        {
            if (!image_.loadFromFile(image_path)) {
                throw my::tracked_exception("Failed to load image: " + image_path);
            }
        }

        std::size_t getSizeX() const
        {
            return image_.getSize().x;
        }

        std::size_t getSizeY() const
        {
            return image_.getSize().y;
        }

        Math::Color01 getPixelColor(std::size_t x, std::size_t y) const
        {
            if (x < image_.getSize().x && y < image_.getSize().y) {
                sf::Color color = image_.getPixel(x, y);
                return Math::Color01(color.r / 255.0, color.g / 255.0, color.b / 255.0);
            } else {
                my::log::warning("Invalid pixel coordinates: (" + std::to_string(x) + ", " + std::to_string(y) + ")");
                return Math::Color01();
            }
        }
    };
}

#endif /* !IMAGELOADER_HPP_ */
