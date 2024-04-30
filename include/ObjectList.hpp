/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** ObjectList
*/

#ifndef OBJECTLIST_HPP_
    #define OBJECTLIST_HPP_

    #include "IObject.hpp"
    #include <vector>
    #include <memory>

namespace Rt
{
    class ObjectList : public IObject
    {
    public:
        std::vector<std::shared_ptr<Rt::IObject>> objects;

        ObjectList() = default;
        ObjectList(std::shared_ptr<Rt::IObject> object)
        {
            add(object);
        }

        void clear()
        {
            objects.clear();
        }

        void add(std::shared_ptr<Rt::IObject> object)
        {
            objects.push_back(object);
        }

        bool hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const override
        {
            Rt::HitData temp_rec;
            bool hit_anything = false;
            auto closest_so_far = ray_t.max;

            for (const auto &object : objects) {
                if (object->hit(ray, Rt::Interval(ray_t.min, closest_so_far), temp_rec)) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;
        }
    };
}

#endif /* !OBJECTLIST_HPP_ */
