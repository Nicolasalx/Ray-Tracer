/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** sphere
*/

#include "LoadScene.hpp"
#include "Sphere.hpp"
#include "Builder.hpp"
#include "my_log.hpp"
#include "my_tracked_exception.hpp"

void Rt::LoadScene::analyseOneSphere(const libconfig::Setting &currentSphere, Rt::ObjectList &world)
{
    try {
        std::string materialName = "";
        double radius = 0.0;
        const libconfig::Setting &position = currentSphere["position"];
        const libconfig::Setting &rotation = currentSphere["rotation"];
        currentSphere.lookupValue("radius", radius);
        currentSphere.lookupValue("material", materialName);

        checkFieldExist(currentSphere, "radius", radius, "sphere");
        checkFieldExist(currentSphere, "material", materialName, "sphere");

        Math::Vector3D vectorPosition = vectorTo3D(parseVector3D(position));
        Math::Vector3D vectorRotation = vectorTo3D(parseVector3D(rotation));

        std::shared_ptr<Rt::IMaterial> material;

        chooseMaterialType(material, materialName);

        world.add(Rt::Builder::createObject<Rt::Sphere>(vectorPosition, vectorRotation, material, radius));
    } catch(const std::exception &exception) {
        throw my::tracked_exception("Error in the parsing of the sphere: " + std::string(exception.what()));
    }
}

void Rt::LoadScene::parseAllSphere(const libconfig::Setting &primitivesSettings, Rt::ObjectList &world)
{
    try {
        const libconfig::Setting &listSpheres = primitivesSettings.lookup("spheres");
    
        for (int i = 0; i < listSpheres.getLength(); ++i) {
            analyseOneSphere(listSpheres[i], world);
        }
    } catch(const my::tracked_exception &exception) {
        throw my::tracked_exception("Triangle");
    } catch (const std::exception& e) {
        return;
    }
}
