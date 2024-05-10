/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** interval
*/

#include "Interval.hpp"

double Rt::Interval::size() const
{
    return max - min;
}

bool Rt::Interval::contains(double x) const
{
    return min <= x && x <= max;
}

bool Rt::Interval::surrounds(double x) const
{
    return min < x && x < max;
}

double Rt::Interval::clamp(double x) const
{
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}

Rt::Interval Rt::Interval::expand(double delta) const
{
    double padding = delta / 2.0;
    return Interval(min - padding, max + padding);
}