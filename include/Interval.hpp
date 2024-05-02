/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Interval
*/

#ifndef INTERVAL_HPP_
    #define INTERVAL_HPP_

    #include <limits>

namespace Rt
{
    class Interval
    {
    public:
        double min;
        double max;

        Interval() : min(+std::numeric_limits<double>::infinity()), max(-std::numeric_limits<double>::infinity()) {};
        Interval(double min_, double max_) : min(min_), max(max_) {}
        Interval(const Rt::Interval &a, const Rt::Interval &b)
        {
            min = a.min <= b.min ? a.min : b.min;
            max = a.max >= b.max ? a.max : b.max;
        }
        ~Interval() = default;

        double size() const
        {
            return max - min;
        }

        bool contains(double x) const
        {
            return min <= x && x <= max;
        }

        bool surrounds(double x) const
        {
            return min < x && x < max;
        }

        double clamp(double x) const
        {
            if (x < min) {
                return min;
            }
            if (x > max) {
                return max;
            }
            return x;
        }

        Interval expand(double delta) const
        {
            double padding = delta / 2.0;
            return Interval(min - padding, max + padding);
        }

        static const Interval empty, universe;
    };
}

#endif /* !INTERVAL_HPP_ */
