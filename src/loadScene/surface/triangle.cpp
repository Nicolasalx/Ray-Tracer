/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** triangle
*/

#include "LoadScene.hpp"
#include "Triangle.hpp"
#include "Builder.hpp"

void Rt::LoadScene::analyseOneTriangle(const libconfig::Setting &currentTriangle, Rt::ObjectList &world)
{
    std::string materialName = "";
    const libconfig::Setting &translation = currentTriangle["translation"];
    const libconfig::Setting &rotation = currentTriangle["rotation"];
    const libconfig::Setting &origin = currentTriangle["origin"];
    const libconfig::Setting &pointA = currentTriangle["pointA"];
    const libconfig::Setting &pointB = currentTriangle["pointB"];
    currentTriangle.lookupValue("material", materialName);

    Math::Vector3D vectorTranslation = vectorTo3D(parseVector3D(translation));
    Math::Vector3D vectorRotation = vectorTo3D(parseVector3D(rotation));
    Math::Point3D pointOrigin = vectorToPoint3D(parseVector3D(origin));
    Math::Point3D PpointA = vectorToPoint3D(parseVector3D(pointA));
    Math::Point3D PpointB = vectorToPoint3D(parseVector3D(pointB));
    std::shared_ptr<Rt::IMaterial> material;
    
    chooseMaterialType(material, materialName);
    world.add(Rt::Builder::createObject<Rt::Triangle>(vectorTranslation, vectorRotation, material, pointOrigin, PpointA, PpointB));
}

void Rt::LoadScene::parseAllTriangle(const libconfig::Setting &primitivesSettings, Rt::ObjectList &world)
{
    try {
        const libconfig::Setting &listTriangles = primitivesSettings.lookup("triangles");

        for (int i = 0; i < listTriangles.getLength(); ++i) {
            analyseOneTriangle(listTriangles[i], world);
        }
    } catch(const std::exception &) {
        return;
    }
}
