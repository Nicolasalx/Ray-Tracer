/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** parseCamera
*/

#include "Camera.hpp"
#include "LoadScene.hpp"

void Rt::LoadScene::parseCamera(const libconfig::Config &cfg, Rt::Camera &camera) const
{
    const libconfig::Setting &cameraSettings = cfg.lookup("camera");

    float fov = 0.0;
    int nb_thread = 0;
    int max_depth = 0;
    int samples_per_pixel = 0;

    cameraSettings.lookupValue("fov", fov);
    cameraSettings.lookupValue("nb_thread", nb_thread);
    cameraSettings.lookupValue("max_depth", max_depth);
    cameraSettings.lookupValue("samples_per_pixel", samples_per_pixel);

    parseResolution(cameraSettings["resolution"], camera);
    parseVector(cameraSettings["look_from"], camera.lookfrom);
    parseVector(cameraSettings["look_at"], camera.lookat);
    parseVector(cameraSettings["vup"], camera.vup);
    parseColorMul(cameraSettings["background"], camera.background);

    camera.fov = fov;
    camera.nb_thread = nb_thread;
    camera.max_depth = max_depth;
    camera.samples_per_pixel = samples_per_pixel;
    adjustCameraSettings(camera);
}

void Rt::LoadScene::parseResolution(const libconfig::Setting &resolution, Rt::Camera &camera)
{
    std::vector<int> vectorResolution = parseVector2D(resolution);
    camera.image_width = vectorResolution.at(0);
    camera.image_height = vectorResolution.at(1);
}

void Rt::LoadScene::parseVector(const libconfig::Setting &setting, Math::Point3D &point)
{
    std::vector<int> vectorData = parseVector3D(setting);
    point = Math::Point3D(vectorData.at(0), vectorData.at(1), vectorData.at(2));
}

void Rt::LoadScene::parseColorMul(const libconfig::Setting &setting, Math::Color01 &color)
{
    std::vector<double> vectorData = parseColorMul(setting);
    color = Math::Color01(vectorData.at(0) * vectorData.at(3), vectorData.at(1) * vectorData.at(3), vectorData.at(2) * vectorData.at(3));
}

void Rt::LoadScene::adjustCameraSettings(Rt::Camera &camera) const
{
    if (this->_lowRes) {
        camera.max_depth = 5;
        camera.samples_per_pixel = 50;
    }
    if (this->_closeWindow) {
        camera.quit_after_render = true;
    }
}
