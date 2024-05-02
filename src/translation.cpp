/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** translation
*/

#include "Translation.hpp"

bool Rt::Translation::hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const
{
    Rt::Ray offset_r(ray.getOrigin() - offset_, ray.getDirection());

    if (!object_->hit(offset_r, ray_t, rec))
        return false;

    rec.pos += offset_;
    return true;
}