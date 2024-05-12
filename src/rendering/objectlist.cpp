/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** objectlist
*/

#include "ObjectList.hpp"

void Rt::ObjectList::clear()
{
    objects.clear();
}

void Rt::ObjectList::add(const std::shared_ptr<Rt::IObject> &object)
{
    objects.push_back(object);
}

bool Rt::ObjectList::hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const
{
    Rt::HitData temp_rec;
    bool hit_anything = false;
    double closest_so_far = ray_t.max;

    for (const std::shared_ptr<Rt::IObject> &object : objects) {
        if (object->hit(ray, Rt::Interval(ray_t.min, closest_so_far), temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}