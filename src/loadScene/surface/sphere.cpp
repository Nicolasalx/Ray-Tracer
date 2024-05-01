/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** sphere
*/

#include "LoadScene.hpp"
#include "Sphere.hpp"

void Rt::LoadScene::analyseOneSphere(const libconfig::Setting &currentSphere, Rt::ObjectList &world)
{
    std::string materialName = "";
    double radius = 0.0;
    const libconfig::Setting &sphere = currentSphere;
    const libconfig::Setting &center = sphere["center"];

    Math::Point3D pointOrigin = vectorToPoint3D(parseVector3D(center));
    sphere.lookupValue("material", materialName);
    sphere.lookupValue("radius", radius);
    std::shared_ptr<Rt::IMaterial> material;
    chooseMaterialType(material);
    world.add(std::make_shared<Rt::Sphere>(pointOrigin, radius, material));
}

void Rt::LoadScene::parseAllSphere(libconfig::Config &cfg, const libconfig::Setting &primitivesSettings, Rt::ObjectList &world)
{
    const libconfig::Setting &listSpheres = primitivesSettings.lookup("spheres");

    for (int i = 0; i < listSpheres.getLength(); ++i) {
        analyseOneSphere(listSpheres[i], world);
    }
}
