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

        static void get_sphere_uv(const Math::Point3D &p, double &u, double &v)
        {
            auto theta = std::acos(-p.y());
            auto phi = std::atan2(-p.z(), p.x()) + std::numbers::pi;

            u = phi / (2 * std::numbers::pi);
            v = theta / std::numbers::pi;
        }

    public:
        Sphere(const Math::Point3D &center, double radius, std::shared_ptr<IMaterial> material)
            : center_(center), radius_(std::fmax(0, radius)), material_(material)
        {
        }

        bool hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const override
        {
            Math::Vector3D oc = center_ - ray.getOrigin();
            auto a = ray.getDirection().length_squared();
            auto h = ray.getDirection().dot(oc);
            auto c = oc.length_squared() - radius_ * radius_;

            auto discriminant = h*h - a*c;
            if (discriminant < 0)
                return false;

            auto sqrtd = std::sqrt(discriminant);

            auto root = (h - sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                root = (h + sqrtd) / a;
                if (!ray_t.surrounds(root))
                    return false;
            }

            rec.t = root;
            rec.pos = ray.at(rec.t);
            Math::Vector3D outward_normal = (rec.pos - center_) / radius_;
            rec.set_face_normal(ray, outward_normal);
            this->get_sphere_uv(outward_normal, rec.u, rec.v);
            rec.material = this->material_;

            return true;
        }
    };
}

#endif /* !SPHERE_HPP_ */
