/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** FileObj
*/

#ifndef FILEOBJ_HPP_
#define FILEOBJ_HPP_
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <vector>

using FaceList = std::vector <std::vector<std::vector <double>>>;
using NormalList = std::vector <std::vector<std::vector <double>>>;
using TextureList = std::vector <std::vector<std::vector <double>>>;
using VertexList = std::vector<std::vector<double>>;

class FileObj {
    public:
        FileObj(const std::string &file_path);
        ~FileObj() = default;
        void printVertexList();
        void printTextureList();
        void printNormalList();
        void printFaceList();
        void VType(std::istringstream &stream);
        void VNType(std::istringstream &stream);
        void VTType(std::istringstream &stream);
        void VFType(std::istringstream &stream);
        void AddVFTN(VertexList &face, VertexList &texture, VertexList &normal, std::string face_index, int index);
        FaceList getFaceList();
    protected:
        VertexList vertex_texture_list;
        VertexList vertex_normal_list;
        VertexList vertex_list;
        FaceList face_list;
        NormalList normal_list;
        TextureList texture_list;
};

#endif /* !FILEOBJ_HPP_ */
