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

void Rt::Raytracer::createObjModel(Rt::ObjectList &world ,const std::string &path)
{
    auto left_red     = std::make_shared<Rt::Lambertian>(Math::Color01(1.0, 0.2, 0.2));

    FileObj obj(path);
    FaceList faceList = obj.getFaceList();
    for (auto face : faceList) {
        for (int i = 0; i < face.size() - 2; i++) {
            world.add(std::make_shared<Rt::Triangle>(Math::Point3D(face[0][0],face[0][1],face[0][2]),
            Math::Point3D(face[i + 1][0], face[i + 1][1],face[i + 1][2]), Math::Point3D(face[i + 2][0] ,face[i + 2][1] ,face[i + 2][2]), left_red));
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
                std::vector<double> vertex(3);
                stream >> vertex[0] >> vertex[1] >> vertex[2];
                if (stream.fail()) {
                    std::cerr << "Error: Invalid obj file\n";
                    return;
                }
                this->vertex_list.push_back(vertex);
            }
            if (line == "vn") {
                std::vector<double> vertex_normal(3);
                stream >> vertex_normal[0] >> vertex_normal[1] >> vertex_normal[2];
                if (stream.fail()) {
                    std::cerr << "Error: Invalid obj file\n";
                    return;
                }
                this->vertex_normal_list.push_back(vertex_normal);
            }
            if (line == "vt") {
                std::vector<double> vertex_texture(2);
                stream >> vertex_texture[0] >> vertex_texture[1];
                if (stream.fail()) {
                    std::cerr << "Error: Invalid obj file\n";
                    return;
                }
                this->vertex_texture_list.push_back(vertex_texture);
            }
            if (line == "f") {
                std::vector<std::vector<double>> face;
                std::vector<std::vector<double>> texture;
                std::vector<std::vector<double>> normal;
                while (stream) {
                    std::string face_index;
                    stream >> face_index;
                    if (stream.fail()) {
                        break;
                    }
                    int index = 0;
                    size_t pos = 0;
                    std::string token;
                    while((pos = face_index.find("/")) != std::string::npos){
                        token = face_index.substr(0, pos);
                        face_index.erase(0, pos + 1);
                        if (index == 0) {
                            face.push_back(vertex_list.at(std::stoi(token) - 1));
                        }
                        if (index == 1 && token != "") {
                            texture.push_back(vertex_texture_list.at(std::stoi(token) - 1));
                        }
                        index++;
                    }
                    if (index == 0) {
                        face.push_back(vertex_list.at(std::stoi(face_index) - 1));
                    }
                    if (index == 1) {
                        texture.push_back(vertex_texture_list.at(std::stoi(face_index) - 1));
                    }
                    if (index == 2) {
                        normal.push_back(vertex_normal_list.at(std::stoi(face_index) - 1));
                    }
                }
                this->face_list.push_back(face);
                this->texture_list.push_back(texture);
                this->normal_list.push_back(normal);
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
