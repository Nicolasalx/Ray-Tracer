/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Config
*/

#include <iostream>
#include <libconfig.h++>
#include "ObjectList.hpp"
#include "Camera.hpp"

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

class ConfigLoader {
    public:
        void loadCfg(const std::string& configFile, Rt::ObjectList& world, Rt::Camera& cam);
    protected:
    private:
};

#endif /* !CONFIG_HPP_ */
