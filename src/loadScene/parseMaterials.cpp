/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** parseMaterials
*/

#include <iostream>
#include "ObjectList.hpp"
#include "Camera.hpp"
#include "LoadScene.hpp"
#include "my_tracked_exception.hpp"
#include <filesystem>
#include "Metal.hpp"

void Rt::LoadScene::getMetal(const libconfig::Setting &material, libconfig::Config &cfg)
{
    const libconfig::Setting &color = material["color"];
    double reflection = 0.0;
    material_t mat;
    std::vector<int> vectorColor = parseColor(color);

    material.lookupValue("reflection", reflection);
    mat.name = METAL;
    mat.color = Math::Color01(vectorColor.at(0), vectorColor.at(1), vectorColor.at(2));
    mat.reflection = reflection;
    _materialsList["metal"] = mat;
}

void Rt::LoadScene::getLambertian(const libconfig::Setting &material, libconfig::Config &cfg)
{
    const libconfig::Setting &color = material["color"];
    material_t mat;
    std::vector<int> vectorColor = parseColor(color);

    mat.name = LAMBERTIAN;
    mat.color = Math::Color01(vectorColor.at(0), vectorColor.at(1), vectorColor.at(2));
    _materialsList["lambertian"] = mat;
}

void Rt::LoadScene::getDielectric(const libconfig::Setting &material, libconfig::Config &cfg)
{
    double reflection = 0.0;
    material_t mat;

    material.lookupValue("reflection", reflection);
    mat.name = DIELECTRIC;
    mat.reflection = reflection;
    _materialsList["dielectric"] = mat;
}

void Rt::LoadScene::getDiffuseLight(const libconfig::Setting &material, libconfig::Config &cfg)
{
    const libconfig::Setting &color = material["color"];
    material_t mat;
    std::vector<int> vectorColor = parseColor(color);

    mat.name = DIFFUSE_LIGHT;
    mat.color = Math::Color01(vectorColor.at(0), vectorColor.at(1), vectorColor.at(2));
    _materialsList["diffuseLight"] = mat;
}

void Rt::LoadScene::parseMaterials(libconfig::Config &cfg)
{
    const libconfig::Setting &materialsSettings = cfg.lookup("materials");
    const libconfig::Setting &listMaterialsSettings = materialsSettings.lookup("listMaterials");

    for (int i = 0; i < listMaterialsSettings.getLength(); ++i) {
        const libconfig::Setting &material = listMaterialsSettings[i];

        std::string materialName = "";
        material.lookupValue("materialName", materialName);

        if (materialName == "metal") {
            getMetal(material, cfg);
        } else if (materialName == "lambertian") {
            getLambertian(material, cfg);
        } else if (materialName == "dielectric") {
            getDielectric(material, cfg);
        } else if (materialName == "diffuseLight") {
            getDiffuseLight(material, cfg);
        }
    }
}
