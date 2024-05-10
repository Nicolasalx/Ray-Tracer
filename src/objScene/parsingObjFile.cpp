/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** parsingObjFile
*/

#include "my_log.hpp"
#include "Color01.hpp"
#include "ColorRGB.hpp"
#include "ObjectList.hpp"
#include "IObject.hpp"
#include "Sphere.hpp"
#include <vector>
#include <iomanip>
#include "Ray.hpp"
#include "Camera.hpp"
#include "Raytracer.hpp"
#include "Lambertian.hpp"
#include "Triangle.hpp"
#include "FileObj.hpp"
#include "Vector3D.hpp"
#include "MaterialFactory.hpp"

void Rt::Raytracer::createObjModel(Rt::ObjectList &world, const std::string &path,
    double scale, std::shared_ptr<Rt::IMaterial> material)
{
    FileObj obj(path);
    FaceList faceList = obj.getFaceList();
    for (auto face : faceList) {
        for (int i = 0; i < static_cast<int>(face.size()) - 2; i++) {
            world.add(std::make_shared<Rt::Triangle>(
                Math::Point3D(
                    face[0][0] * scale,
                    face[0][1] * scale,
                    face[0][2] * scale),
                Math::Point3D(
                    face[i + 1][0] * scale,
                    face[i + 1][1] * scale,
                    face[i + 1][2] * scale),
                Math::Point3D(
                    face[i + 2][0] * scale,
                    face[i + 2][1] * scale,
                    face[i + 2][2] * scale), material));
        }
    }
}

void Rt::Raytracer::createObjModelRandom(Rt::ObjectList &world,
    const std::string &path, double scale)
{
    FileObj obj(path);
    FaceList faceList = obj.getFaceList();
    for (auto face : faceList) {
        for (int i = 0; i < static_cast<int>(face.size()) - 2; i++) {
            world.add(std::make_shared<Rt::Triangle>(
                Math::Point3D(
                    face[0][0] * scale,
                    face[0][1] * scale,
                    face[0][2] * scale),
                Math::Point3D(
                    face[i + 1][0] * scale,
                    face[i + 1][1] * scale,
                    face[i + 1][2] * scale),
                Math::Point3D(
                    face[i + 2][0] * scale,
                    face[i + 2][1] * scale,
                    face[i + 2][2] * scale), Rt::MaterialFactory::createMaterial<Rt::Lambertian>(
                        Math::Color01(Rt::Random::getBw01(), Rt::Random::getBw01(), Rt::Random::getBw01()))));
        }
    }
}

FileObj::FileObj(std::string file_path)
{
    std::string lines;
    std::ifstream file(file_path);
    if (file.is_open()) {
        while (getline(file, lines)) {
            std::string line;
            std::istringstream stream(lines);
            stream >> line;
            if (line == "v") {
                VType(stream);
            }
            if (line == "vn") {
                VNType(stream);
            }
            if (line == "vt") {
                VTType(stream);
            }
            if (line == "f") {
                VFType(stream);
            }
        }
        file.close();
    }
}

FileObj::~FileObj()
{
}

void FileObj::printVertexList()
{
    int index = 1;
    for (auto vertex : this->vertex_list) {
        std::cout << "vertex " << index++ << " : x: " << vertex[0] << " y: " << vertex[1] << " z: " << vertex[2] << std::endl;
    }
}

void FileObj::printFaceList()
{
    int index = 1;
    for (auto face : this->face_list) {
        std::cout << "face " << index++ << " :";
        for (auto vertex : face) {
            std::cout << " {x: " << vertex[0] << " y: " << vertex[1] << " z: " << vertex[2] << "}";
        }
        std::cout << "\n";
    }
}

FaceList FileObj::getFaceList()
{
    return this->face_list;
}

void FileObj::printTextureList()
{
    int index = 1;
    for (auto texture : this->texture_list) {
        std::cout << "texture " << index++ << " :";
        for (auto vertex : texture) {
            std::cout << " {x: " << vertex[0] << " y: " << vertex[1] << "}";
        }
        std::cout << "\n";
    }
}

void FileObj::printNormalList()
{
    int index = 1;
    for (auto normal : this->normal_list) {
        std::cout << "normal " << index++ << " :";
        for (auto vertex : normal) {
            std::cout << " {x: " << vertex[0] << " y: " << vertex[1] << " z: " << vertex[2] << "}";
        }
        std::cout << "\n";
    }
}
