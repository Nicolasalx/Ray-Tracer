/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Object
*/

#ifndef IOBJECT_HPP_
    #define IOBJECT_HPP_

    #include "Ray.hpp"
    #include "Point3D.hpp"
    #include "Interval.hpp"
    #include "HitRecord.hpp"
    #include "BoundingBox.hpp"

namespace Rt
{
    class IObject
    {
    public:
        virtual ~IObject() = default;

        virtual bool hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitRecord &rec) const = 0;
        virtual Rt::BoundingBox getBoundingBox() const = 0;
    };
}

#endif /* !IOBJECT_HPP_ */
