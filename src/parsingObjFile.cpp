/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** parsingObjFile
*/

#include "FileObj.hpp"

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
            if (line == "f") {
                std::vector<std::vector<double>> face;
                while (stream) {
                    int vertex_index;
                    stream >> vertex_index;
                    if (stream.fail()) {
                        break;
                    }
                    face.push_back(vertex_list.at(vertex_index - 1));
                }
                this->face_list.push_back(face);
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