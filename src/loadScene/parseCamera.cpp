/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** parseCamera
*/

#include "Camera.hpp"
#include "LoadScene.hpp"

void Rt::LoadScene::parseCamera(libconfig::Config &cfg, Rt::Camera &camera)
{
    const libconfig::Setting &cameraSettings = cfg.lookup("camera");
    const libconfig::Setting &resolution = cameraSettings["resolution"];
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
    std::vector<double> vectorBackground = parseColorMul(background);

    camera.fov = fov;
    camera.nb_thread = nb_thread;
    camera.max_depth = max_depth;
    camera.samples_per_pixel = samples_per_pixel;
    camera.image_width = vectorResolution.at(0);
    camera.image_height = vectorResolution.at(1);
    camera.lookfrom = Math::Point3D(vectorLookFrom.at(0), vectorLookFrom.at(1), vectorLookFrom.at(2));
    camera.lookat = Math::Point3D(vectorLookAt.at(0), vectorLookAt.at(1), vectorLookAt.at(2));
    camera.vup = Math::Point3D(vectorVup.at(0), vectorVup.at(1), vectorVup.at(2));
    camera.background = Math::Color01(vectorBackground.at(0) * vectorBackground.at(3), vectorBackground.at(1) * vectorBackground.at(3), vectorBackground.at(2) * vectorBackground.at(3));
}
