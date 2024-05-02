/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** config
*/

#include <iostream>
#include "ObjectList.hpp"
#include "LoadScene.hpp"
#include "my_tracked_exception.hpp"
#include <filesystem>

void Rt::LoadScene::parseArgs(int argc, const char **argv)
{
    if (argc < 2) {
        throw my::tracked_exception("Bad number of arguments (minimum 1 scene required).");
    }
    for (int i = 1; i < argc; ++i) {
        if (!std::filesystem::is_directory(argv[i])) {
            _listConfigFile.push_back(argv[i]);
        } else {
            throw my::tracked_exception("The provided file is a directory.");
        }
    }
}

void Rt::LoadScene::loadScene(const std::string &filepath, Rt::ObjectList &world, Rt::Camera &camera)
{
    libconfig::Config cfg;

    try {
        cfg.readFile(filepath.c_str());
        parseMaterials(cfg);
        parsePrimitives(cfg, world);
        parseCamera(cfg, camera);
    } catch(const libconfig::FileIOException &fioex) {
        throw my::tracked_exception("Can't open configuration file to parse the scene.");
    } catch(const libconfig::ParseException &pex) {
        std::cerr << "Syntax error in the configuration file at line " << pex.getLine() << ": " << pex.getError() << std::endl; // ! Delete after with the return (set error in the throw)
        throw my::tracked_exception("Syntax error in the configuration file.");
        return;
    }
}

void Rt::LoadScene::loadAllScenes(Rt::ObjectList &world, Rt::Camera &camera)
{
    // Les couleurs doivent etre rendu sur une échelle de 0 à 1 (/255.0 et pas /255 => division à virgule et pas entière)
    for (const auto &filepath: _listConfigFile) {
        loadScene(filepath, world, camera);
    }
}
