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
#include "TextureFactory.hpp"
#include <thread>
#include "LoadScene.hpp"
#include <libconfig.h++>

std::mutex Rt::Raytracer::mutex;
std::atomic_bool Rt::Raytracer::end_rendering(false);
std::atomic_bool Rt::Raytracer::close_window(false);

void Rt::Raytracer::launchRendering(Rt::ObjectList &world, Rt::Camera &camera)
{
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
