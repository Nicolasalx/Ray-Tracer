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
        Rt::BoundingBox bounding_box_;

    public:
        Sphere(const Math::Point3D &center, double radius, std::shared_ptr<IMaterial> material)
            : center_(center), radius_(std::fmax(0, radius)), material_(material)
        {
            Math::Vector3D rvec = Math::Vector3D(radius, radius, radius);
            bounding_box_ = Rt::BoundingBox(center - rvec, center + rvec);
        }

        bool hit(const Rt::Ray &r, Rt::Interval ray_t, Rt::HitRecord &rec) const override
        {
            Math::Vector3D oc = center_ - r.getOrigin();
            auto a = r.getDirection().length_squared();
            auto h = r.getDirection().dot(oc);
            auto c = oc.length_squared() - radius_ * radius_;

            auto discriminant = h*h - a*c;
            if (discriminant < 0)
                return false;

            auto sqrtd = sqrt(discriminant);

            // Find the nearest root that lies in the acceptable range.
            auto root = (h - sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                root = (h + sqrtd) / a;
                if (!ray_t.surrounds(root))
                    return false;
            }

            rec.t = root;
            rec.pos = r.at(rec.t);
            Math::Vector3D outward_normal = (rec.pos - center_) / radius_;
            rec.set_face_normal(r, outward_normal);
            rec.material = this->material_;

            return true;
        }

        Rt::BoundingBox getBoundingBox() const override
        {
            return bounding_box_;
        }
    };
}

#endif /* !SPHERE_HPP_ */
