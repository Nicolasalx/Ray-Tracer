/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Plane
*/

#ifndef PLANE_HPP_
    #define PLANE_HPP_

    #include "IObject.hpp"

namespace Rt
{
    class Plane : public Rt::IObject
    {
    private:
        Math::Point3D pos_;
        Math::Vector3D u_;
        Math::Vector3D v_;
        Math::Vector3D w_;
        std::shared_ptr<Rt::IMaterial> material_;
        Math::Vector3D normal_;
        double d_ = 0.0;

    public:
        Plane() = default;
        Plane(const Math::Point3D &pos, const Math::Vector3D &u,
        const Math::Vector3D &v, std::shared_ptr<IMaterial> material)
          : pos_(pos), u_(u), v_(v), material_(std::move(material))
        {
            Math::Vector3D n = u.cross(v);
            normal_ = n.unit_vector();
            d_ = normal_.dot(pos_);
            w_ = n / n.dot(n);
        }
        Plane(double height, double width, std::shared_ptr<IMaterial> material)
            : material_(std::move(material))
        {
            u_ = Math::Vector3D(-width, 0, 0);
            v_ = Math::Vector3D(0, height, 0);
            Math::Vector3D n = u_.cross(v_);
            normal_ = n.unit_vector();
            d_ = normal_.dot(pos_);
            w_ = n / n.dot(n);
        }

        bool hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const override;

        virtual bool is_interior(double a, double b, Rt::HitData &rec) const;
    };
}

#endif /* !PLANE_HPP_ */
