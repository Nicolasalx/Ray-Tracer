/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Random
*/

#ifndef RANDOM_HPP_
    #define RANDOM_HPP_

    #include <random>

namespace Rt
{
    class Random
    {
    public:
        ~Random() = default;

        static double getBw01();

        static double get(double min, double max);
    };
}

#endif /* !RANDOM_HPP_ */
