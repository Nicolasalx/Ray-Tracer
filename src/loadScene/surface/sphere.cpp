/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** sphere
*/

#include "LoadScene.hpp"
#include "Sphere.hpp"
#include "Builder.hpp"

void Rt::LoadScene::analyseOneSphere(const libconfig::Setting &currentSphere, Rt::ObjectList &world)
{
    std::string materialName = "";
    double radius = 0.0;
    const libconfig::Setting &sphere = currentSphere;
    const libconfig::Setting &center = sphere["position"];
    // ! To Add Rotation

    Math::Point3D pointOrigin = vectorToPoint3D(parseVector3D(center));
    sphere.lookupValue("material", materialName);
    sphere.lookupValue("radius", radius);
    std::shared_ptr<Rt::IMaterial> material;

    std::cout << "------------------------------------------------------\n";
    std::cout << "New Sphere:\n";
    std::cout << "Point Pos: " << pointOrigin.x() << " / " << pointOrigin.y() << " / " << pointOrigin.z() << "\n";
    std::cout << "Radius: " << radius << "\n";
    chooseMaterialType(material, materialName);
    std::cout << "------------------------------------------------------\n";

    world.add(Rt::Builder::createObject<Rt::Sphere>(pointOrigin, radius, material));
}

void Rt::LoadScene::parseAllSphere(const libconfig::Setting &primitivesSettings, Rt::ObjectList &world)
{
    try {
        libconfig::Setting &listSpheres = primitivesSettings.lookup("spheres");
        for (int i = 0; i < listSpheres.getLength(); ++i) {
            analyseOneSphere(listSpheres[i], world);
        }
    } catch(const std::exception &) {
        return;
    }
}
