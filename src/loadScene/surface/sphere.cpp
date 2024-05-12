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
#include "MaterialFactory.hpp"
#include "TextureFactory.hpp"
#include "Lambertian.hpp"
#include "ChessTexture.hpp"
#include "ImageTexture.hpp"

void Rt::LoadScene::analyseOneSphere(const libconfig::Setting &currentSphere, Rt::ObjectList &world)
{
    try {
        std::string materialName;
        double radius = 0.0;
        const libconfig::Setting &position = currentSphere["position"];
        const libconfig::Setting &rotation = currentSphere["rotation"];
        currentSphere.lookupValue("radius", radius);
        currentSphere.lookupValue("material", materialName);

        checkFieldExist(currentSphere, "radius", radius, "sphere");
        checkFieldExist(currentSphere, "material", materialName, "sphere");
        Math::Vector3D vectorPosition = vectorTo3D(parseVector3D(position));
        Math::Vector3D vectorRotation = vectorTo3D(parseVector3D(rotation));

        Rt::material_t allMaterial;
        std::shared_ptr<Rt::IMaterial> material;
        chooseMaterialType(material, materialName, allMaterial);

        if (allMaterial.nameTexture == "chess") {
            world.add(Rt::Builder::createObject<Rt::Sphere>(vectorPosition, vectorRotation, Rt::MaterialFactory::createMaterial<Rt::Lambertian>(Rt::TextureFactory::createTexture<Rt::ChessTexture>(allMaterial.scale, allMaterial.color1, allMaterial.color2)), radius));
        } else if (allMaterial.nameTexture == "image") {
            world.add(Rt::Builder::createObject<Rt::Sphere>(vectorPosition, vectorRotation, Rt::MaterialFactory::createMaterial<Rt::Lambertian>(Rt::TextureFactory::createTexture<Rt::ImageTexture>(allMaterial.filepath)), radius));
        } else {
            world.add(Rt::Builder::createObject<Rt::Sphere>(vectorPosition, vectorRotation, material, radius));
        }
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
        throw my::tracked_exception("In the parsing libConfig ++ the Sphere has a problem!");
    } catch (const std::exception& e) {
        return;
    }
// std::shared_ptr<Rt::IObject> test =
// Rt::Builder::createObject<Rt::Sphere>(Math::Vector3D(0, 0, 0), Math::Vector3D(0, 0, 0), Rt::MaterialFactory::createMaterial<Rt::Lambertian>(Rt::TextureFactory::createTexture<Rt::ChessTexture>(1, Math::Color01(1, 0, 0), Math::Color01(0, 0, 1))), 50);
}
