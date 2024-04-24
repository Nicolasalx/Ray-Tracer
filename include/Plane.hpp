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
        Rt::BoundingBox bounding_box_;
        Math::Vector3D normal_;
        double d_;

    public:
        Plane(const Math::Point3D &pos, const Math::Vector3D &u, const Math::Vector3D &v, std::shared_ptr<IMaterial> material)
          : pos_(pos), u_(u), v_(v), material_(material)
        {
            auto n = u.cross(v);
            normal_ = n.unit_vector();
            d_ = normal_.dot(pos_);
            w_ = n / n.dot(n);
            set_bounding_box();
        }

        virtual void set_bounding_box()
        {
            auto bbox_diagonal1 = Rt::BoundingBox(pos_, pos_ + u_ + v_);
            auto bbox_diagonal2 = Rt::BoundingBox(pos_ + u_, pos_ + v_);
            bounding_box_ = Rt::BoundingBox(bbox_diagonal1, bbox_diagonal2);
        }

        Rt::BoundingBox getBoundingBox() const override
        {
            return bounding_box_;
        }

        bool hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitRecord &rec) const override
        {
             auto denom = normal_.dot(ray.getDirection());

            // No hit if the ray is parallel to the plane.
            if (std::fabs(denom) < 1e-8)
                return false;

            // Return false if the hit point parameter t is outside the ray interval.
            auto t = (d_ - normal_.dot(ray.getOrigin())) / denom;
            if (!ray_t.contains(t))
                return false;

            auto intersection = ray.at(t);
            Math::Vector3D planar_hitpt_vector = intersection - pos_;
            auto alpha = w_.dot(planar_hitpt_vector.cross(v_));
            auto beta = w_.dot(u_.cross(planar_hitpt_vector));

            if (!is_interior(alpha, beta, rec)) {
                return false;
            }
            rec.t = t;
            rec.pos = intersection;
            rec.material = material_;
            rec.set_face_normal(ray, normal_);

            return true;
        }

        virtual bool is_interior(double a, double b, Rt::HitRecord &rec) const
        {
            Rt::Interval unit_interval = Rt::Interval(0, 1);
            // Given the hit point in plane coordinates, return false if it is outside the
            // primitive, otherwise set the hit record UV coordinates and return true.

            if (!unit_interval.contains(a) || !unit_interval.contains(b))
                return false;

            rec.u = a;
            rec.v = b;
            return true;
        }
    };
}

#endif /* !PLANE_HPP_ */
