/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Color
*/

#ifndef COLORRGB_HPP_
    #define COLORRGB_HPP_

    #include "Vector3D.hpp"
    #include "Color01.hpp"
    #include <iostream>
    #include <algorithm>
    #include "Raytracer.hpp"
    #include "Interface.hpp"

namespace Rt
{
    class ColorRGB
    {
    private:
        std::array<int, 3> color = {0, 0, 0};

    public:
        ColorRGB(const Math::Color01 color01);
        ColorRGB(int r, int g, int b);
        ~ColorRGB() = default;

        double r() const;
        double g() const;
        double b() const;

        void displayColor(int x, int y);
    };
}

#endif /* !COLORRGB_HPP_ */
