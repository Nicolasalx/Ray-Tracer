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
    #include "my_tracked_exception.hpp"

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
            void getMetal(const libconfig::Setting &material, std::string &materialName);
            void getLambertian(const libconfig::Setting &material, std::string &materialName);
            void getDielectric(const libconfig::Setting &material, std::string &materialName);
            void getDiffuseLight(const libconfig::Setting &material, std::string &materialName);

            // Handle primitive
            void parsePrimitives(libconfig::Config &cfg, Rt::ObjectList &world);
            void chooseMaterialType(std::shared_ptr<Rt::IMaterial> &material, std::string &materialName);

            // Camera
            void parseCamera(libconfig::Config &cfg, Rt::Camera &camera);

            // Sphere
            void parseAllSphere(const libconfig::Setting &primitivesSettings, Rt::ObjectList &world);
            void analyseOneSphere(const libconfig::Setting &currentSphere, Rt::ObjectList &world);

            // Triangle
            void parseAllTriangle(const libconfig::Setting &primitivesSettings, Rt::ObjectList &world);
            void analyseOneTriangle(const libconfig::Setting &currentTriangle, Rt::ObjectList &world);

            // Plane
            void parseAllPlane(const libconfig::Setting &primitivesSettings, Rt::ObjectList &world);
            void analyseOnePlane(const libconfig::Setting &currentPlane, Rt::ObjectList &world);

            // Cone
            void parseAllCone(const libconfig::Setting &primitivesSettings, Rt::ObjectList &world);
            void analyseOneCone(const libconfig::Setting &currentCone, Rt::ObjectList &world);

            // Cylinder
            void parseAllCylinder(const libconfig::Setting &primitivesSettings, Rt::ObjectList &world);
            void analyseOneCylinder(const libconfig::Setting &currentCylinder, Rt::ObjectList &world);

            // Object
            void parseObject(libconfig::Config &cfg, Rt::ObjectList &world);
            void parseOneObject(const libconfig::Setting &object, Rt::ObjectList &world);

            // Generic functions to parse
            std::vector<int> parseVector3D(const libconfig::Setting &vector);
            std::vector<int> parseVector2D(const libconfig::Setting &vector);
            std::vector<double> parseColor(const libconfig::Setting &vector);
            std::vector<double> parseColorMul(const libconfig::Setting &vector);

            Math::Point3D vectorToPoint3D(std::vector<int> list);
            Math::Point3D vectorTo3D(std::vector<int> list);
            double checkValueIsColor(int value);

            template<typename T>
            void checkFieldExist(const libconfig::Setting &currentElem, const std::string &field, T &valueToGet, const std::string &surfaceName)
            {
                if (currentElem.exists(field)) {
                    currentElem.lookupValue(field, valueToGet);
                } else {
                    throw my::tracked_exception("Error in the parsing of the " + surfaceName);
                }
            }

        private:
            std::vector<std::string> _listConfigFile;
            std::map<std::string, material_t> _materialsList;
    };
}

#endif /* !LOADSCENE_HPP_ */
