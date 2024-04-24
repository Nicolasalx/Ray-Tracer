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

typedef std::vector <std::vector<std::vector <double>>> FaceList;

class FileObj {
    public:
        FileObj(std::string file_path);
        ~FileObj();
        void printVertexList();
        void printFaceList();
        FaceList getFaceList();
    protected:
        std::vector <std::vector<double>> vertex_list;
        FaceList face_list;
};

#endif /* !FILEOBJ_HPP_ */
