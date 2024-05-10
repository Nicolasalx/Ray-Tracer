/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** typeObj
*/

#include "FileObj.hpp"

void FileObj::VType(std::istringstream &stream)
{
    std::vector<double> vertex(3);
    stream >> vertex[0] >> vertex[1] >> vertex[2];
    if (stream.fail()) {
        std::cerr << "Error: Invalid obj file\n";
        return;
    }
    this->vertex_list.push_back(vertex);
}

void FileObj::VNType(std::istringstream &stream)
{
    std::vector<double> vertex_normal(3);
    stream >> vertex_normal[0] >> vertex_normal[1] >> vertex_normal[2];
    if (stream.fail()) {
        std::cerr << "Error: Invalid obj file\n";
        return;
    }
    this->vertex_normal_list.push_back(vertex_normal);
}

void FileObj::VTType(std::istringstream &stream)
{
    std::vector<double> vertex_texture(2);
    stream >> vertex_texture[0] >> vertex_texture[1];
    if (stream.fail()) {
        std::cerr << "Error: Invalid obj file\n";
        return;
    }
    this->vertex_texture_list.push_back(vertex_texture);
}

void FileObj::VFType(std::istringstream &stream)
{
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