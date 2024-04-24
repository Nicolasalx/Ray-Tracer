/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Raytracer
*/

#ifndef RAYTRACER_HPP_
    #define RAYTRACER_HPP_

    #include "IObject.hpp"
    #include "Camera.hpp"
    #include "ObjectList.hpp"
    #include <mutex>
    #include <atomic>

namespace Rt
{
    class Raytracer
    {
    public:
        ~Raytracer() = default;

        static void launchRendering();
        static void createObjModel(Rt::ObjectList &world ,const std::string &path);

        static std::mutex mutex;
        static std::atomic_bool end_rendering;
    };
}

#endif /* !RAYTRACER_HPP_ */
