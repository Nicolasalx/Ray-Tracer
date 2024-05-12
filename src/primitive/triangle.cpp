/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** triangle
*/

#include "Triangle.hpp"

bool Rt::Triangle::is_interior(double a, double b, Rt::HitData &rec) const
{
    if ((a < 0) || (b < 0) || (a + b > 1)) {
        return false;
    }
    rec.u = a;
    rec.v = b;
    return true;
}