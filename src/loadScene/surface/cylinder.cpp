/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** cylinder
*/

#include "LoadScene.hpp"
#include "Cylinder.hpp"
#include "Builder.hpp"

void Rt::LoadScene::analyseOneCylinder(const libconfig::Setting &currentCylinder, Rt::ObjectList &world)
{
    std::string materialName = "";
    double radius = 0.0;
    double length = 0.0;
    const libconfig::Setting &translation = currentCylinder["translation"];
    const libconfig::Setting &rotation = currentCylinder["rotation"];
    currentCylinder.lookupValue("radius", radius);
    currentCylinder.lookupValue("length", length);
    currentCylinder.lookupValue("material", materialName);

    Math::Vector3D vectorTranslation = vectorTo3D(parseVector3D(translation));
    Math::Vector3D vectorRotation = vectorTo3D(parseVector3D(rotation));

    std::shared_ptr<Rt::IMaterial> material;

    chooseMaterialType(material, materialName);
    world.add(Rt::Builder::createObject<Rt::Cylinder>(vectorTranslation, vectorRotation, material, radius, length));
}

void Rt::LoadScene::parseAllCylinder(const libconfig::Setting &primitivesSettings, Rt::ObjectList &world)
{
    try {
        const libconfig::Setting &listCylinders = primitivesSettings.lookup("cylinders");

        for (int i = 0; i < listCylinders.getLength(); ++i) {
            analyseOneCylinder(listCylinders[i], world);
        }
    } catch(const std::exception &) {
        return;
    }
}
