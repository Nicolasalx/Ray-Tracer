/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** matrix3D
*/

#include "Matrix3D.hpp"

Math::Matrix3D::Matrix3D()
{
    matrix_[0] = {1, 0, 0};
    matrix_[1] = {0, 1, 0};
    matrix_[2] = {0, 0, 1};
}

Math::Matrix3D::Matrix3D(double matrix00, double matrix10, double matrix20,
    double matrix01, double matrix11, double matrix21,
    double matrix02, double matrix12, double matrix22)
{
    matrix_[0] = {matrix00, matrix10, matrix20};
    matrix_[1] = {matrix01, matrix11, matrix21};
    matrix_[2] = {matrix02, matrix12, matrix22};
}

Math::Matrix3D Math::Matrix3D::transpose() const
{
    Math::Matrix3D transposed_matrix;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            transposed_matrix(i, j) = matrix_[j][i];
        }
    }
    return transposed_matrix;
}

Math::Vector3D Math::Matrix3D::operator * (const Math::Vector3D &vec) const
{
    double x = matrix_[0][0] * vec.x() + matrix_[0][1] * vec.y() + matrix_[0][2] * vec.z();
    double y = matrix_[1][0] * vec.x() + matrix_[1][1] * vec.y() + matrix_[1][2] * vec.z();
    double z = matrix_[2][0] * vec.x() + matrix_[2][1] * vec.y() + matrix_[2][2] * vec.z();
    return Math::Vector3D(x, y, z);
}

Math::Matrix3D Math::Matrix3D::operator * (const Math::Matrix3D &other) const
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

double &Math::Matrix3D::operator () (int i, int j)
{
    return matrix_[i][j];
}

const double &Math::Matrix3D::operator () (int i, int j) const
{
    return matrix_[i][j];
}
