/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** cylinder
*/

#include "LoadScene.hpp"
#include "Cylinder.hpp"
#include "Builder.hpp"
#include "my_log.hpp"
#include "my_tracked_exception.hpp"

void Rt::LoadScene::analyseOneCylinder(const libconfig::Setting &currentCylinder, Rt::ObjectList &world)
{
    try {
        std::string materialName = "";
        double radius = 0.0;
        double length = 0.0;
        const libconfig::Setting &position = currentCylinder["position"];
        const libconfig::Setting &rotation = currentCylinder["rotation"];
        currentCylinder.lookupValue("radius", radius);
        currentCylinder.lookupValue("length", length);
        currentCylinder.lookupValue("material", materialName);

        Math::Vector3D vectorPosition = vectorTo3D(parseVector3D(position));
        Math::Vector3D vectorRotation = vectorTo3D(parseVector3D(rotation));

        std::shared_ptr<Rt::IMaterial> material;

        chooseMaterialType(material, materialName);
        world.add(Rt::Builder::createObject<Rt::Cylinder>(vectorPosition, vectorRotation, material, radius, length));
    } catch(const std::exception &exception) {
        throw my::tracked_exception("Error in the parsing of the cylinder: " + std::string(exception.what()));
    }
}

void Rt::LoadScene::parseAllCylinder(const libconfig::Setting &primitivesSettings, Rt::ObjectList &world)
{
    const libconfig::Setting &listCylinders = primitivesSettings.lookup("cylinders");

    for (int i = 0; i < listCylinders.getLength(); ++i) {
        analyseOneCylinder(listCylinders[i], world);
    }
}
