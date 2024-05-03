/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
    #define CYLINDER_HPP_

    #include "IObject.hpp"

namespace Rt
{
    class Cylinder : public Rt::IObject
    {
    private:
        Math::Point3D center_;
        double radius_;
        double length_;
        std::shared_ptr<Rt::IMaterial> material_;

    public:
        Cylinder(const Math::Point3D &center, double radius, double length, std::shared_ptr<IMaterial> material)
            : center_(center), radius_(std::fmax(0, radius)), length_(std::fmax(0, length)), material_(material)
        {
        }
        Cylinder(double radius, double length, std::shared_ptr<IMaterial> material)
            : radius_(std::fmax(0, radius)), length_(std::fmax(0, length)), material_(material)
        {
        }

        bool hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const override;
    };
}

#endif /* !CYLINDER_HPP_ */
