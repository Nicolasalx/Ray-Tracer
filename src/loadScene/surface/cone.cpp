/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** cone
*/

#include "LoadScene.hpp"
#include "Cone.hpp"
#include "Builder.hpp"

void Rt::LoadScene::analyseOneCone(const libconfig::Setting &currentCone, Rt::ObjectList &world)
{
    std::string materialName = "";
    double radius = 0.0;
    double length = 0.0;
    const libconfig::Setting &translation = currentCone["translation"];
    const libconfig::Setting &rotation = currentCone["rotation"];
    currentCone.lookupValue("radius", radius);
    currentCone.lookupValue("length", length);
    currentCone.lookupValue("material", materialName);

    Math::Vector3D vectorTranslation = vectorTo3D(parseVector3D(translation));
    Math::Vector3D vectorRotation = vectorTo3D(parseVector3D(rotation));

    std::shared_ptr<Rt::IMaterial> material;

    chooseMaterialType(material, materialName);
    world.add(Rt::Builder::createObject<Rt::Cone>(vectorTranslation, vectorRotation, material, radius, length));
}

void Rt::LoadScene::parseAllCone(const libconfig::Setting &primitivesSettings, Rt::ObjectList &world)
{
    try {
        const libconfig::Setting &listCones = primitivesSettings.lookup("cones");

        for (int i = 0; i < listCones.getLength(); ++i) {
            analyseOneCone(listCones[i], world);
        }
    } catch(const std::exception &) {
        return;
    }
}
