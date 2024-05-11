/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** parseMaterials
*/

#include <iostream>
#include "ObjectList.hpp"
#include "LoadScene.hpp"
#include "my_tracked_exception.hpp"
#include "Metal.hpp"

void Rt::LoadScene::getMetal(const libconfig::Setting &material, std::string &materialName)
{
    const libconfig::Setting &color = material["color"];
    double reflection = 0.0;
    material_t mat;
    std::vector<double> vectorColor = parseColor(color);

    material.lookupValue("reflection", reflection);
    mat.name = METAL;
    mat.color = Math::Color01(vectorColor.at(0), vectorColor.at(1), vectorColor.at(2));
    mat.reflection = reflection;
    _materialsList[materialName] = mat;
}

void Rt::LoadScene::getLambertian(const libconfig::Setting &material, std::string &materialName)
{
    const libconfig::Setting &color = material["color"];
    material_t mat;
    std::vector<double> vectorColor = parseColor(color);

    mat.name = LAMBERTIAN;
    mat.color = Math::Color01(vectorColor.at(0), vectorColor.at(1), vectorColor.at(2));

    try {
        double scale = 0.0;
        std::string textureName = "";
        std::string filepathImg = "";
        const libconfig::Setting &texture = material["texture"];
        texture.lookupValue("name", textureName);

        mat.nameTexture = textureName;

        if (textureName == "chess") {
            const libconfig::Setting &color1 = texture["color1"];
            const libconfig::Setting &color2 = texture["color2"];
            texture.lookupValue("scale", scale);

            std::vector<double> vectorColor1 = parseColor(color1);
            std::vector<double> vectorColor2 = parseColor(color2);

            mat.scale = scale;
            mat.color1 = Math::Color01(vectorColor1.at(0), vectorColor1.at(1), vectorColor1.at(2));
            mat.color2 = Math::Color01(vectorColor2.at(0), vectorColor2.at(1), vectorColor2.at(2));
        } else if (textureName == "image") {
            texture.lookupValue("path", filepathImg);
            mat.filepath = filepathImg;
        } else {
            throw my::tracked_exception("Error in the parsing of a texture named: " + textureName);
        }


    } catch(const std::exception &e) {}
    _materialsList[materialName] = mat;
}

void Rt::LoadScene::getDielectric(const libconfig::Setting &material, std::string &materialName)
{
    double reflection = 0.0;
    material_t mat;

    material.lookupValue("reflection", reflection);
    mat.name = DIELECTRIC;
    mat.reflection = reflection;
    _materialsList[materialName] = mat;
}

void Rt::LoadScene::getDiffuseLight(const libconfig::Setting &material, std::string &materialName)
{
    const libconfig::Setting &color = material["color"];
    material_t mat;
    std::vector<double> vectorColor = parseColorMul(color);

    mat.name = DIFFUSE_LIGHT;
    mat.color = Math::Color01(vectorColor.at(0) * vectorColor.at(3), vectorColor.at(1) * vectorColor.at(3), vectorColor.at(2) * vectorColor.at(3));
    _materialsList[materialName] = mat;
}

void Rt::LoadScene::parseMaterials(libconfig::Config &cfg)
{
    const libconfig::Setting &materialsSettings = cfg.lookup("materials");
    const libconfig::Setting &listMaterialsSettings = materialsSettings.lookup("listMaterials");

    for (int i = 0; i < listMaterialsSettings.getLength(); ++i) {
        const libconfig::Setting &material = listMaterialsSettings[i];
        std::string materialName = "";
        material.lookupValue("materialName", materialName);
        if (materialName.starts_with("metal")) {
            getMetal(material, materialName);
        } else if (materialName.starts_with("lambertian")) {
            getLambertian(material, materialName);
        } else if (materialName.starts_with("dielectric")) {
            getDielectric(material, materialName);
        } else if (materialName.starts_with("diffuseLight")) {
            getDiffuseLight(material, materialName);
        }
    }
}
