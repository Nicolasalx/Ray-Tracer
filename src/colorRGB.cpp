/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** colorRGB
*/

#include "ColorRGB.hpp"

Rt::ColorRGB::ColorRGB(const Math::Color01 color01) : color
{
    static_cast<int>(std::clamp<double>((color01[0] > 0 ? std::sqrt(color01[0]) : 0), 0, 1) * 255),
    static_cast<int>(std::clamp<double>((color01[1] > 0 ? std::sqrt(color01[1]) : 0), 0, 1) * 255),
    static_cast<int>(std::clamp<double>((color01[2] > 0 ? std::sqrt(color01[2]) : 0), 0, 1) * 255)}
{
}

Rt::ColorRGB::ColorRGB(int r, int g, int b) : color({r, g, b}) {}

double Rt::ColorRGB::r() const
{
    return color[0];
}

double Rt::ColorRGB::g() const
{
    return color[1];
}

double Rt::ColorRGB::b() const
{
    return color[2];
}

void Rt::ColorRGB::displayColor(int x, int y)
{
    int index = ((y * Rt::Interface::image_size_x + x) * 4);
    Rt::Raytracer::mutex.lock();
    Rt::Interface::image_pixel[index] = color[0];
    Rt::Interface::image_pixel[index + 1] = color[1];
    Rt::Interface::image_pixel[index + 2] = color[2];
    Rt::Interface::image_pixel[index + 3] = 255;
    Rt::Interface::image_pixel_i += 4;
    Rt::Raytracer::mutex.unlock();
}
