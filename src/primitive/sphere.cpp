/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** sphere
*/

#include "Sphere.hpp"

bool Rt::Sphere::hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const
{
    Math::Vector3D oc = center_ - ray.getOrigin();
    double a = ray.getDirection().length_squared();
    double h = ray.getDirection().dot(oc);
    double c = oc.length_squared() - radius_ * radius_;
    double discriminant = h * h - a * c;

    if (discriminant < 0) {
        return false;
    }
    double sqrtd = std::sqrt(discriminant);

    double root = (h - sqrtd) / a;
    if (!ray_t.surrounds(root)) {
        root = (h + sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            return false;
        }
    }

    rec.t = root;
    rec.pos = ray.at(rec.t);
    Math::Vector3D outward_normal = (rec.pos - center_) / radius_;
    rec.set_face_normal(ray, outward_normal);
    Rt::Sphere::get_sphere_uv(outward_normal, rec.u, rec.v);
    rec.material = this->material_;

    return true;
}

void Rt::Sphere::get_sphere_uv(const Math::Point3D &p, double &u, double &v)
{
    double theta = std::acos(-p.y());
    double phi = std::atan2(-p.z(), p.x()) + std::numbers::pi;

    u = phi / (2 * std::numbers::pi);
    v = theta / std::numbers::pi;
}