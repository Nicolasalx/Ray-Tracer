/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** plane
*/

#include "LoadScene.hpp"
#include "Plane.hpp"

void Rt::LoadScene::analyseOnePlane(const libconfig::Setting &currentPlane, Rt::ObjectList &world)
{
    std::string materialName = "";
    const libconfig::Setting &plane = currentPlane;
    const libconfig::Setting &pos = plane["pos"];
    const libconfig::Setting &u = plane["u"];
    const libconfig::Setting &v = plane["v"];

    Math::Point3D pointPos = vectorToPoint3D(parseVector3D(pos));
    Math::Vector3D vectorU = vectorTo3D(parseVector3D(u));
    Math::Vector3D vectorV = vectorTo3D(parseVector3D(v));

    plane.lookupValue("material", materialName);
    std::shared_ptr<Rt::IMaterial> material;
    chooseMaterialType(material);
    world.add(std::make_shared<Rt::Plane>(pointPos, vectorU, vectorV, material));
}

void Rt::LoadScene::parseAllPlane(libconfig::Config &cfg, const libconfig::Setting &primitivesSettings, Rt::ObjectList &world)
{
    const libconfig::Setting &listPlanes = primitivesSettings.lookup("planes");

    for (int i = 0; i < listPlanes.getLength(); ++i) {
        analyseOnePlane(listPlanes[i], world);
    }
}
