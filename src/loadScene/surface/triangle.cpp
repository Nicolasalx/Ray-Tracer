/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** triangle
*/

#include "LoadScene.hpp"
#include "Triangle.hpp"

void Rt::LoadScene::analyseOneTriangle(const libconfig::Setting &currentTriangle, Rt::ObjectList &world)
{
    std::string materialName = "";
    const libconfig::Setting &triangle = currentTriangle;
    const libconfig::Setting &origin = triangle["origin"];
    const libconfig::Setting &pointA = triangle["pointA"];
    const libconfig::Setting &pointB = triangle["pointB"];

    Math::Point3D pointOrigin = vectorToPoint3D(parseVector3D(origin));
    Math::Point3D PpointA = vectorToPoint3D(parseVector3D(pointA));
    Math::Point3D PpointB = vectorToPoint3D(parseVector3D(pointB));
    triangle.lookupValue("material", materialName);
    std::shared_ptr<Rt::IMaterial> material;
    
    std::cout << "------------------------------------------------------\n";
    std::cout << "New Triangle:\n";
    std::cout << "Point Pos: " << pointOrigin.x() << " / " << pointOrigin.y() << " / " << pointOrigin.z() << "\n";
    std::cout << "Vector U: " << PpointA.x() << " / " << PpointA.y() << " / " << PpointA.z() << "\n";
    std::cout << "Vector V: " << PpointB.x() << " / " << PpointB.y() << " / " << PpointB.z() << "\n";

    chooseMaterialType(material, materialName);
    std::cout << "------------------------------------------------------\n";
    world.add(std::make_shared<Rt::Triangle>(pointOrigin, PpointA, PpointB, material));
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
