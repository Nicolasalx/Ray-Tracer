/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Ray
*/

#ifndef RAY_HPP_
    #define RAY_HPP_

    #include "Point3D.hpp"
    #include "Vector3D.hpp"

namespace Rt
{
    class Ray
    {
    private:
        Math::Point3D origin_;
        Math::Vector3D direction_;

    public:
        Ray() = default;
        Ray(const Math::Point3D &origin, const Math::Vector3D &direction)
            : origin_(origin), direction_(direction) {}
        ~Ray() = default;

        const Math::Point3D &getOrigin() const { return origin_; }
        const Math::Vector3D &getDirection() const { return direction_; }

        Math::Point3D at(double t) const
        {
            return origin_ + direction_ * t;
        }

        Rt::Ray rotate(const Math::Matrix3D &rotation_matrix) const
        {
            return Rt::Ray(this->origin_.rotate(rotation_matrix), this->direction_.rotate(rotation_matrix));
        }
    };
}

#endif /* !RAY_HPP_ */
