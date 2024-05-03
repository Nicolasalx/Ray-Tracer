/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Builder
*/

#ifndef BUILDER_HPP_
    #define BUILDER_HPP_

    #include "IObject.hpp"
    #include "IMaterial.hpp"
    #include "Sphere.hpp"
    #include "Plane.hpp"
    #include "Triangle.hpp"
    #include "Cone.hpp"
    #include "Cylinder.hpp"

    #include "Translation.hpp"
    #include "Rotation.hpp"

namespace Rt
{
    class Builder
    {
    public:
        template<typename T, typename ... Param>
        static std::shared_ptr<Rt::IObject> createObject(
            const Math::Vector3D &translation, const Math::Vector3D &rotation,
            std::shared_ptr<Rt::IMaterial> material, Param &&... param)
        {
            std::shared_ptr<Rt::IObject> object_ = std::make_shared<T>(std::forward<Param>(param)..., material);
            object_ = std::make_shared<Rt::Rotation>(object_, rotation);
            object_ = std::make_shared<Rt::Translation>(object_, translation);
            return object_;
        }
    };
}

#endif /* !BUILDER_HPP_ */
