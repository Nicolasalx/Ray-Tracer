/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Vector3D
*/

#ifndef VECTOR3D_HPP_
    #define VECTOR3D_HPP_

    #include <cmath>

namespace Math
{
    class Vector3D
    {
        public:
            Vector3D() = default;
            Vector3D(double x, double y, double z) : X(x), Y(y), Z(z) {}

            double length()
            {
                return std::sqrt(std::pow(X, 2) + std::pow(Y, 2) + std::pow(Z, 2));
            }

            double X = 0;
            double Y = 0;
            double Z = 0;
    };
}

#endif /* !VECTOR3D_HPP_ */
