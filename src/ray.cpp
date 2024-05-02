/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** ray
*/

#include "Ray.hpp"

const Math::Point3D &Rt::Ray::getOrigin() const
{
    return origin_;
}

const Math::Vector3D &Rt::Ray::getDirection() const
{
    return direction_;
}

Math::Point3D Rt::Ray::at(double t) const
{
    return origin_ + direction_ * t;
}

Rt::Ray Rt::Ray::rotate(const Math::Matrix3D &rotation_matrix) const
{
    return Rt::Ray(this->origin_.rotate(rotation_matrix), this->direction_.rotate(rotation_matrix));
}