/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** parseVector3D
*/

#include <iostream>
#include "ObjectList.hpp"
#include "Camera.hpp"
#include "LoadScene.hpp"
#include "my_tracked_exception.hpp"
#include <filesystem>

std::vector<int> Rt::LoadScene::parseVector3D(const libconfig::Setting &vector)
{
    std::vector<int> listElement;

    listElement.push_back(vector["x"]);
    listElement.push_back(vector["y"]);
    listElement.push_back(vector["z"]);
    return listElement;
}

Math::Point3D Rt::LoadScene::vectorToPoint3D(std::vector<int> list)
{
    if (list.size() != 3) {
        throw("Invalid size of vector, need to be a size of 3!");
    }
    return Math::Point3D(list.at(0), list.at(1), list.at(2));
}

Math::Point3D Rt::LoadScene::vectorTo3D(std::vector<int> list)
{
    if (list.size() != 3) {
        throw("Invalid size of vector, need to be a size of 3!");
    }
    return Math::Point3D(list.at(0), list.at(1), list.at(2));
}

std::vector<int> Rt::LoadScene::parseColor(const libconfig::Setting &vector)
{
    std::vector<int> listElement;

    listElement.push_back(vector["r"]);
    listElement.push_back(vector["g"]);
    listElement.push_back(vector["b"]);
    return listElement;
}

std::vector<int> Rt::LoadScene::parseVector2D(const libconfig::Setting &vector)
{
    std::vector<int> listElement;

    listElement.push_back(vector["x"]);
    listElement.push_back(vector["y"]);
    return listElement;
}
