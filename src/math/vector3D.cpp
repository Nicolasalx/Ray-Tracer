/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** vector3D
*/

#include "Vector3D.hpp"
#include "Matrix3D.hpp"

Math::Vector3D::Vector3D(double x, double y, double z)
    : vector({x, y, z})
{
}

double Math::Vector3D::x() const
{
    return vector[0];
}

double Math::Vector3D::y() const
{
    return vector[1];
}

double Math::Vector3D::z() const
{
    return vector[2];
}

Math::Vector3D Math::Vector3D::operator - () const
{
    return Math::Vector3D(-vector[0], -vector[1], -vector[2]);
}

double Math::Vector3D::operator [] (int i) const
{
    return vector[i];
}

double &Math::Vector3D::operator [] (int i)
{
    return vector[i];
}

Math::Vector3D &Math::Vector3D::operator += (const Math::Vector3D &other)
{
    vector[0] += other.vector[0];
    vector[1] += other.vector[1];
    vector[2] += other.vector[2];
    return *this;
}

Math::Vector3D &Math::Vector3D::operator *= (double t)
{
    vector[0] *= t;
    vector[1] *= t;
    vector[2] *= t;
    return *this;
}

Math::Vector3D &Math::Vector3D::operator /= (double t)
{
    return *this *= 1 / t;
}

double Math::Vector3D::length() const
{
    return std::sqrt(length_squared());
}

double Math::Vector3D::length_squared() const
{
    return vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2];
}

Math::Vector3D Math::Vector3D::operator + (const Math::Vector3D &other) const
{
    return Math::Vector3D(vector[0] + other.vector[0], vector[1] + other.vector[1], vector[2] + other.vector[2]);
}

Math::Vector3D Math::Vector3D::operator - (const Math::Vector3D &other) const
{
    return Math::Vector3D(vector[0] - other.vector[0], vector[1] - other.vector[1], vector[2] - other.vector[2]);
}

Math::Vector3D Math::Vector3D::operator * (const Math::Vector3D &other) const
{
    return Math::Vector3D(vector[0] * other.vector[0], vector[1] * other.vector[1], vector[2] * other.vector[2]);
}

Math::Vector3D Math::Vector3D::operator * (double t) const
{
    return Math::Vector3D(t * vector[0], t * vector[1], t * vector[2]);
}

Math::Vector3D Math::Vector3D::operator / (double t) const
{
    return *this * (1 / t);
}

double Math::Vector3D::dot(const Math::Vector3D &other) const
{
    return vector[0] * other[0]
            + vector[1] * other[1]
            + vector[2] * other[2];
}

Math::Vector3D Math::Vector3D::cross(const Math::Vector3D &other) const
{
    return Math::Vector3D(vector[1] * other.vector[2] - vector[2] * other.vector[1],
        vector[2] * other.vector[0] - vector[0] * other.vector[2],
        vector[0] * other.vector[1] - vector[1] * other.vector[0]);
}

Math::Vector3D Math::Vector3D::unit_vector() const
{
    return *this / this->length();
}

Math::Vector3D Math::Vector3D::random()
{
    return Math::Vector3D(Rt::Random::getBw01(), Rt::Random::getBw01(), Rt::Random::getBw01());
}

Math::Vector3D Math::Vector3D::random(double min, double max)
{
    return Math::Vector3D(Rt::Random::get(min, max), Rt::Random::get(min, max), Rt::Random::get(min, max));
}

Math::Vector3D Math::Vector3D::random_in_unit_sphere()
{
    while (true) {
        Math::Vector3D p = Math::Vector3D::random(-1, 1);
        if (p.length_squared() < 1) {
            return p;
        }
    }
}

Math::Vector3D Math::Vector3D::random_unit_vector()
{
    return random_in_unit_sphere().unit_vector();
}

Math::Vector3D Math::Vector3D::random_on_hemisphere(const Math::Vector3D &normal)
{
    Math::Vector3D on_unit_sphere = random_unit_vector();
    if (on_unit_sphere.dot(normal) > 0) {
        return on_unit_sphere;
    } else {
        return -on_unit_sphere;
    }
}

bool Math::Vector3D::near_zero() const
{
    return (std::fabs(vector[0]) < 1e-8)
        && (std::fabs(vector[1]) < 1e-8)
        && (std::fabs(vector[2]) < 1e-8);
}

Math::Vector3D Math::Vector3D::reflect(const Math::Vector3D &n) const
{
    return *this - n * (2 * this->dot(n));
}

Math::Vector3D Math::Vector3D::refract(const Math::Vector3D &n, double etai_over_etat) const
{
    double cos_theta = std::fmin((-(*this)).dot(n), 1.0);
    Math::Vector3D r_out_perp = (*this + n * cos_theta) * etai_over_etat;
    Math::Vector3D r_out_parallel = n * (-std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())));
    return r_out_perp + r_out_parallel;
}

Math::Vector3D Math::Vector3D::rotate(const Math::Matrix3D &rotation_matrix) const
{
    return rotation_matrix * (*this);
}

Math::Vector3D Math::operator * (double t, const Math::Vector3D &vector)
{
    return Vector3D(t * vector.x(), t * vector.y(), t * vector.z());
}

Math::Vector3D &Math::Vector3D::operator *= (const Math::Vector3D &other)
{
    vector[0] *= other.vector[0];
    vector[1] *= other.vector[1];
    vector[2] *= other.vector[2];
    return *this;
}

Math::Vector3D Math::Vector3D::operator / (const Math::Vector3D &other) const
{
    return Math::Vector3D(
        vector[0] / other.vector[0],
        vector[1] / other.vector[1],
        vector[2] / other.vector[2]);
}
