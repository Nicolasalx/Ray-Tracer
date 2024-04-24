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

    auto material_ground = std::make_shared<Lambertian>(Math::Color01(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Math::Color01(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<Dielectric>(1.50);
    auto material_bubble = std::make_shared<Dielectric>(1.00 / 1.50);
    auto material_right  = std::make_shared<Metal>(Math::Color01(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<Sphere>(Math::Point3D( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Math::Point3D( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(std::make_shared<Sphere>(Math::Point3D(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(Math::Point3D(-1.0,    0.0, -1.0),   0.4, material_bubble));
    world.add(std::make_shared<Sphere>(Math::Point3D( 1.0,    0.0, -1.0),   0.5, material_right));

    Rt::Camera cam;

    cam.fov = 90;
    cam.image_width = 480;
    cam.image_height = 270;
    cam.samples_per_pixel = 20; // 20 - 100
    cam.max_depth = 10; // 10 - 50
    cam.nb_thread = 32;

    cam.lookfrom = Math::Point3D(-2,2,1);
    cam.lookat   = Math::Point3D(0,0,-1);
    cam.vup      = Math::Vector3D(0,1,0);

    cam.render(world);
}

int main(int argc, const char *argv[]) {
    try {
        Rt::Interface interface(480, 270);
        std::string configFile = "simple_scene";
        Rt::ObjectList world;
        Rt::Camera cam;
        // loadCfg(configFile, world, cam);

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

