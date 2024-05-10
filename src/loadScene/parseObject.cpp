/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** parseObject
*/

#include "LoadScene.hpp"

void Rt::LoadScene::parseOneObject(const libconfig::Setting &object, Rt::ObjectList &world)
{
    try {
        std::string filepath = "";
        double scale = 0.0;
        std::shared_ptr<Rt::IMaterial> material;
        std::string materialName = "";

        object.lookupValue("filepath", filepath);
        object.lookupValue("scale", scale);

        object.lookupValue("material", materialName);

        std::size_t found = materialName.find_last_of("_");
        if (found != std::string::npos) {
            std::string result = materialName.substr(found + 1);
            if (result == "RANDOM") {
                Rt::Raytracer::createObjModelRandom(world, filepath, scale);
                return;
            }
        }
        chooseMaterialType(material, materialName);
        Rt::Raytracer::createObjModel(world, filepath, scale, material);
    } catch(const std::exception &exception) {
        throw my::tracked_exception("Error in the parsing of the cone: " + std::string(exception.what()));
    }
}

void Rt::LoadScene::parseObject(libconfig::Config &cfg, Rt::ObjectList &world)
{
    const libconfig::Setting &objectsSettings = cfg.lookup("objects");
    const libconfig::Setting &listObjectsSettings = objectsSettings.lookup("listObjects");

    for (int i = 0; i < listObjectsSettings.getLength(); ++i) {
        parseOneObject(listObjectsSettings[i], world);
    }
}
