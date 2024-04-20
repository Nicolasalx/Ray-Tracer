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

        static double getBw01()
        {
            std::random_device random;
            std::mt19937 gen(random());
            std::uniform_real_distribution<double> distr(0.0, 1.0);

            return distr(gen);
        }

        static double get(double min, double max)
        {
            std::random_device random;
            std::mt19937 gen(random());
            std::uniform_real_distribution<double> distr(min, max);

            return distr(gen);
        }
    };
}

#endif /* !RANDOM_HPP_ */
