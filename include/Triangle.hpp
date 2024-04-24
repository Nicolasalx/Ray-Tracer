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
        Triangle(const Math::Point3D &origin, const Math::Vector3D &aa, const Math::Vector3D &ab, std::shared_ptr<Rt::IMaterial> material)
            : Rt::Plane(origin, aa, ab, material)
        {}
        ~Triangle() = default;

        bool is_interior(double a, double b, Rt::HitRecord &rec) const override
        {
            if ((a < 0) || (b < 0) || (a + b > 1))
                return false;

            rec.u = a;
            rec.v = b;
            return true;
        }
    };
}

#endif /* !TRIANGLE_HPP_ */
