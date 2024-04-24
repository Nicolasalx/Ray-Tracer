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

        static void get_sphere_uv(const Math::Point3D &p, double& u, double& v) {
            // p: a given point on the sphere of radius one, centered at the origin.
            // u: returned value [0,1] of angle around the Y axis from X=-1.
            // v: returned value [0,1] of angle from Y=-1 to Y=+1.
            //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
            //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
            //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

            auto theta = acos(-p.y());
            auto phi = atan2(-p.z(), p.x()) + M_PI;

            u = phi / (2*M_PI);
            v = theta / M_PI;
        }

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
            this->get_sphere_uv(outward_normal, rec.u, rec.v);
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
