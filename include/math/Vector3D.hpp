/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Vecor3D
*/

#ifndef VECTOR3D_HPP_
    #define VECTOR3D_HPP_

    #include <array>
    #include <cmath>
    #include "Random.hpp"
    #include "Matrix3D.hpp"

namespace Math
{
    class Matrix3D;

    class Vector3D
    {
    protected:
        std::array<double, 3> vector = {0, 0, 0};

    public:
        Vector3D() = default;
        Vector3D(double x, double y, double z);
        ~Vector3D() = default;

        double x() const;
        double y() const;
        double z() const;

        Vector3D operator - () const;
        double operator [] (int i) const;
        double &operator [] (int i);

        Vector3D &operator += (const Vector3D &other);
        Vector3D &operator *= (const Vector3D &other);
        Vector3D &operator *= (double t);
        Vector3D &operator /= (double t);
        double length() const;
        double length_squared() const;
        Vector3D operator + (const Vector3D &other) const;
        Vector3D operator - (const Vector3D &other) const;
        Vector3D operator * (const Vector3D &other) const;
        Vector3D operator * (double t) const;
        Vector3D operator / (double t) const;
        Vector3D operator / (const Vector3D &other) const;
        double dot(const Vector3D &other) const;
        Vector3D cross(const Vector3D &other) const;
        Vector3D unit_vector() const;
        static Vector3D random();
        static Vector3D random(double min, double max);
        static Vector3D random_in_unit_sphere();
        static Vector3D random_unit_vector();
        static Vector3D random_on_hemisphere(const Vector3D &normal);
        bool near_zero() const;
        Vector3D reflect(const Vector3D &n) const;
        Vector3D refract(const Vector3D &n, double etai_over_etat);
        Vector3D rotate(const Math::Matrix3D &rotation_matrix) const;
    };

    Vector3D operator * (double t, const Vector3D &vector);
}

#endif /* !VECTOR3D_HPP_ */
