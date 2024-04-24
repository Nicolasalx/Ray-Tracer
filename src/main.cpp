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

void Rt::Raytracer::createObjModel(Rt::ObjectList &world ,const std::string &path)
{
    auto left_red     = std::make_shared<Rt::Lambertian>(Math::Color01(1.0, 0.2, 0.2));

    FileObj obj(path);
    FaceList faceList = obj.getFaceList();
    for (auto face : faceList) {
        for (int i = 0; i < face.size() - 2; i++) {
            std::cout << face[0][0] << " " << face[0][1] << " " << face[0][2] << " ";
            std::cout << face[i + 1][0] << " " << face[i + 1][1] << " " << face[i + 1][2] << " ";
            std::cout << face[i + 2][0] << " " << face[i + 2][1] << " " << face[i + 2][2] << " \n";
            world.add(std::make_shared<Rt::Triangle>(Math::Point3D(face[0][0],face[0][1],face[0][2]),
            Math::Point3D(face[i + 1][0], face[i + 1][1],face[i + 1][2]), Math::Point3D(face[i + 2][0] ,face[i + 2][1] ,face[i + 2][2]), left_red));
            // world.add(std::make_shared<Rt::Triangle>(Math::Point3D(0,0, 0),
            // Math::Point3D(1, 0,0), Math::Point3D(1 ,1, 0), left_red));
        }
    }
    obj.printFaceList();
}

void Rt::Raytracer::launchRendering()
{
    Rt::ObjectList world;


    auto left_red     = std::make_shared<Rt::Lambertian>(Math::Color01(1.0, 0.2, 0.2));
    auto back_green   = std::make_shared<Rt::Lambertian>(Math::Color01(0.2, 1.0, 0.2));
    auto right_blue   = std::make_shared<Rt::Lambertian>(Math::Color01(0.2, 0.2, 1.0));
    auto upper_orange = std::make_shared<Rt::Lambertian>(Math::Color01(1.0, 0.5, 0.0));
    auto lower_teal   = std::make_shared<Rt::Lambertian>(Math::Color01(0.2, 0.8, 0.8));

    createObjModel(world, "assets/vaisseau.obj");
    auto difflight = std::make_shared<Rt::DiffuseLight>(Math::Color01(10,10,10));
    world.add(std::make_shared<Rt::Sphere>(Math::Point3D(0,0,0), 0.3, difflight));

    // Quads
    // world.add(std::make_shared<Rt::Plane>(Math::Point3D(-3,-2, 5), Math::Vector3D(0, 0,-4), Math::Vector3D(0, 4, 0), left_red));
    // world.add(std::make_shared<Rt::Plane>(Math::Point3D(-2,-2, 0), Math::Vector3D(4, 0, 0), Math::Vector3D(0, 4, 0), back_green));
    // world.add(std::make_shared<Rt::Plane>(Math::Point3D( 3,-2, 1), Math::Vector3D(0, 0, 4), Math::Vector3D(0, 4, 0), right_blue));
    // world.add(std::make_shared<Rt::Plane>(Math::Point3D(-2, 3, 1), Math::Vector3D(4, 0, 0), Math::Vector3D(0, 0, 4), upper_orange));
    // world.add(std::make_shared<Rt::Plane>(Math::Point3D(-2,-3, 5), Math::Vector3D(4, 0, 0), Math::Vector3D(0, 0,-4), lower_teal));

    

    Rt::Camera cam;

    cam.fov = 90;
    cam.image_width = Rt::Interface::image_size_x;
    cam.image_height = Rt::Interface::image_size_y;
    cam.samples_per_pixel = 20; // 20 - 100
    cam.max_depth = 20; // 10 - 50
    cam.nb_thread = 32;

    cam.lookfrom = Math::Point3D(10,5,10);
    cam.lookat   = Math::Point3D(0,0,0);
    cam.vup      = Math::Vector3D(0,1,0);
    cam.background = Math::Color01(0.3, 0.3, 0.3);

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

