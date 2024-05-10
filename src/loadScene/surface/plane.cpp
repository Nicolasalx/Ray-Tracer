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
    try {
        std::string materialName = "";
        double height = 0.0;
        double width = 0.0;
        std::shared_ptr<Rt::IMaterial> material;
        const libconfig::Setting &position = currentPlane["position"];
        const libconfig::Setting &rotation = currentPlane["rotation"];

        checkFieldExist(currentPlane, "height", height, "plane");
        checkFieldExist(currentPlane, "width", width, "plane");
        checkFieldExist(currentPlane, "material", materialName, "plane");

        Math::Vector3D vectorPosition = vectorTo3D(parseVector3D(position));
        Math::Vector3D vectorRotation = vectorTo3D(parseVector3D(rotation));

        chooseMaterialType(material, materialName);
        world.add(Rt::Builder::createObject<Rt::Plane>(vectorPosition, vectorRotation, material, height, width));
    } catch(const libconfig::SettingNotFoundException &nfex) {
        throw my::tracked_exception("Error in the parsing of the plane:");
    } catch(const std::exception &exception) {
        throw my::tracked_exception("Error in the parsing of the plane: " + std::string(exception.what()));
    }
}

void Rt::LoadScene::parseAllPlane(const libconfig::Setting &primitivesSettings, Rt::ObjectList &world)
{
    try {
        const libconfig::Setting &listPlanes = primitivesSettings.lookup("planes");

        for (int i = 0; i < listPlanes.getLength(); ++i) {
            analyseOnePlane(listPlanes[i], world);
        }
    } catch(const my::tracked_exception &exception) {
        throw my::tracked_exception("In the parsing libConfig ++ the Plane has a problem!");
    } catch (const std::exception& e) {
        return;
    }
}
