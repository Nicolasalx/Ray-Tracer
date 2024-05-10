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
#include "LoadScene.hpp"
#include <libconfig.h++>

std::mutex Rt::Raytracer::mutex;
std::atomic_bool Rt::Raytracer::end_rendering(false);

void Rt::Raytracer::launchRendering(Rt::ObjectList &world, Rt::Camera &camera)
{
    std::shared_ptr<Rt::IMaterial> red = std::make_shared<Rt::Lambertian>(Math::Color01(1, 0, 0));
    auto white = std::make_shared<Rt::Lambertian>(Math::Color01(0.73, 0.73, 0.73));
    auto green = std::make_shared<Rt::Lambertian>(Math::Color01(0, 1, 0));
    auto light = std::make_shared<Rt::DiffuseLight>(Math::Color01(1 * 20, 1 * 20, 1 * 20));
    camera.render(world);
}

int main(int argc, const char *argv[])
{
    Rt::LoadScene allScenes;
    Rt::ObjectList world;
    Rt::Camera camera;

    std::srand(std::time(nullptr));
    try {
        allScenes.parseArgs(argc, argv);
        allScenes.loadAllScenes(world, camera);
        Rt::Interface interface(camera.image_width, camera.image_height);

        std::thread render_thread([&](){ Rt::Raytracer::launchRendering(world, camera); });
        interface.loop();
        Rt::Raytracer::end_rendering = true;
        render_thread.join();
    } catch (const std::exception &exception) {
        my::log::error(exception.what());
        return 84;
    } catch (...) {
        my::log::error("Unknow error.");
        return 84;
    }
    return 0;
}
