/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** HitData
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

    struct HitData
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
            if (ray.getDirection().dot(outward_normal) < 0) {
                normal = outward_normal;
            } else {
                normal = -outward_normal;
            }
        }
    };
}

#endif /* !HITRECORD_HPP_ */
