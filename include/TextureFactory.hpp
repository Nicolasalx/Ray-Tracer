/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** TextureFactory
*/

#ifndef TEXTUREFACTORY_HPP_
    #define TEXTUREFACTORY_HPP_

    #include "IMaterial.hpp"
    #include "ITexture.hpp"

namespace Rt
{
    class TextureFactory
    {
    public:
        template<typename T, typename ... Param>
        static std::shared_ptr<Rt::ITexture> createTexture(Param &&... param)
        {
            return std::make_shared<T>(std::forward<Param>(param) ...);
        }
    };
}

#endif /* !TEXTUREFACTORY_HPP_ */
