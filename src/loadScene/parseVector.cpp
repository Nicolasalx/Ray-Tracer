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

    int x = vector["x"];
    int y = vector["y"];
    int z = vector["z"];

    listElement.push_back(x);
    listElement.push_back(y);
    listElement.push_back(z);
    return listElement;
}

Math::Point3D Rt::LoadScene::vectorToPoint3D(std::vector<int> list)
{
    if (list.size() != 3) {
        throw("Invalid size of vector, need to be a size of 3!");
    }
    return Math::Point3D(list.at(0), list.at(1), list.at(2));
}

Math::Vector3D Rt::LoadScene::vectorTo3D(std::vector<int> list)
{
    if (list.size() != 3) {
        throw("Invalid size of vector, need to be a size of 3!");
    }
    return Math::Vector3D(list.at(0), list.at(1), list.at(2));
}

double Rt::LoadScene::checkValueIsColor(int value)
{
    if (value < 0 || value > 255) {
        throw("In the parsing with lib config a color value is not correct (need to be between 0 and 255)!");
    }
    return (static_cast<double>(value) / 255.0);
}

std::vector<double> Rt::LoadScene::parseColor(const libconfig::Setting &vector)
{
    std::vector<double> listElement;

    int r = vector["r"];
    int g = vector["g"];
    int b = vector["b"];

    double rdouble = checkValueIsColor(r);
    double gdouble = checkValueIsColor(g);
    double bdouble = checkValueIsColor(b);

    listElement.push_back(rdouble);
    listElement.push_back(gdouble);
    listElement.push_back(bdouble);
    return listElement;
}

std::vector<double> Rt::LoadScene::parseColorMul(const libconfig::Setting &vector)
{
    std::vector<double> listElement;

    int r = vector["r"];
    int g = vector["g"];
    int b = vector["b"];
    double multiplier = vector["multiplier"];

    double rdouble = checkValueIsColor(r);
    double gdouble = checkValueIsColor(g);
    double bdouble = checkValueIsColor(b);

    listElement.push_back(rdouble);
    listElement.push_back(gdouble);
    listElement.push_back(bdouble);
    listElement.push_back(multiplier);
    return listElement;
}

std::vector<int> Rt::LoadScene::parseVector2D(const libconfig::Setting &vector)
{
    std::vector<int> listElement;

    int x = vector["x"];
    int y = vector["y"];

    listElement.push_back(x);
    listElement.push_back(y);
    return listElement;
}
