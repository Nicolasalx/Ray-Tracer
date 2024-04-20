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

namespace Math
{
    class Vector3D
    {
    protected:
        std::array<double, 3> vector = {0, 0, 0};

    public:
        Vector3D() = default;
        Vector3D(double x, double y, double z) : vector({x, y, z}) {}
        ~Vector3D() = default;

        double x() const { return vector[0]; }
        double y() const { return vector[1]; }
        double z() const { return vector[2]; }

        Vector3D operator - () const { return Vector3D(-vector[0], -vector[1], -vector[2]); }
        double operator [] (int i) const { return vector[i]; }
        double &operator [] (int i) { return vector[i]; }

        Vector3D &operator += (const Vector3D &other)
        {
            vector[0] += other.vector[0];
            vector[1] += other.vector[1];
            vector[2] += other.vector[2];
            return *this;
        }

        Vector3D &operator *= (double t)
        {
            vector[0] *= t;
            vector[1] *= t;
            vector[2] *= t;
            return *this;
        }

        Vector3D &operator /= (double t)
        {
            return *this *= 1 / t;
        }

        double length() const
        {
            return std::sqrt(length_squared());
        }

        double length_squared() const
        {
            return vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2];
        }

        Vector3D operator + (const Vector3D &other) const
        {
            return Vector3D(vector[0] + other.vector[0], vector[1] + other.vector[1], vector[2] + other.vector[2]);
        }

        Vector3D operator - (const Vector3D &other) const
        {
            return Vector3D(vector[0] - other.vector[0], vector[1] - other.vector[1], vector[2] - other.vector[2]);
        }

        Vector3D operator * (const Vector3D &other) const
        {
            return Vector3D(vector[0] * other.vector[0], vector[1] * other.vector[1], vector[2] * other.vector[2]);
        }

        Vector3D operator * (double t) const
        {
            return Vector3D(t * vector[0], t * vector[1], t * vector[2]);
        }

        Vector3D operator / (double t) const
        {
            return *this * (1 / t);
        }

        double dot(const Vector3D &other) const
        {
            return vector[0] * other[0]
                 + vector[1] * other[1]
                 + vector[2] * other[2];
        }

        Vector3D cross(const Vector3D &other) const
        {
            return Vector3D(vector[1] * other.vector[2] - vector[2] * other.vector[1],
                vector[2] * other.vector[0] - vector[0] * other.vector[2],
                vector[0] * other.vector[1] - vector[1] * other.vector[0]);
        }

        Vector3D unit_vector() const
        {
            return *this / this->length();
        }

        static Vector3D random()
        {
            return Vector3D(Rt::Random::getBw01(), Rt::Random::getBw01(), Rt::Random::getBw01());
        }

        static Vector3D random(double min, double max)
        {
            return Vector3D(Rt::Random::get(min, max), Rt::Random::get(min, max), Rt::Random::get(min, max));
        }

        static Vector3D random_in_unit_sphere()
        {
            while (true) {
                Vector3D p = Vector3D::random(-1, 1);
                if (p.length_squared() < 1) {
                    return p;
                }
            }
        }

        static Vector3D random_unit_vector()
        {
            return random_in_unit_sphere().unit_vector();
        }

        static Vector3D random_on_hemisphere(const Vector3D &normal)
        {
            Vector3D on_unit_sphere = random_unit_vector();
            if (on_unit_sphere.dot(normal) > 0) {
                return on_unit_sphere;
            } else {
                return -on_unit_sphere;
            }
        }

        bool near_zero() const
        {
            return (std::fabs(vector[0]) < 1e-8)
                && (std::fabs(vector[1]) < 1e-8)
                && (std::fabs(vector[2]) < 1e-8);
        }

        Vector3D reflect(const Vector3D &n) const
        {
            return *this - n * (2 * this->dot(n));
        }

        Vector3D refract(const Vector3D &n, double etai_over_etat)
        {
            double cos_theta = std::fmin((-(*this)).dot(n), 1.0);
            Vector3D r_out_perp = (*this + n * cos_theta) * etai_over_etat;
            Vector3D r_out_parallel = n * (-std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())));
            return r_out_perp + r_out_parallel;
        }
    };

    inline Vector3D operator * (double t, const Vector3D &vector)
    {
        return Vector3D(t * vector.x(), t * vector.y(), t * vector.z());
    }
}

#endif /* !VECTOR3D_HPP_ */
