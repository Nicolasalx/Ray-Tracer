/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** random
*/

#include "Random.hpp"

double Rt::Random::getBw01()
{
    return std::rand() / (RAND_MAX + 1.0);
}

double Rt::Random::get(double min, double max)
{
    return min + (max - min) * getBw01();
}