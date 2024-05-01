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

void Rt::LoadScene::chooseMaterialType(std::shared_ptr<Rt::IMaterial> &material)
{
    auto itMetal = _materialsList.find("metal");
    auto itDielectric = _materialsList.find("dielectric");
    auto itLambertian = _materialsList.find("lambertian");
    auto itDiffuseLight = _materialsList.find("diffuseLight");

    if (itMetal != _materialsList.end()) {
        material = std::make_shared<Rt::Metal>(itMetal->second.color, itMetal->second.reflection);
    } else if (itLambertian != _materialsList.end()) {
        material = std::make_shared<Rt::Lambertian>(itLambertian->second.color);
    } else if (itDielectric != _materialsList.end()) {
        material = std::make_shared<Rt::Dielectric>(itDielectric->second.reflection);
    } else if (itDiffuseLight != _materialsList.end()) {
        material = std::make_shared<Rt::DiffuseLight>(itDiffuseLight->second.color);
    } else {
        throw my::tracked_exception("In the parsing with libConfig++, we have detect a mysterious material!");
    }
}

void Rt::LoadScene::parsePrimitives(libconfig::Config &cfg, Rt::ObjectList &world)
{
    const libconfig::Setting &primitivesSettings = cfg.lookup("primitives");

    parseAllSphere(cfg, primitivesSettings, world);
    parseAllTriangle(cfg, primitivesSettings, world);
    parseAllPlane(cfg, primitivesSettings, world);
}
