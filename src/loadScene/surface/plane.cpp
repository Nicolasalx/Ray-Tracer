/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** plane
*/

#include "LoadScene.hpp"
#include "Plane.hpp"
#include "Builder.hpp"
#include "my_log.hpp"
#include "my_tracked_exception.hpp"

void Rt::LoadScene::analyseOnePlane(const libconfig::Setting &currentPlane, Rt::ObjectList &world)
{
    try
    {
        std::string materialName = "";
        std::shared_ptr<Rt::IMaterial> material;
        const libconfig::Setting &translation = currentPlane["translation"];
        const libconfig::Setting &rotation = currentPlane["rotation"];    
        const libconfig::Setting &pos = currentPlane["pos"];
        const libconfig::Setting &u = currentPlane["u"];
        const libconfig::Setting &v = currentPlane["v"];
        currentPlane.lookupValue("material", materialName);

        Math::Vector3D vectorTranslation = vectorTo3D(parseVector3D(translation));
        Math::Vector3D vectorRotation = vectorTo3D(parseVector3D(rotation));
        Math::Point3D pointPos = vectorToPoint3D(parseVector3D(pos));
        Math::Vector3D vectorU = vectorTo3D(parseVector3D(u));
        Math::Vector3D vectorV = vectorTo3D(parseVector3D(v));

        chooseMaterialType(material, materialName);
        world.add(Rt::Builder::createObject<Rt::Plane>(vectorTranslation, vectorRotation, material, pointPos, vectorU, vectorV));
    } catch(const std::exception &exception) {
        throw my::tracked_exception("Error in the parsing of the plane: " + std::string(exception.what()));
    }
}

void Rt::LoadScene::parseAllPlane(const libconfig::Setting &primitivesSettings, Rt::ObjectList &world)
{
    const libconfig::Setting &listPlanes = primitivesSettings.lookup("planes");

    for (int i = 0; i < listPlanes.getLength(); ++i) {
        analyseOnePlane(listPlanes[i], world);
    }
}
