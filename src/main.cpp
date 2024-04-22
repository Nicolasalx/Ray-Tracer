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
#include <libconfig.h++>

std::size_t Rt::Interface::image_pixel_i = 0;
sf::Uint8 *Rt::Interface::image_pixel = nullptr;

std::mutex Rt::Raytracer::mutex;
std::atomic_bool Rt::Raytracer::end_rendering(false);

std::size_t Rt::Interface::image_size_x = 480;
std::size_t Rt::Interface::image_size_y = 270;

void loadCfg(const std::string& configFile, Rt::ObjectList& world, Rt::Camera& cam)
{
    libconfig::Config cfg;
    try {
        cfg.readFile(configFile.c_str());
    } catch(const libconfig::FileIOException& fioex) {
        std::cerr << "Erreur lors de la lecture du fichier de configuration." << std::endl;
        return;
    } catch(const libconfig::ParseException& pex) {
        std::cerr << "Erreur de syntaxe dans le fichier de configuration à la ligne " << pex.getLine() << ": " << pex.getError() << std::endl;
        return;
    }

    const libconfig::Setting& cameraSettings = cfg.lookup("camera");
    const libconfig::Setting& primitivesSettings = cfg.lookup("primitives");
    const libconfig::Setting& res = cameraSettings["resolution"];
    const libconfig::Setting& pos = cameraSettings["position"];
    const libconfig::Setting& rot = cameraSettings["rotation"];
    int resolution_width = res["width"];
    int resolution_height = res["height"];
    int position_x = pos["x"];
    int position_y = pos["y"];
    int position_z = pos["z"];
    int rotation_x = rot["x"];
    int rotation_y = rot["y"];
    int rotation_z = rot["z"];
    float field_of_view;
    cameraSettings.lookupValue("fieldOfView", field_of_view);

    const libconfig::Setting& spheresSettings = primitivesSettings["spheres"];
    for (int i = 0; i < spheresSettings.getLength(); ++i) {
        const libconfig::Setting& sphere = spheresSettings[i];
        int x, y, z, r, color_r, color_g, color_b;
        sphere.lookupValue("x", x);
        sphere.lookupValue("y", y);
        sphere.lookupValue("z", z);
        sphere.lookupValue("r", r);
        const libconfig::Setting& color = sphere["color"];
        color.lookupValue("r", color_r);
        color.lookupValue("g", color_g);
        color.lookupValue("b", color_b);
    }

    const libconfig::Setting& planesSettings = primitivesSettings["planes"];
    for (int i = 0; i < planesSettings.getLength(); ++i) {
        const libconfig::Setting& plane = planesSettings[i];
        std::string axis;
        int position, color_r, color_g, color_b;
        plane.lookupValue("axis", axis);
        plane.lookupValue("position", position);
        const libconfig::Setting& color = plane["color"];
        color.lookupValue("r", color_r);
        color.lookupValue("g", color_g);
        color.lookupValue("b", color_b);
    }
}

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
        loadCfg(configFile, world, cam);

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

