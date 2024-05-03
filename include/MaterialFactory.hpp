/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** MaterialFactory
*/

#ifndef MATERIALFACTORY_HPP_
    #define MATERIALFACTORY_HPP_

    #include "IMaterial.hpp"

namespace Rt
{
    class MaterialFactory
    {
    public:
        template<typename T, typename ... Param>
        static std::shared_ptr<Rt::IMaterial> createMaterial(Param &&... param)
        {
            return std::make_shared<T>(std::forward<Param>(param) ...);
        }
    };
}

#endif /* !MATERIALFACTORY_HPP_ */
