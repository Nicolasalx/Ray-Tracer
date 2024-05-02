/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Translation
*/

#ifndef TRANSLATION_HPP_
    #define TRANSLATION_HPP_

    #include "IObject.hpp"

namespace Rt
{
    class Translation : public Rt::IObject
    {
    private:
        std::shared_ptr<Rt::IObject> object_;
        Math::Vector3D offset_;

    public:
        Translation(std::shared_ptr<Rt::IObject> object, const Math::Vector3D &offset)
            : object_(object), offset_(offset)
        {
        }

        bool hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const override
        {
            Rt::Ray offset_r(ray.getOrigin() - offset_, ray.getDirection());

            if (!object_->hit(offset_r, ray_t, rec))
                return false;

            rec.pos += offset_;
            return true;
        }
    };
}

#endif /* !TRANSLATION_HPP_ */
