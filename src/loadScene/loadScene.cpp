/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** config
*/

#include <iostream>
#include "ObjectList.hpp"
#include "Camera.hpp"
#include "LoadScene.hpp"
#include "my_tracked_exception.hpp"
#include <filesystem>

void Rt::LoadScene::parseArgs(int argc, const char **argv)
{
    if (argc < 2) {
        throw my::tracked_exception("Bad number of arguments (minimum 1 scene required).");
    }
    for (int i = 1; i < argc; ++i) {
        if (!std::filesystem::is_directory(argv[i])) {
            _listConfigFile.push_back(argv[i]);
        } else {
            throw my::tracked_exception("The provided file is a directory.");
        }
    }
}

void Rt::LoadScene::parseLight(libconfig::Config &cfg, Rt::ObjectList &world)
{
    const libconfig::Setting &lightsSettings = cfg.lookup("lights");
}

void Rt::LoadScene::parseCamera(libconfig::Config &cfg, Rt::Camera &camera)
{
    const libconfig::Setting &cameraSettings = cfg.lookup("camera");
    const libconfig::Setting &resolution = cameraSettings["resolution"];
    const libconfig::Setting &position = cameraSettings["position"];
    const libconfig::Setting &look_from = cameraSettings["look_from"];
    const libconfig::Setting &look_at = cameraSettings["look_at"];
    const libconfig::Setting &vup = cameraSettings["vup"];
    const libconfig::Setting &background = cameraSettings["background"];

    float fov = 0.0;
    int nb_thread = 0;
    int max_depth = 0;
    int samples_per_pixel = 0;

    cameraSettings.lookupValue("fov", fov);
    cameraSettings.lookupValue("nb_thread", nb_thread);
    cameraSettings.lookupValue("max_depth", max_depth);
    cameraSettings.lookupValue("samples_per_pixel", samples_per_pixel);

    std::vector<int> vectorResolution = parseVector2D(resolution);
    std::vector<int> vectorLookFrom = parseVector3D(look_from);
    std::vector<int> vectorLookAt = parseVector3D(look_at);
    std::vector<int> vectorVup = parseVector3D(vup);
    std::vector<int> vectorBackground = parseVector3D(background);

    camera.fov = fov;
    camera.nb_thread = nb_thread;
    camera.max_depth = max_depth;
    camera.samples_per_pixel = samples_per_pixel;
    camera.image_width = vectorResolution.at(0);
    camera.image_height = vectorResolution.at(1);
    camera.lookfrom = Math::Point3D(vectorLookFrom.at(0), vectorLookFrom.at(1), vectorLookFrom.at(2));
    camera.lookat = Math::Point3D(vectorLookAt.at(0), vectorLookAt.at(1), vectorLookAt.at(2));
    camera.vup = Math::Point3D(vectorVup.at(0), vectorVup.at(1), vectorVup.at(2));
    camera.background = Math::Point3D(vectorBackground.at(0), vectorBackground.at(1), vectorBackground.at(2));
}

void Rt::LoadScene::loadScene(const std::string &filepath, Rt::ObjectList &world, Rt::Camera &camera)
{
    libconfig::Config cfg;

    try {
        cfg.readFile(filepath.c_str());
        parseMaterials(cfg);
        parsePrimitives(cfg, world);
        parseLight(cfg, world);
        parseCamera(cfg, camera);
    } catch(const libconfig::FileIOException &fioex) {
        throw my::tracked_exception("Can't open configuration file to parse the scene.");
    } catch(const libconfig::ParseException &pex) {
        std::cerr << "Syntax error in the configuration file at line " << pex.getLine() << ": " << pex.getError() << std::endl; // ! Delete after with the return (set error in the throw)
        throw my::tracked_exception("Syntax error in the configuration file.");
        return;
    }
}

void Rt::LoadScene::loadAllScenes(Rt::ObjectList &world, Rt::Camera &camera)
{
    // Les couleurs doivent etre rendu sur une échelle de 0 à 1 (/255.0 et pas /255 => division à virgule et pas entière)

    // Créer comme cela :
    // world.add(std::make_shared<Rt::Plane>(Math::Point3D(343, 554, 332), Math::Vector3D(-130,0,0), Math::Vector3D(0,0,-105), light));

    for (const auto &filepath: _listConfigFile) {
        loadScene(filepath, world, camera);
    }
}
