/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Matrix3x3
*/

#ifndef MATRIX3D_HPP_
    #define MATRIX3D_HPP_

    #include "Vector3D.hpp"
    #include <array>
    #include <cmath>

namespace Math
{
    class Vector3D;

    class Matrix3D
    {
    private:
        std::array<std::array<double, 3>, 3> matrix_;

    public:
        Matrix3D();
        Matrix3D(double matrix00, double matrix10, double matrix20,
            double matrix01, double matrix11, double matrix21,
            double matrix02, double matrix12, double matrix22);
        ~Matrix3D() = default;

        Math::Matrix3D transpose() const;
        Math::Vector3D operator * (const Math::Vector3D &vec) const;
        Math::Matrix3D operator * (const Math::Matrix3D &other) const;
        double &operator () (int i, int j);
        const double &operator () (int i, int j) const;
    };
}

#endif /* !MATRIX3D_HPP_ */
