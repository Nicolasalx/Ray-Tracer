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
    class Matrix3D
    {
    private:
        std::array<std::array<double, 3>, 3> matrix_;

    public:
        Matrix3D()
        {
            matrix_[0] = {1, 0, 0};
            matrix_[1] = {0, 1, 0};
            matrix_[2] = {0, 0, 1};
        }
        Matrix3D(double matrix00, double matrix10, double matrix20,
            double matrix01, double matrix11, double matrix21,
            double matrix02, double matrix12, double matrix22)
        {
            matrix_[0] = {matrix00, matrix10, matrix20};
            matrix_[1] = {matrix01, matrix11, matrix21};
            matrix_[2] = {matrix02, matrix12, matrix22};
        }
        ~Matrix3D() = default;

        static Math::Matrix3D fromEulerAngles(const Math::Vector3D &angles)
        {
            double cy = std::cos(angles.y());
            double sy = std::sin(angles.y());
            double cp = std::cos(angles.x());
            double sp = std::sin(angles.x());
            double cr = std::cos(angles.z());
            double sr = std::sin(angles.z());

            return Math::Matrix3D(
                cy * cr + sy * sp * sr,
                cp * sr,
                cy * sp * sr - cr * sy,
                cr * sy * sp - cy * sr,
                cp * cr,
                cy * cr * sp + sr * sy,
                cp * sy,
                -sp,
                cp * cy
            );
        }

        Math::Matrix3D operator * (const Math::Matrix3D &other) const
        {
            Math::Matrix3D res;

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    res.matrix_[i][j] = 0;
                    res.matrix_[i][j] += matrix_[i][0] * other.matrix_[0][j];
                    res.matrix_[i][j] += matrix_[i][1] * other.matrix_[1][j];
                    res.matrix_[i][j] += matrix_[i][2] * other.matrix_[2][j];
                }
            }
            return res;
        }

        Math::Vector3D operator * (const Math::Vector3D &vec) const
        {
            double x = matrix_[0][0] * vec.x() + matrix_[0][1] * vec.y() + matrix_[0][2] * vec.z();
            double y = matrix_[1][0] * vec.x() + matrix_[1][1] * vec.y() + matrix_[1][2] * vec.z();
            double z = matrix_[2][0] * vec.x() + matrix_[2][1] * vec.y() + matrix_[2][2] * vec.z();
            return Math::Vector3D(x, y, z);
        }

        double &operator () (int i, int j)
        {
            return matrix_[i][j];
        }

        const double &operator () (int i, int j) const
        {
            return matrix_[i][j];
        }
    };
}

#endif /* !MATRIX3D_HPP_ */
