/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** raytracer
*/

#include "Raytracer.hpp"

std::mutex Rt::Raytracer::mutex;
std::atomic_bool Rt::Raytracer::end_rendering(false);
std::atomic_bool Rt::Raytracer::close_window(false);

void Rt::Raytracer::launchRendering(Rt::ObjectList &world, Rt::Camera &camera)
{
    std::srand(std::time(nullptr));
    camera.render(world);
}
