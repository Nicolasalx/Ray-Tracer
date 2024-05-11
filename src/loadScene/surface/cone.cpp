/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** cone
*/

#include "LoadScene.hpp"
#include "Cone.hpp"
#include "Builder.hpp"
#include "my_log.hpp"
#include "my_tracked_exception.hpp"
#include "TextureFactory.hpp"
#include "Lambertian.hpp"
#include "ChessTexture.hpp"
#include "ImageTexture.hpp"
#include "MaterialFactory.hpp"

void Rt::LoadScene::analyseOneCone(const libconfig::Setting &currentCone, Rt::ObjectList &world)
{
    try {
        std::string materialName = "";
        double radius = 0.0;
        double length = 0.0;
        const libconfig::Setting &position = currentCone["position"];
        const libconfig::Setting &rotation = currentCone["rotation"];

        checkFieldExist(currentCone, "radius", radius, "cone");
        checkFieldExist(currentCone, "length", length, "cone");
        checkFieldExist(currentCone, "material", materialName, "cone");

        Math::Vector3D vectorPosition = vectorTo3D(parseVector3D(position));
        Math::Vector3D vectorRotation = vectorTo3D(parseVector3D(rotation));

        std::shared_ptr<Rt::IMaterial> material;
        Rt::material_t allMaterial;
        chooseMaterialType(material, materialName, allMaterial);

        if (allMaterial.nameTexture == "chess") {
            world.add(Rt::Builder::createObject<Rt::Cone>(vectorPosition, vectorRotation, Rt::MaterialFactory::createMaterial<Rt::Lambertian>(Rt::TextureFactory::createTexture<Rt::ChessTexture>(allMaterial.scale, allMaterial.color1, allMaterial.color2)), radius, length));
        } else if (allMaterial.nameTexture == "image") {
            world.add(Rt::Builder::createObject<Rt::Cone>(vectorPosition, vectorRotation, Rt::MaterialFactory::createMaterial<Rt::Lambertian>(Rt::TextureFactory::createTexture<Rt::ImageTexture>(allMaterial.filepath)), radius, length));
        } else {
            world.add(Rt::Builder::createObject<Rt::Cone>(vectorPosition, vectorRotation, material, radius, length));
        }
    } catch(const std::exception &exception) {
        throw my::tracked_exception("Error in the parsing of the cone: " + std::string(exception.what()));
    }
}

void Rt::LoadScene::parseAllCone(const libconfig::Setting &primitivesSettings, Rt::ObjectList &world)
{
    try {
        const libconfig::Setting &listCones = primitivesSettings.lookup("cones");
    
        for (int i = 0; i < listCones.getLength(); ++i) {
            analyseOneCone(listCones[i], world);
        }
    } catch(const my::tracked_exception &exception) {
        throw my::tracked_exception("In the parsing libConfig ++ the Cone has a problem!");
    } catch (const std::exception& e) {
        return;
    }
}
