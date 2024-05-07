/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** parsePrimitives
*/

#include <iostream>
#include "ObjectList.hpp"
#include "Camera.hpp"
#include "LoadScene.hpp"
#include "my_tracked_exception.hpp"
#include <filesystem>
#include "Metal.hpp"
#include "Dielectric.hpp"
#include "Lambertian.hpp"
#include "DiffuseLight.hpp"

void Rt::LoadScene::chooseMaterialType(std::shared_ptr<Rt::IMaterial> &material, std::string &materialName)
{
    if (materialName.starts_with("metal")) {
        auto itMetal = _materialsList.find(materialName);
        if (itMetal != _materialsList.end()) {
            material = std::make_shared<Rt::Metal>(itMetal->second.color, itMetal->second.reflection);
        }
    } else if (materialName.starts_with("lambertian")) {
        auto itLambertian = _materialsList.find(materialName);
        if (itLambertian != _materialsList.end()) {
            material = std::make_shared<Rt::Lambertian>(itLambertian->second.color);
        }
    } else if (materialName.starts_with("dielectric")) {
        auto itDielectric = _materialsList.find(materialName);
        if (itDielectric != _materialsList.end()) {
            material = std::make_shared<Rt::Dielectric>(itDielectric->second.reflection);
        }
    } else if (materialName.starts_with("diffuseLight")) {
        auto itDiffuseLight = _materialsList.find(materialName);
        if (itDiffuseLight != _materialsList.end()) {
            material = std::make_shared<Rt::DiffuseLight>(itDiffuseLight->second.color);
        }
    } else {    
        throw my::tracked_exception("In the parsing with libConfig++, we have detect a mysterious material!");
    }
}

void Rt::LoadScene::parsePrimitives(libconfig::Config &cfg, Rt::ObjectList &world)
{
    const libconfig::Setting &primitivesSettings = cfg.lookup("primitives");

    parseAllSphere(primitivesSettings, world);
    parseAllTriangle(primitivesSettings, world);
    parseAllPlane(primitivesSettings, world);
    parseAllCone(primitivesSettings, world);
    parseAllCylinder(primitivesSettings, world);
}
