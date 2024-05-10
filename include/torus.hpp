/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** torus
*/

#ifndef TORUS_HPP_
    #define TORUS_HPP_

    #include "IObject.hpp"

namespace Rt
{
    class torus : public Rt::IObject
    {
    private:
        Math::Point3D center_;
        double radius_;
        double length_;
        std::shared_ptr<Rt::IMaterial> material_;

    public:
        torus(const Math::Point3D &center, double radius, double lenght, std::shared_ptr<IMaterial> material)
            : center_(center), radius_(std::fmax(0, radius)), length_(std::fmax(0, lenght)), material_(material)
        {
        }

        bool hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const override;
    };
}

#endif /* !TORUS_HPP_ */