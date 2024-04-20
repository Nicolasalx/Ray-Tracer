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
#include <thread>

std::size_t Rt::Interface::image_pixel_i = 0;
sf::Uint8 *Rt::Interface::image_pixel = nullptr;

std::mutex Rt::Raytracer::mutex;
std::atomic_bool Rt::Raytracer::end_rendering(false);

std::size_t Rt::Interface::image_size_x = 480;
std::size_t Rt::Interface::image_size_y = 270;

void Rt::Raytracer::launchRendering()
{
    Rt::ObjectList world;

    auto ground_material = std::make_shared<Lambertian>(Math::Color01(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Math::Point3D(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = Rt::Random::getBw01();
            Math::Point3D center(a + 0.9* Rt::Random::getBw01(), 0.2, b + 0.9*Rt::Random::getBw01());

            if ((center - Math::Point3D(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<IMaterial> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Math::Color01::random() * Math::Color01::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Math::Color01::random(0.5, 1);
                    auto fuzz = Rt::Random::get(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Math::Point3D(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Math::Color01(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Math::Point3D(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Math::Color01(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Math::Point3D(4, 1, 0), 1.0, material3));

    world = Rt::ObjectList(std::make_shared<Rt::BoundingNode>(world));

    Rt::Camera cam;

    cam.fov = 20;
    cam.image_width = 480;
    cam.image_height = 270;
    cam.samples_per_pixel = 20; // 20 - 100
    cam.max_depth = 10; // 10 - 50
    cam.nb_thread = 32;

    cam.lookfrom = Math::Point3D(13,2,3);
    cam.lookat   = Math::Point3D(0,0,0);
    cam.vup      = Math::Vector3D(0,1,0);

    cam.render(world);
}

int main(int argc, const char *argv[])
{
    try {
        Rt::Interface interface(480, 270);

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
