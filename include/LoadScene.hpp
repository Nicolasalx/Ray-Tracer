/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** LoadScene
*/

#ifndef LOADSCENE_HPP_
    #define LOADSCENE_HPP_

    #include <string>
    #include "ObjectList.hpp"
    #include "Camera.hpp"
    #include <vector>
    #include <libconfig.h++>
    #include <map>
    #include "Point3D.hpp"

namespace Rt
{
    enum material_name_e {
        METAL,
        LAMBERTIAN,
        DIELECTRIC,
        DIFFUSE_LIGHT
    };

    typedef struct {
        material_name_e name;
        Math::Color01 color;
        double reflection = 0.0;
    } material_t;

    class LoadScene {
        public:
            LoadScene() = default;
            ~LoadScene() = default;

            void parseArgs(int argc, const char **argv);
            void loadAllScenes(ObjectList &world, Camera &camera);
            void loadScene(const std::string &filepath, ObjectList &world, Camera &camera);

            // Handle materials
            void parseMaterials(libconfig::Config &cfg);
            void getMetal(const libconfig::Setting &material, libconfig::Config &cfg);
            void getLambertian(const libconfig::Setting &material, libconfig::Config &cfg);
            void getDielectric(const libconfig::Setting &material, libconfig::Config &cfg);
            void getDiffuseLight(const libconfig::Setting &material, libconfig::Config &cfg);  

            // Handle primitive
            void parsePrimitives(libconfig::Config &cfg, Rt::ObjectList &world);
            void chooseMaterialType(std::shared_ptr<Rt::IMaterial> &material);
            void parseLight(libconfig::Config &cfg, Rt::ObjectList &world);

            // Camera
            void parseCamera(libconfig::Config &cfg, Rt::Camera &camera);

            // Sphere
            void parseAllSphere(libconfig::Config &cfg, const libconfig::Setting &primitivesSettings, Rt::ObjectList &world);
            void analyseOneSphere(const libconfig::Setting &currentSphere, Rt::ObjectList &world);

            // Triangle
            void parseAllTriangle(libconfig::Config &cfg, const libconfig::Setting &primitivesSettings, Rt::ObjectList &world);
            void analyseOneTriangle(const libconfig::Setting &currentTriangle, Rt::ObjectList &world);

            // Plane
            void parseAllPlane(libconfig::Config &cfg, const libconfig::Setting &primitivesSettings, Rt::ObjectList &world);
            void analyseOnePlane(const libconfig::Setting &currentPlane, Rt::ObjectList &world);

            // Generic functions to parse
            std::vector<int> parseVector3D(const libconfig::Setting &vector);
            std::vector<int> parseVector2D(const libconfig::Setting &vector);
            std::vector<int> parseColor(const libconfig::Setting &vector);
            Math::Point3D vectorToPoint3D(std::vector<int> list);
            Math::Point3D vectorTo3D(std::vector<int> list);

        private:
            std::vector<std::string> _listConfigFile;
            std::map<std::string, material_t> _materialsList;
    };
}

#endif /* !LOADSCENE_HPP_ */
