/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Rotation
*/

#ifndef ROTATION_HPP_
    #define ROTATION_HPP_

    #include "IObject.hpp"
    #include "Matrix3D.hpp"

namespace Rt
{
    class Rotation : public IObject
    {
    private:
        std::shared_ptr<Rt::IObject> object_;
        Math::Vector3D angle_;

        Math::Matrix3D rotationMatrix(const Math::Vector3D &angles) const;

    public:
        Rotation(const std::shared_ptr<Rt::IObject> object, Math::Vector3D angle)
            : object_(std::move(object)), angle_(Math::Vector3D(
                angle.x() * (std::numbers::pi / 180.0),
                angle.y() * (std::numbers::pi / 180.0),
                angle.z() * (std::numbers::pi / 180.0)))
        {
        }

        bool hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const override;
    };
}

#endif /* !ROTATION_HPP_ */
