/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Triangle
*/

#ifndef TRIANGLE_HPP_
    #define TRIANGLE_HPP_

    #include "Plane.hpp"

namespace Rt
{
    class Triangle : public Rt::Plane
    {
    public:
        Triangle(const Math::Point3D &origin, const Math::Point3D &pointA, const Math::Point3D &pointB, std::shared_ptr<Rt::IMaterial> material)
            : Rt::Plane(origin, pointA - origin, pointB - origin, material)
        {}
        ~Triangle() = default;

        bool is_interior(double a, double b, Rt::HitData &rec) const override;
    };
}

#endif /* !TRIANGLE_HPP_ */