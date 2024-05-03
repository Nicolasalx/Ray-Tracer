/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
    #define SPHERE_HPP_

    #include "IObject.hpp"

namespace Rt
{
    class Sphere : public Rt::IObject
    {
    private:
        Math::Point3D center_;
        double radius_;
        std::shared_ptr<Rt::IMaterial> material_;

        static void get_sphere_uv(const Math::Point3D &p, double &u, double &v);

    public:
        Sphere(const Math::Point3D &center, double radius, std::shared_ptr<IMaterial> material)
            : center_(center), radius_(std::fmax(0, radius)), material_(material)
        {
        }
        Sphere(double radius, std::shared_ptr<IMaterial> material)
            : radius_(std::fmax(0, radius)), material_(material)
        {
        }

        bool hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const override;
    };
}

#endif /* !SPHERE_HPP_ */
