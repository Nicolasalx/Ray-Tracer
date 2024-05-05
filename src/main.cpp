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
#include "Cylinder.hpp"
#include "Cone.hpp"
#include "Translation.hpp"
#include "Rotation.hpp"
#include "Builder.hpp"
#include "MaterialFactory.hpp"
#include <thread>
#include <libconfig.h++>

std::mutex Rt::Raytracer::mutex;
std::atomic_bool Rt::Raytracer::end_rendering(false);

void Rt::Raytracer::launchRendering()
{
    Rt::ObjectList world;

    std::shared_ptr<Rt::IMaterial> red = std::make_shared<Rt::Lambertian>(Math::Color01(1, 0, 0));
//    std::shared_ptr<Rt::ITexture> chess_bord = std::make_shared<Rt::ChessTexture>(25, Math::Color01(1, 0, 0), Math::Color01(0, 1, 1));
    std::shared_ptr<Rt::ITexture> chess_bord = std::make_shared<Rt::ImageTexture>("texture/cyberpunk_2077.png");
    std::shared_ptr<Rt::IMaterial> chess_mat = std::make_shared<Rt::Lambertian>(chess_bord);
    auto white = std::make_shared<Rt::Lambertian>(Math::Color01(0.73, 0.73, 0.73));
    auto green = std::make_shared<Rt::Lambertian>(Math::Color01(0, 1, 0));
    auto light = std::make_shared<Rt::DiffuseLight>(Math::Color01(1 * 20, 1 * 20, 1 * 20));

    world.add(std::make_shared<Rt::Plane>(Math::Point3D(555,0,0), Math::Vector3D(0,555,0), Math::Vector3D(0,0,555), white));
    world.add(std::make_shared<Rt::Plane>(Math::Point3D(0,0,0), Math::Vector3D(0,555,0), Math::Vector3D(0,0,555), white));
    world.add(std::make_shared<Rt::Plane>(Math::Point3D(343, 554, 332), Math::Vector3D(-130,0,0), Math::Vector3D(0,0,-105), light));
    world.add(std::make_shared<Rt::Plane>(Math::Point3D(0,0,0), Math::Vector3D(555,0,0), Math::Vector3D(0,0,555), white));
    world.add(std::make_shared<Rt::Plane>(Math::Point3D(555,555,555), Math::Vector3D(-555,0,0), Math::Vector3D(0,0,-555), white));
    world.add(std::make_shared<Rt::Plane>(Math::Point3D(0,0,555), Math::Vector3D(555,0,0), Math::Vector3D(0,555,0), white));

    // world.add(Rt::Builder::createObject<Rt::Cone>(
//         Math::Vector3D(555 / 2., 250, 555 / 2.),
        // Math::Vector3D(0, 0, 180),
        // Rt::MaterialFactory::createMaterial<Rt::Lambertian>(Math::Color01(1, 0, 0)),
        // 100.0, 250.0));

    Rt::Camera cam;

    cam.fov = 40;
    cam.image_width = Rt::Interface::image_size_x;
    cam.image_height = Rt::Interface::image_size_y;
    cam.samples_per_pixel = 250; // 20 - 100
    cam.max_depth = 3; // 10 - 50
    cam.nb_thread = 32;

    cam.lookfrom = Math::Point3D(278, 278, -800);
    cam.lookat = Math::Point3D(278, 278, 0);
    cam.vup = Math::Vector3D(0,1,0);
    cam.background = Math::Color01(0, 0, 0);

    cam.render(world);
}

int main(int argc, const char *argv[])
{
    std::srand(std::time(nullptr));
    try {
        Rt::Interface interface(1080 / 8, 1080 / 8);

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
