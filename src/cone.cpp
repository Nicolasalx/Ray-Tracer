/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** cone
*/

#include "Cone.hpp"

bool Rt::Cone::hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const
{
    Math::Vector3D oc = ray.getOrigin() - center_;

    double k = radius_ / length_;
    double a = ray.getDirection().x() * ray.getDirection().x() + ray.getDirection().z() * ray.getDirection().z() - k * k * ray.getDirection().y() * ray.getDirection().y();
    double b = 2.0 * (oc.x() * ray.getDirection().x() + oc.z() * ray.getDirection().z() - k * k * oc.y() * ray.getDirection().y());
    double c = oc.x() * oc.x() + oc.z() * oc.z() - k * k * oc.y() * oc.y();

    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0)
    {
        double root1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
        double root2 = (-b + std::sqrt(discriminant)) / (2.0 * a);

        if (!ray_t.surrounds(root1) && !ray_t.surrounds(root2))
            return false;

        double hit_y1 = ray.getOrigin().y() + root1 * ray.getDirection().y();
        double hit_y2 = ray.getOrigin().y() + root2 * ray.getDirection().y();

        if (hit_y1 < center_.y() || hit_y1 > center_.y() + length_)
        {
            if (hit_y2 < center_.y() || hit_y2 > center_.y() + length_)
                return false;
            else
                root1 = root2;
        }

        double hit_y = ray.getOrigin().y() + root1 * ray.getDirection().y();
        rec.t = root1;
        rec.pos = ray.at(rec.t);
        Math::Vector3D outward_normal = Math::Vector3D((rec.pos.x() - center_.x()) / (1 - k * k), k * k, (rec.pos.z() - center_.z()) / (1 - k * k)).unit_vector();
                
        if (ray.getDirection().dot(outward_normal) > 0)
            outward_normal = -outward_normal;

        rec.set_face_normal(ray, outward_normal);
        rec.material = material_;

        double phi = std::atan2(outward_normal.x(), outward_normal.z());
        rec.u = 1 - (phi + std::numbers::pi) / (2 * std::numbers::pi);
        rec.v = (hit_y - center_.y()) / length_;

    return true;
    }

    return false;
}