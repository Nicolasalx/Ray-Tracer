/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** plane
*/

#include "Plane.hpp"

bool Rt::Plane::is_interior(double a, double b, Rt::HitData &rec) const
{
    Rt::Interval unit_interval = Rt::Interval(0, 1);

    if (!unit_interval.contains(a) || !unit_interval.contains(b))
        return false;

    rec.u = a;
    rec.v = b;
    return true;
}

bool Rt::Plane::hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const
{
    auto denom = normal_.dot(ray.getDirection());

    if (std::fabs(denom) < 1e-8)
        return false;

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