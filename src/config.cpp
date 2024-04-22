/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** config
*/

#include <iostream>
#include <libconfig.h++>
#include "ObjectList.hpp"
#include "Camera.hpp"
#include "Config.hpp"

void ConfigLoader::loadCfg(const std::string& configFile, Rt::ObjectList& world, Rt::Camera& cam) {
    libconfig::Config cfg;
    try {
        cfg.readFile(configFile.c_str());
    } catch(const libconfig::FileIOException& fioex) {
        std::cerr << "Erreur lors de la lecture du fichier de configuration." << std::endl;
        return;
    } catch(const libconfig::ParseException& pex) {
        std::cerr << "Erreur de syntaxe dans le fichier de configuration à la ligne " << pex.getLine() << ": " << pex.getError() << std::endl;
        return;
    }
    const libconfig::Setting& cameraSettings = cfg.lookup("camera");
    const libconfig::Setting& primitivesSettings = cfg.lookup("primitives");
    const libconfig::Setting& res = cameraSettings["resolution"];
    const libconfig::Setting& pos = cameraSettings["position"];
    const libconfig::Setting& rot = cameraSettings["rotation"];
    int resolution_width = res["width"];
    int resolution_height = res["height"];
    int position_x = pos["x"];
    int position_y = pos["y"];
    int position_z = pos["z"];
    int rotation_x = rot["x"];
    int rotation_y = rot["y"];
    int rotation_z = rot["z"];
    float field_of_view;
    cameraSettings.lookupValue("fieldOfView", field_of_view);
    const libconfig::Setting& spheresSettings = primitivesSettings["spheres"];
    for (int i = 0; i < spheresSettings.getLength(); ++i) {
        const libconfig::Setting& sphere = spheresSettings[i];
        int x, y, z, r, color_r, color_g, color_b;
        sphere.lookupValue("x", x);
        sphere.lookupValue("y", y);
        sphere.lookupValue("z", z);
        sphere.lookupValue("r", r);
        const libconfig::Setting& color = sphere["color"];
        color.lookupValue("r", color_r);
        color.lookupValue("g", color_g);
        color.lookupValue("b", color_b);
    }
    const libconfig::Setting& planesSettings = primitivesSettings["planes"];
    for (int i = 0; i < planesSettings.getLength(); ++i) {
        const libconfig::Setting& plane = planesSettings[i];
        std::string axis;
        int position, color_r, color_g, color_b;
        plane.lookupValue("axis", axis);
        plane.lookupValue("position", position);
        const libconfig::Setting& color = plane["color"];
        color.lookupValue("r", color_r);
        color.lookupValue("g", color_g);
        color.lookupValue("b", color_b);
    }
}
