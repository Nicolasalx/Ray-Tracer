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
            add(std::move(object));
        }

        void clear();

        void add(std::shared_ptr<Rt::IObject> object);

        bool hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const override;
    };
}

#endif /* !OBJECTLIST_HPP_ */
