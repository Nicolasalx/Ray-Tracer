/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-tekspice-thibaud.cathala
** File description:
** main
*/

#include <iostream>
#include <memory>
#include <stdexcept>
#include "my_log.hpp"
#include "Color01.hpp"
#include "ColorRGB.hpp"
#include "ObjectList.hpp"
#include "IObject.hpp"
#include "Sphere.hpp"
#include <vector>
#include <iomanip>
#include "Ray.hpp"
#include "Camera.hpp"
#include "Raytracer.hpp"
#include "Interface.hpp"
#include "Metal.hpp"
#include "Lambertian.hpp"
#include "Dielectric.hpp"
#include "ChessTexture.hpp"
#include "ImageTexture.hpp"
#include "Plane.hpp"
#include "Triangle.hpp"
#include "DiffuseLight.hpp"
#include "FileObj.hpp"
#include <thread>
#include <libconfig.h++>

std::mutex Rt::Raytracer::mutex;
std::atomic_bool Rt::Raytracer::end_rendering(false);

void Rt::Raytracer::launchRendering()
{
    Rt::ObjectList world;

    auto red   = std::make_shared<Rt::Lambertian>(Math::Color01(1, 0, 0));
    auto white = std::make_shared<Rt::Lambertian>(Math::Color01(0.73, 0.73, 0.73));
    auto green = std::make_shared<Rt::Lambertian>(Math::Color01(0, 1, 0));
    auto light = std::make_shared<Rt::DiffuseLight>(Math::Color01(15, 15, 15));

    world.add(std::make_shared<Rt::Plane>(Math::Point3D(555,0,0), Math::Vector3D(0,555,0), Math::Vector3D(0,0,555), green));
    world.add(std::make_shared<Rt::Plane>(Math::Point3D(0,0,0), Math::Vector3D(0,555,0), Math::Vector3D(0,0,555), red));
    world.add(std::make_shared<Rt::Plane>(Math::Point3D(343, 554, 332), Math::Vector3D(-130,0,0), Math::Vector3D(0,0,-105), light));
    world.add(std::make_shared<Rt::Plane>(Math::Point3D(0,0,0), Math::Vector3D(555,0,0), Math::Vector3D(0,0,555), white));
    world.add(std::make_shared<Rt::Plane>(Math::Point3D(555,555,555), Math::Vector3D(-555,0,0), Math::Vector3D(0,0,-555), white));
    world.add(std::make_shared<Rt::Plane>(Math::Point3D(0,0,555), Math::Vector3D(555,0,0), Math::Vector3D(0,555,0), white));

    Rt::Camera cam;

    cam.fov = 40;
    cam.image_width = Rt::Interface::image_size_x;
    cam.image_height = Rt::Interface::image_size_y;
    cam.samples_per_pixel = 100; // 20 - 100
    cam.max_depth = 20; // 10 - 50
    cam.nb_thread = 32;

    cam.lookfrom = Math::Point3D(278,278,-800);
    cam.lookat   = Math::Point3D(278,278,0);
    cam.vup      = Math::Vector3D(0,1,0);
    cam.background = Math::Color01(0, 0, 0);

    cam.render(world);
}

int main(int argc, const char *argv[])
{
    std::srand(std::time(nullptr));
    try {
        Rt::Interface interface(1920 / 8, 1080 / 8);

        std::thread render_thread(Rt::Raytracer::launchRendering);
        interface.loop();
        Rt::Raytracer::end_rendering = true;
        render_thread.join();
    } catch (const std::exception &exception) {
        my::log::error(exception.what());
        return 84;
    }
    return 0;
}
