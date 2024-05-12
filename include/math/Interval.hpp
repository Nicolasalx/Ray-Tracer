/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Interval
*/

#ifndef INTERVAL_HPP_
    #define INTERVAL_HPP_

    #include <limits>
    #include <algorithm>

namespace Rt
{
    class Interval
    {
    public:
        double min;
        double max;

        Interval() : min(std::numeric_limits<double>::infinity()), max(-std::numeric_limits<double>::infinity()) {};
        Interval(double min_, double max_) : min(min_), max(max_) {}
        Interval(const Rt::Interval &a, const Rt::Interval &b)
        {
            min = std::min(a.min, b.min);
            max = std::max(a.max, b.max);
        }
        ~Interval() = default;

        double size() const;

        bool contains(double x) const;

        bool surrounds(double x) const;

        double clamp(double x) const;

        Interval expand(double delta) const;
    };
}

#endif /* !INTERVAL_HPP_ */
