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
#include "BoundingNode.hpp"
#include "TextureChecker.hpp"
#include "ImageTexture.hpp"
#include "Plane.hpp"
#include "Triangle.hpp"
#include "DiffuseLight.hpp"
#include "FileObj.hpp"
#include <thread>
#include <libconfig.h++>

std::size_t Rt::Interface::image_pixel_i = 0;
sf::Uint8 *Rt::Interface::image_pixel = nullptr;

std::mutex Rt::Raytracer::mutex;
std::atomic_bool Rt::Raytracer::end_rendering(false);

std::size_t Rt::Interface::image_size_x = 480;
std::size_t Rt::Interface::image_size_y = 270;

void Rt::Raytracer::launchRendering()
{
    Rt::ObjectList world;

    auto red   = std::make_shared<Rt::Lambertian>(Math::Color01(0.65, 0.05, 0.05));
    auto white = std::make_shared<Rt::Lambertian>(Math::Color01(0.73, 0.73, 0.73));
    auto green = std::make_shared<Rt::Lambertian>(Math::Color01(0.12, 0.45, 0.15));
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
    cam.samples_per_pixel = 50; // 20 - 100
    cam.max_depth = 10; // 10 - 50
    cam.nb_thread = 32;

    cam.lookfrom = Math::Point3D(278,278,-800);
    cam.lookat   = Math::Point3D(278,278,0);
    cam.vup      = Math::Vector3D(0,1,0);
    cam.background = Math::Color01(0, 0, 0);

    cam.render(world);
}

int main(int argc, const char *argv[]) {

    try {
        Rt::Interface interface(Rt::Interface::image_size_x, Rt::Interface::image_size_y);

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

