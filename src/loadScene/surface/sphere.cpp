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
        const libconfig::Setting &translation = currentSphere["translation"];
        const libconfig::Setting &rotation = currentSphere["rotation"];
        currentSphere.lookupValue("radius", radius);
        currentSphere.lookupValue("material", materialName);

        Math::Vector3D vectorTranslation = vectorTo3D(parseVector3D(translation));
        Math::Vector3D vectorRotation = vectorTo3D(parseVector3D(rotation));

        std::shared_ptr<Rt::IMaterial> material;

        chooseMaterialType(material, materialName);

        world.add(Rt::Builder::createObject<Rt::Sphere>(vectorTranslation, vectorRotation, material, radius));
    } catch(const std::exception &exception) {
        throw my::tracked_exception("Error in the parsing of the sphere: " + std::string(exception.what()));
    }
}

void Rt::LoadScene::parseAllSphere(const libconfig::Setting &primitivesSettings, Rt::ObjectList &world)
{
    const libconfig::Setting &listSpheres = primitivesSettings.lookup("spheres");
    for (int i = 0; i < listSpheres.getLength(); ++i) {
        analyseOneSphere(listSpheres[i], world);
    }
}
