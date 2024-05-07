/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** imageloader
*/

#include "ImageLoader.hpp"

void Rt::ImageLoader::loadImage(const std::string &image_path)
{
    if (!image_.loadFromFile(image_path)) {
        throw my::tracked_exception("Failed to load image: " + image_path);
    }
}

std::size_t Rt::ImageLoader::getSizeX() const
{
    return image_.getSize().x;
}

std::size_t Rt::ImageLoader::getSizeY() const
{
    return image_.getSize().y;
}

Math::Color01 Rt::ImageLoader::getPixelColor(std::size_t x, std::size_t y) const
{
    if (x < image_.getSize().x && y < image_.getSize().y) {
        sf::Color color = image_.getPixel(x, y);
        return Math::Color01(color.r / 255.0, color.g / 255.0, color.b / 255.0);
    } else {
        my::log::warning("Invalid pixel coordinates: (" + std::to_string(x) + ", " + std::to_string(y) + ")");
        return Math::Color01();
    }
}