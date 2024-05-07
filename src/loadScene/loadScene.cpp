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

    cfg.readFile(filepath.c_str());
    try {
        parseMaterials(cfg);
    } catch(const std::exception &e) {}
    try {
        parsePrimitives(cfg, world);
    } catch(const std::exception &e) {}
    try {
        parseCamera(cfg, camera);
    } catch(const std::exception &e) {}
}

void Rt::LoadScene::loadAllScenes(Rt::ObjectList &world, Rt::Camera &camera)
{
    for (const auto &filepath: _listConfigFile) {
        loadScene(filepath, world, camera);
    }
}
