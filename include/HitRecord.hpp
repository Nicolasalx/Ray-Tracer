/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** HitRecord
*/

#ifndef HITRECORD_HPP_
    #define HITRECORD_HPP_

    #include "Vector3D.hpp"
    #include "Ray.hpp"
    #include <memory>
    #include "IMaterial.hpp"

namespace Rt
{
    class AMaterial;

    struct HitRecord
    {
        Math::Point3D pos;
        Math::Vector3D normal;
        double t;
        double u;
        double v;
        bool front_face;
        std::shared_ptr<Rt::IMaterial> material;

        void set_face_normal(const Rt::Ray &ray, const Math::Vector3D &outward_normal)
        {
            // Sets the hit record normal vector.
            // NOTE: the parameter `outward_normal` is assumed to have unit length.
            front_face = (ray.getDirection().dot(outward_normal) < 0);
            normal = front_face ? outward_normal : -outward_normal;
        }
    };
}

#endif /* !HITRECORD_HPP_ */
